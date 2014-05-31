"""
	hormodular 
	
	Hormodular main program, intended as an automated framework for evolution 
	of modular robots

"""

__author__ = 'David Estevez Fernandez'
__license__ = 'GPLv3'

# Imports:
from xml.dom.minidom import parse, parseString # for parsing xml files
import os, sys
import time as t
import optparse
	
class Hormodular:
	
	def __init__(self):
		# Define module variables:
		self.robotData = dict()
		self.dataFolder = ''
		self.evolutionFile = ''
		self.xmlFile = None

	# Functions:
	def showInfo(self):
		"""
			Hormodular intro message
		"""
		print "Hormodular - Modular Robot Framework"
		print "------------------------------------"
		
		
	def getRobotDataFromUser(self):
		"""
			Asks the user for robot info
		"""
		self.robotData['name'] = raw_input('Insert robot name:>')
		self.robotData['runtime'] = float( raw_input('Run time (ms):>'))
		self.robotData['timestep'] = float( raw_input('Time step (ms):>'))
		self.robotData['nModules'] = int( raw_input('Number of modules:>'))
		self.robotData['configFile'] = raw_input('Config file:>')
		
		
	def getRobotDataFromFile(self, file):
		"""
			Extracts the robot data from a file
		"""
		stringTags = [ 'name', 'configFile']
		floatTags = [ 'runtime', 'timestep']
		intTags = [ 'nModules' ]
		
		f = open( file, 'r')
		
		for line in f.readlines():
			data = line.split('=')
			
			if data[0] in stringTags:	
				self.robotData[ data[0] ] = data[1]
			elif data[0] in floatTags:
				self.robotData[ data[0] ] = float( data[1] )
			elif data[0] in intTags:
				self.robotData[ data[0] ] = int( data[1] )
			else:
				print 'Tag not recognized: ' + str(data[0])
				
		f.close()
		print 'Read parameters from file: ' + file
		
		
		
	def createWorkingFolderAndFiles(self):
		"""
			Create the working folder and the files needed for the program
		"""
		# Create temp folder if not present
		if not os.path.isdir( "../data/tmp"):
			os.mkdir("../data/tmp")
			
		# Get timestamp
		currentTime = t.localtime()
		currentTimeStr = '-'.join( [ str(currentTime[i]) for i in range(6) ])
		
		# Create data folder
		self.dataFolder = '../data/tmp/data-' + currentTimeStr
		if not os.path.isdir( self.dataFolder):
			os.mkdir( self.dataFolder)
		
		# Create empty gait table:
		#self.createEmptyGaitTable()


	def createEmptyGaitTable(self):
		"""
			Creates a gait table with 0 for all the parameters
		"""
		values = [ 0 for i in range(0, self.robotData['nModules']) ]
		table = self.generateGaitTable( self.robotData['nModules'], values, values, values)
		
		# Open the file and save the table data
		f = open( self.dataFolder + '/gait_table.txt', 'w')
		f.write( table)
		f.close()

		
	def generateGaitTable(self, size, amplitudes, offsets, phases):
		"""
			Generates a string containing the gait table info of the current individual
		"""
		if len(amplitudes) == size and len(offsets) == size and len(phases) == size:
						
			return_string =  '# Gait Table created by Hormodular [https://github.com/David-Estevez/hormodular.git]\n'
			return_string += '# name: gaitTable\n'
			return_string += '# type: matrix\n'
			return_string += '# rows: ' + str(size) + '\n'
			return_string += '# columns: 3\n'
			
			individual_strings = list()
			
			for i in range(0, size):
				return_string += ' '.join( str(j) for j in [amplitudes[i], offsets[i], phases[i] ]) + '\n'
			
			return return_string
		else:
			raise IndexError
			
	def customizeEvolutionFile( self):
		"""
			Change the basic parameter file to add the needed parameters
		"""
		# Parse the xml data
		self.xmlfile = parse(self.evolutionFile)

		# Set the correct genome size
		for element in self.xmlfile.getElementsByTagName('Entry'):
			if element.getAttribute('key') == 'dimension':
				if element.hasChildNodes:
					# If xml parser considers that the value is a child entry
					element.childNodes[0].data = unicode( str( self.robotData['nModules']))
				else:
					#If xml parser considers that the value is part of the node data
					element.data = unicode( str( self.robotData['nModules']))
					
		# Get the registry node:
		registryNode = self.xmlfile.getElementsByTagName('Registry')[0]
		
		# Set the log file info
		"""
		<Entry key="log.level">3</Entry> <!-- log level; valid values are 1 (minimal) to 5 (verbose) (default: 3) -->
		<Entry key="log.filename">log.txt</Entry> <!-- log filename (default: none) -->
		<Entry key="log.frequency">1</Entry> <!-- log only every 'frequency' generations (default: 1) -->
		"""
		self.addEntry( registryNode, "log.level", 5) # 5 -> verbose log
		self.addEntry( registryNode, "log.filename", self.dataFolder + '/log.txt' ) 
		self.addEntry( registryNode, "log.frequency", 1 ) # Log each 1 generation(s)
		
		# Set the milestone file info
		"""
		<Entry key="milestone.filename">out.txt</Entry> <!-- milestone file (if stated) stores all the population (default: none) -->
		<Entry key="milestone.interval">0</Entry> <!-- milestone saving interval in generations; 0: save only at the end (default: 0) -->
		"""
		self.addEntry( registryNode, "milestone.filename", self.dataFolder + '/milestonefile.txt')
		self.addEntry( registryNode, "milestone.interval", 1 ) # Save milestone each 1 generation(s)
		
		# Set the robot info
		"""
		<Entry key='robot.modules'>3</Entry> <!-- Number of modules -->
    	<Entry key='robot.runtime'>10000</Entry> <!-- Max runtime (ms) -->
    	<Entry key='robot.timestep'>1</Entry> <!-- Time step (ms) -->
    	<Entry key='robot.simulationfile'>../../data/models/Minicube-II.env.xml</Entry>  <!-- Simulation model file -->
    	<Entry key='robot.configfile'>../../data/gait tables/evolving_gaits.txt</Entry> <!-- Gait table file -->
    	"""
		self.addEntry( registryNode, "robot.modules", self.robotData['nModules'])
		self.addEntry( registryNode, "robot.runtime", int(self.robotData['runtime']))
		self.addEntry( registryNode, "robot.timestep", int(self.robotData['timestep']))
		self.addEntry( registryNode, "robot.simulationfile", self.robotData['simulationFile'])
		self.addEntry( registryNode, "robot.configfile", self.robotData['configFile'])
		
	
	def addEntry(self, node, key, value ):
		"""
			Adds an child entry to the node specified of the xml tree with the
			given value
		"""
		print "Added to node: " + str(key) + str(value)
							
	def main(self, args):
		# Intro screen:
		self.showInfo()
		
		# Get configuration data:
		if len(args) == 2:
			self.getRobotDataFromFile( args[1] )
		else:
			self.getRobotDataFromUser()
			print self.robotData

			
		self.evolutionFile = raw_input('Evolution configuration file:>')
		
		# Create needed folders and files:		
		self.createWorkingFolderAndFiles()
		
		# Open evolution file and generate custom parameters
		self.customizeEvolutionFile()
		
		# Write modified xml file to data folder
		print self.xmlfile.toprettyxml()
		f = open( self.dataFolder + '/parameters.xml', 'w')
		self.xmlfile.writexml( f)
		f.close()

if __name__ == '__main__':
	#foo = Hormodular()
	#foo.main(sys.argv)
	import hormodular.core as h
	
	# Get configuration data:
	if len(sys.argv) == 2:
		robot = h.getRobotDataFromFile( sys.argv[1] )
	else:
		robot = None
		
	print robot
	
	# Get evolution configuration
	problem = h.getEvolutionConfigurationFromFile( './parameters.xml')
	print problem
	
	# Get timestamp
	robot.problemId = problem.timestamp
	
	# Create folder
	dataFolder = h.createWorkingFolder( '..', robot.problemId)
	
	# Create empty gait table
	#h.createEmptyGaitTableOnDataFolder( robot, dataFolder)
	
	# Load robot model file, set gait table folder and copy it to new location
	xmlconfigfile = parse(robot.configFile)
	h.updateAndCopyRobotFile( xmlconfigfile, dataFolder )
	robot.configFile = dataFolder + '/robot_config.xml'
	
	# Customize and create evolution file
	xmlfile = parse('./parameters.xml')
	
	# 
	h.addDefaultParametersToRegistry( xmlfile, dataFolder )
	
	h.addRobotToConfigFile( xmlfile, robot, dataFolder)
	
	h.saveEvolutionFile( xmlfile, dataFolder )
	
	h.runEvolution( dataFolder)
	
	
	
