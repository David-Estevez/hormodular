"""
	Core

	hormodular main functions

"""

__author__ = 'David Estevez Fernandez'
__license__ = 'GPLv3'

from ModularRobot import ModularRobot
from EvolutionConfiguration import EvolutionConfiguration

import time as t
import os
from xml.dom.minidom import parse, parseString # for parsing xml files
import subprocess

def getRobotDataFromFile( file):
	"""
		Extracts the robot data from a file
	"""
	robotData = dict()
	
	stringTags = [ 'name', 'simulationfile']
	floatTags = [ 'runtime', 'timestep']
	intTags = [ 'nModules' ]
	
	f = open( file, 'r')
	
	for line in f.readlines():
		data = line.split('=')
		
		if data[0] in stringTags:	
			robotData[ data[0] ] = data[1].replace( '\n', '')
		elif data[0] in floatTags:
			robotData[ data[0] ] = float( data[1] )
		elif data[0] in intTags:
			robotData[ data[0] ] = int( data[1] )
		#else:
		#	print 'Tag not recognized: ' + str(data[0])
			
	f.close()
	print 'Read parameters from file: ' + file

	return ModularRobot( robotData['name'] , robotData['nModules'], robotData['runtime'], robotData['timestep'], robotData['simulationfile'])


def getEvolutionConfigurationFromFile( file ):
	"""
		From a xml file retrieves a EvolutionConfiguration object
	"""
	xmlfile = parse( file )
	return getEvolutionConfigurationFromXml( xmlfile)
	
	
def getEvolutionConfigurationFromXml( xmlfile ):
	"""
		From a parsed xml tree retrieves a EvolutionConfiguration object
	"""
	# Get algorithm 
	algorithmNode = xmlfile.getElementsByTagName( 'Algorithm' )[0]
	strAlgorithmParams = getEntriesFromNode( algorithmNode)
	algorithmParams = {}
	for key in strAlgorithmParams:		
		algorithmParams[key] = float(strAlgorithmParams[key])
			
	# Get mutation & crossover operators
	genotypeNode = xmlfile.getElementsByTagName( 'FloatingPoint' )[0]
	genotypeEntries = getEntriesFromNode( genotypeNode )
	mutationParams = {}
	crossoverParams = {}
	
	for key in genotypeEntries:
		if 'mut.' in key:
			mutationParams[key] = float(genotypeEntries[key])
		elif 'crx.' in key:
			crossoverParams[key] = float(genotypeEntries[key])
	
	# Get population 
	registryNode = xmlfile.getElementsByTagName( 'Registry')[0]
	registryEntries = getEntriesFromNode( registryNode )
	population = registryEntries['population.size']
	
	# Get termination criteria 
	terminationCriteria = {}
	for key in registryEntries:
		if 'term.' in key:
			terminationCriteria[key] = float( registryEntries[key] )		
 
	# Create id
	id = createTimestamp()
	
	return EvolutionConfiguration( algorithmParams, mutationParams, crossoverParams, population, terminationCriteria, id)
	

		
		
def getEntriesFromNode( node):
	"""
		Returns all the pairs key-value from a xml file <Entry>
	"""
	pairs = {}
	
	for element in node.getElementsByTagName( 'Entry'):
		pairs[ element.getAttribute('key') ] = getDataFromNode( element)
		
	return pairs
	
	
	
def getDataFromNode( node):
	"""
		Returns the data contained in a certain xml node
	"""
	if node.hasChildNodes:
		# If xml parser considers that the value is a child entry
		return unicode( str(node.childNodes[0].data ))
	else:
		#If xml parser considers that the value is part of the node data
		return unicode( str(node.data))
		
		
def createTimestamp( ):
	"""
		Creates timestamp / id from current time
	"""
	currentTime = t.localtime()
	return '-'.join( [ str(currentTime[i]) for i in range(6) ])
	
	
def createWorkingFolder( rootFolder, timestamp ):
	"""
		Creates the working folder and the files needed for the program
	"""
	# Create temp folder if not present
	if not os.path.isdir( "../data/tmp"):
		os.mkdir("../data/tmp")
		
	# Create data folder
	dataFolder =  rootFolder + '/data/tmp/data-' + timestamp
	if not os.path.isdir( dataFolder):
		os.mkdir( dataFolder)
	
	return dataFolder
	

def createEmptyGaitTableOnDataFolder( robot, folder):
	"""
		Creates the gait table on the specified folder
		(temporal function ?)
	"""
	createEmptyGaitTable(robot, folder + '/gait_table.txt')
	
	
def createEmptyGaitTable(robot, file):
	"""
		Creates a gait table with 0 for all the parameters
	"""
	table = generateGaitTable( robot )
	
	# Open the file and save the table data
	f = open( file, 'w')
	f.write( table)
	f.close()


def generateGaitTable(robot):
	"""
		Generates a string containing the gait table info of the current individual
	"""
	if len(robot.amplitudes) == robot.nModules and len(robot.offsets) == robot.nModules and len(robot.phases) == robot.nModules:
					
		return_string =  '# Gait Table created by Hormodular [https://github.com/David-Estevez/hormodular.git]\n'
		return_string += '# name: gaitTable\n'
		return_string += '# type: matrix\n'
		return_string += '# rows: ' + str(robot.nModules) + '\n'
		return_string += '# columns: 3\n'
		
		individual_strings = list()
		
		for i in range(0, robot.nModules):
			return_string += ' '.join( str(j) for j in [robot.amplitudes[i], robot.offsets[i], robot.phases[i] ]) + '\n'
		
		return return_string
	else:
		raise IndexError


def addNode( parent, tag, attributes, value ):
	"""
		Adds a child node to a xml node with a tag, attribute and value
	"""
	xmlbase = parseString( '<xml></xml>')
	newTag = xmlbase.createElement( tag )
	valueNode = xmlbase.createTextNode( str(value) )
	
	for key in attributes:
		newTag.setAttribute( key, attributes[key])
		
	newTag.appendChild( valueNode)
	parent.appendChild( newTag)
	
	
def addEntryToRegistry( xmlfile, parameter, value):
	"""
		Adds an entry in the registry section of the xml file
	"""
	addNode( xmlfile.getElementsByTagName('Registry')[0], 'Entry',  {'key':parameter}, value )
	
	
def addDefaultParametersToRegistry( xmlfile, dataFolder ):
	"""
		Adds the default configuration to the registry section of the xml file
	"""
	defaultConfig = []
	
	defaultConfig.append( ( 'log.level', 5 ))
	defaultConfig.append( ('log.filename', dataFolder + '/log.txt' ))	
	defaultConfig.append( ('log.frequency', 1 ))
	
	defaultConfig.append( ('milestone.filename', dataFolder + '/milestonefile.txt'))
	defaultConfig.append( ('milestone.interval', 1 ))
	
	
	for value in defaultConfig:
		addEntryToRegistry( xmlfile, value[0], value[1] )
	
	
def addRobotToConfigFile( xmlfile, robot, dataFolder ):
	"""
		Adds the robot information to the xml tree
	"""
	addRobotToRegistry( xmlfile, robot, dataFolder)
	setRobotDimensions( xmlfile, robot )
	
def addRobotToRegistry( xmlfile, robot, dataFolder ):
	"""
		Puts the robot data into the xml registry section
	"""
	addEntryToRegistry( xmlfile, 'robot.modules', robot.nModules )
	addEntryToRegistry( xmlfile, 'robot.runtime', robot.runTime )
	addEntryToRegistry( xmlfile, 'robot.timestep', robot.timeStep )
	addEntryToRegistry( xmlfile, 'robot.simulationfile', robot.simulationFile )
	addEntryToRegistry( xmlfile, 'robot.gaittablefile', dataFolder + '/gait_table.txt' )
	
def setRobotDimensions( xmlfile, robot ):
	"""
		Customizes the genotype with the correct dimensions
	"""
	genotypeNode = xmlfile.getElementsByTagName( 'Genotype' )[0]
	
	# Set the correct genome size
	for element in genotypeNode.getElementsByTagName('Entry'):
		if element.getAttribute('key') == 'dimension':
			if element.hasChildNodes:
				# If xml parser considers that the value is a child entry
				element.childNodes[0].data = unicode( str( robot.nModules))
			else:
				#If xml parser considers that the value is part of the node data
				element.data = unicode( str( robot.nModules))
	
def saveEvolutionFile( xmlfile, dataFolder ):
	"""
		Saves the contents of the xml file in the specified folder
	"""
	f = open ( dataFolder + '/evolution_parameters.xml', 'w')
	f.write( xmlfile.toprettyxml() )
	f.close()
	

def runEvolution( dataFolder ):
	"""
		Runs the evolve binary with the configuration file created
	"""
	subprocess.call( [ './evolve-gaits', dataFolder + '/evolution_parameters.xml'])
	
if __name__ == '__main__':
	# Test things
	pass
