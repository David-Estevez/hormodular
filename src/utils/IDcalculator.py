#!/bin/python

import sys

connector_id_dict = { 'F':0, 'R':1, 'B':2, 'L':3 }
angle_id_dict = { '0':0, '90':1, '180':2, '270':3, 0:0, 90:1, 180:2, 270:3, 1:1, 2:2, 3:3, '1':1, '2':2, '3':3 }
	
def main(description_string):
	print "ID: " + str(calculateID(description_string)) + '\n'
	
	

def calculateID( description_string ):
	_id = 0
	tokens = [ i.strip() for i in description_string[1:-1].split(',')]
	tokens_with_hierarchy = []
	
	level = 0
	for token in tokens:
		if '(' in token:
			_id += ( connector_id_dict[token.strip('(').strip()] * 1 * 17**level)
		elif ')' in token:
			_id += ( angle_id_dict[token.strip(')').strip()] * 4 * 17**level)
			level += 1
		elif 'X' in token or 'x' in token:
			_id += (16 * 17**level)
			level +=1
			
	return _id
	
	
if __name__ == '__main__':
	if len(sys.argv) == 2:
		main(sys.argv[1])
	else:
		print "Usage: IDcalculator <description string>\n"
