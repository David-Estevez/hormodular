"""
	EvolutionConfiguration

	Class to represent a hormodular Evolution configuration

"""

__author__ = 'David Estevez Fernandez'
__license__ = 'GPLv3'

import time as t

class EvolutionConfiguration:
	"""
		Data container for Evolution Configuration parameters
	"""
	
	def __init__( self, algorithm, mutation, crossover, populationSize, termination, timestamp = ''):
		"""
			algorithm : list containing the algorithm parameters:
				algoritm = [ "RouletteWheel", { "crxprob":0.5, "selpresure":10}]
				
			mutation: dict containing the mutation configuration:
				mutation = { "simple":0.05 }
				
			crossover: dict containing the crossover configuration:
				crossover = { "arithmetic":1 }
				
			termination: dict containing the termination criteria:
				termination = { "maxgen":50, "maxtime":1000 }
				
			timestamp: id of the problem, constructed from the current time
		"""
				
		self.algorithm = algorithm
		self.mutation = mutation
		self.crossover = crossover
		self.populationSize = populationSize
		self.termination = termination
		if timestamp == '':
			# Get timestamp
			currentTime = t.localtime()
			self.timestamp = '-'.join( [ str(currentTime[i]) for i in range(6) ])
		else:
			self.timestamp = timestamp

	def __str__(self):
		description = 'EvolutionConfiguration {\n'
		description += '\tAlgorithm: ' + str(self.algorithm) + '\n'
		description += '\tMutation: ' + str( self.mutation) + '\n'
		description += '\tCrossover: ' + str( self.crossover ) + '\n'
		description += '\tPopulation size: ' + str( self.populationSize) + '\n'
		description += '\tTermination criteria: ' + str(self.termination) + '\n' 
		description += '\tId: ' + str(self.timestamp) + '\n}'
		
		return description
