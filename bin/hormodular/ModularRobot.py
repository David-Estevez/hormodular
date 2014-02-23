"""
	ModularRobot
	
	Class to represent a hormodular Modular Robot

"""

__author__ = 'David Estevez Fernandez'
__license__ = 'GPLv3'

class ModularRobot:
	"""
		Data container for hormodular Modular Robot
	"""
	
	def __init__(self, name , nModules, runTime, timeStep, simulationFile = '',  amplitudes = [], offsets = [],  phases = [], generation = 0, fitness = 0, problemId = '' ):
		self.name = name
		self.nModules = nModules;
		self.runTime = runTime;
		self.timeStep = timeStep;
		self.simulationFile = simulationFile
		
		if not amplitudes:
			self.amplitudes = [ 0 for j in range(0, nModules) ]
		else:
			self.amplitudes = amplitudes
		
		if not offsets:
			self.offsets = [ 0 for j in range(0, nModules) ]
		else:
			self.offsets = offsets
			
		if not phases:
			self.phases = [ 0 for j in range(0, nModules) ]
		else:
			self.phases = phases
			
		self.generation = generation
		self.fitness = fitness
		self.problemId = problemId

	def __str__(self):
		description = 'ModularRobot {\n'
		description += '\tName: ' + self.name + '\n'
		description += '\tnModules: ' + str( self.nModules) + '\n'
		description += '\tRun Time: ' + str( self.runTime ) + '\n'
		description += '\tTime step: ' + str( self.timeStep) + '\n'
		description += '\tSimulation File: ' + self.simulationFile + '\n}'
		
		return description
