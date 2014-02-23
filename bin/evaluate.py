"""
	Evaluate
	
	Evaluates an individual based on the milestone file
	
	Part of the hormodular project
	
"""
from __future__ import division 
import wx # For GUI

from xml.dom.minidom import parseString # for parsing xml files
import subprocess
import matplotlib
matplotlib.use('WXAgg')
import pylab # for plotting nice fitness graphs
import os
from individual import Individual

__author__ = 'David Estevez-Fernandez'
__license__ = 'GPLv3'


class MainWin( wx.Frame):
	
	def __init__( self, parent):
		# Program variables initialization
		self.individuals = []
		self.evaluationProgramPath = '/home/def/Repositories/hormodular/src/build-qt/evaluate-gaits'
		self.gaitTableFile = '/home/def/Repositories/hormodular/data/gait tables/evaluation.txt'
		self.robotSceneFile = ''
		self.logFile = ''
		
		# Construct the window
		super( MainWin, self).__init__( parent, title='hormodular - evaluate', size = ( 400, 300), style=wx.DEFAULT_FRAME_STYLE ^ wx.RESIZE_BORDER)
		
		self.InitUI()
		self.Centre()
		self.Show()
		
	def InitUI( self):
		""" Definition of the UI """
		self.panel = wx.Panel(self)

		font = wx.SystemSettings_GetFont(wx.SYS_SYSTEM_FONT)
		font.SetPointSize(9)
		
		#Textbox to put the filepath of the milestone file
		self.fileBox = wx.TextCtrl( self.panel, pos=( 10, 10), size=( 400-10-100-10, 25))
		
		# Button for loading the file
		self.loadButton = wx.Button( self.panel, label='Load', pos=(400-10-100, 10), size=( 100, 25))
		self.loadButton.Bind( wx.EVT_BUTTON, self.loadFile)
		
		# Listbox for listing the individuals
		self.listBoxIndividuals = wx.ListBox( self.panel, pos=(10, 10+25+10), size=(400-10-10, 200))

		# Run parameters:
		self.runText = wx.StaticText( self.panel, label = 'Run for (ms):', pos=( 10, 10+25+10+200+10), size = (80, 25))
		self.runtimeBox = wx.TextCtrl( self.panel, pos = ( 10+80+10, 10+25+10+200+5), size = (130, 25) )
		self.runtimeBox.SetValue( '-1')
		self.runButton = wx.Button( self.panel, label = 'Run', pos = ( 10+80+10+130+5, 10+25+10+200+5), size = (75, 25))
		self.runButton.Bind( wx.EVT_BUTTON, self.runEvaluation )
		
		# Plot fitness function:
		self.fitnessButton = wx.Button( self.panel, label = 'Plot fitness', pos = ( 10+80+10+110+5+75+20, 10+25+10+200+5), size = (80, 25))
		self.fitnessButton.Bind( wx.EVT_BUTTON, self.plotFitness )
		
	def loadFile(self, e):
		"""
			Actions to be made when load button is pressed.
		"""
		lastFilePath = self.fileBox.GetValue()
		
		# Create a file selection dialog
		if lastFilePath == '':
			lastFilePath = '~/Repositories/hormodular/src'
		else:
			lastFilePath = os.path.dirname( lastFilePath)
		
		print lastFilePath	
		fileDialog = wx.FileDialog( self, defaultDir = lastFilePath, wildcard = '*.*', style = wx.FD_OPEN )
	
		# Show dialog to get file path
		fileDialog.ShowModal()
		filePath = fileDialog.GetPath()
		fileDialog.Destroy()
		print 'Loading file: ' + filePath
		self.fileBox.SetValue( filePath )
			
		# At this point filePath should contain the path to the results file
		# Parse the xml file:
		self.parseFile( filePath)

		
	def runEvaluation( self, e):
		"""
			Runs the evaluation program with the specified parameters
		"""
		print 'Evaluating things...'
		print 'Run with individual: ' + str( self.individuals[ self.listBoxIndividuals.GetSelections()[0] ])
		
		# Get the simulation time:
		sim_time = int(self.runtimeBox.GetValue())
		
		# Create the gait table:
		file = open( self.gaitTableFile, 'w')
		file.write( self.individuals[ self.listBoxIndividuals.GetSelections()[0]].generateGaitTable())
		file.close()
		
		# Run the program:
		subprocess.call( [ self.evaluationProgramPath, self.robotSceneFile, self.gaitTableFile, str(sim_time) ])
		
	def plotFitness( self, e):
		"""
			Extracts the fitness data from the log file and plots it
		"""
		
		print 'Plotting fitness...'
		
		# Get text from log file
		print 'Opening ' + self.logFile
		
		f = open( self.logFile, 'r')
		
		# Extract fitness history:
		fitness_history = []
		generation_history = []
		avg_fitness_history = []
		
		for line in f.readlines():
			if line.find( 'Generation: ') != -1:
				generation_history.append( int( line.split(' ')[1]))
				continue
				
			if line.find( '\tmax: ') != -1:
				fitness_history.append( float( line.split(' ')[1]))
				continue
				
			if line.find( '\tavg: ') != -1:
				avg_fitness_history.append( float( line.split(' ')[1]))
				continue
	
		f.close()					
		
		#print generation_history
		#print fitness_history
		
		# Plot	
		pylab.plot( generation_history, fitness_history, 'b-')
		#pylab.plot( generation_history, avg_fitness_history, 'r-')
		pylab.show()
		
		
	def parseFile( self, filePath):
		"""
			Parses the output file from the evolution process to extract 
			info about the individuals and their fitness value
		"""
		print 'Parsing...'
		
		# Open the file and read the contents
		file = open( filePath, 'r')
		fileContents = file.read();
		file.close()
		
		# Parse the xml data
		xmlfile = parseString( fileContents)
		
		# Getting population data:
		# ---------------------------------------------------------------------------------------------
		xmlPopulation = xmlfile.getElementsByTagName('Deme')[0]
		
		# Create new individuals list:
		self.individuals = []
		
		# Load the hall of fame individuals
		self.individuals.append( Individual( 'HallOfFame', xmlPopulation.getElementsByTagName('Individual')[0] ))

		# Load the population individuals
		for xmlIndividual in xmlPopulation.getElementsByTagName('Individual')[1:]:
			self.individuals.append( Individual( 'Individual'+ str(len(self.individuals)), xmlIndividual))

		# Set the info about the loaded individuals on listBox
		self.listBoxIndividuals.Set( [ str(i) for i in self.individuals] )		
		
		# Getting scene file / log file filepath
		# ----------------------------------------------------------------------------------------------
		xmlSceneFile = xmlfile.getElementsByTagName('Registry')[0]
		found = False
		for entry in xmlSceneFile.getElementsByTagName( 'Entry'):
			if entry.getAttribute( 'key' ) == 'robot.simulationfile':
				self.robotSceneFile = entry.childNodes[0].data
				#print self.robotSceneFile
				if found:
					break
				else:
					found = True
				
			if entry.getAttribute( 'key') == 'log.filename':
				self.logFile = entry.childNodes[0].data
				
				if found:
					break
				else:
					found = True
				
	
if __name__ == '__main__':
	app = wx.App()
	MainWin(None)
	app.MainLoop()
