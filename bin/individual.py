"""
	Individual - Individual coming from the evolution process
	
	Part of the hormodular project
	
"""

__author__ = 'David Estevez-Fernandez'
__license__ = 'GPLv3'

class Individual:
	"""
		Represents an individual coming from the evolution process
	"""
	
	def __init__( self, name, xml_description):
		"""
			Extracts the info of an individual from a xml description
			and stores the information in this class
		"""
		# Basic info:
		self.name = name
		try:
			self.generation = int(xml_description.getAttribute('gen'))
		except ValueError:
			self.generation = -1
			
		self.fitnessMax = float( xml_description.getElementsByTagName('FitnessMax')[0].getAttribute('value') )
		
		# Motion-related info ( amplitude, offset, phase)
		self.size = int(xml_description.getElementsByTagName('FloatingPoint')[0].getAttribute('size') )
		
		self.amplitudes = []
		self.offsets = []
		self.phases = []
		
		xmlMotionInfo = xml_description.getElementsByTagName('FloatingPoint')

		try:
			amplitude_str = xmlMotionInfo[0].childNodes[0].data
			offset_str = xmlMotionInfo[1].childNodes[0].data
			phase_str = xmlMotionInfo[2].childNodes[0].data
		except Exception, e:
			print str(e)
			print "Bad data from file. Exiting..."
			exit(-1)
				
		self.amplitudes = [ float(i) for i in amplitude_str.strip().split('\t') ]
		self.offsets = [ float(i) for i in offset_str.strip().split('\t') ]
		self.phases = [ float(i) for i in phase_str.strip().split('\t') ]

		
	def __str__( self):
		"""
			Return the main characteristics of the individual in a brief string
		"""
		return self.name + ', gen: ' + str( self.generation) + ', fitness: ' + str( self.fitnessMax)
	
	def generateGaitTable( self):
		"""
			Generates a string containing the gait table info of the current individual
		"""
		return_string =  '# Gait Table created by Hormodular [https://github.com/David-Estevez/hormodular.git]\n'
		return_string += '# name: gaitTable\n'
		return_string += '# type: matrix\n'
		return_string += '# rows: ' + str(self.size) + '\n'
		return_string += '# columns: 3\n'
		
		individual_strings = list()
		
		for i in range(0, self.size):
			return_string += ' '.join( str(j) for j in [self.amplitudes[i], self.offsets[i], self.phases[i] ]) + '\n'
			
		
		return return_string
