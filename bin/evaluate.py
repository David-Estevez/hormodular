"""
	Evaluate
	
	Evaluates an individual based on the milestone file
	
	Part of the hormodular project
	
"""
from __future__ import division
import wx

__author__ = 'David Estevez-Fernandez'
__license__ = 'GPLv3'


class MainWin( wx.Frame):
	
	def __init__( self, parent):
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
		
		#Textbox to put the filepath
		self.fileBox = wx.TextCtrl( self.panel, pos=( 10, 10), size=( 400-10-100-10, 25))
		
		# Button for loading the file
		self.loadButton = wx.Button( self.panel, label='Load', pos=(400-10-100, 10), size=( 100, 25))
		self.loadButton.Bind( wx.EVT_BUTTON, self.loadFile)
		
		# Listbox for listing the individuals
		self.listBoxIndividuals = wx.ListBox( self.panel, pos=(10, 10+25+10), size=(400-10-10, 200))
		self.listBoxIndividuals.Append("Individual #1")

	def loadFile(self, e):
		print 'Loading things...'
		
if __name__ == '__main__':
	app = wx.App()
	MainWin(None)
	app.MainLoop()
