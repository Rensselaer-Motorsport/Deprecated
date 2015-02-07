# Rensselaer Motorsports 2014

# Author : Mitchell Mellone
# Version : 0.2.0
# Most Recent Edits : 2-5-15
# Description : Base class for a GUI using the pyQt library that will display
# information from the sensors on the car in a clear and readable way

import sys
from PyQt4 import QtGui, QtCore
import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtGui
import pyqtgraph.console
from pyqtgraph.dockarea import *
import numpy as np

import database as db

class GUI_window(QtGui.QMainWindow):
    def __init__(self):
        super(GUI_window, self).__init__()
        self.initUI()
        # self.initGraphs()

    def initUI(self):
        #Exit action initialization
        exitAction = QtGui.QAction(QtGui.QIcon('logo.png'), '&Exit', self)
        exitAction.setShortcut('Ctrl+Q')
        exitAction.setStatusTip('Exit application')
        exitAction.triggered.connect(QtGui.qApp.quit)

        #Open action initialization
        #!!NOT FUNCTIONAL!!
        openAction = QtGui.QAction('&Open File', self)
        openAction.setShortcut('Ctrl+O')
        openAction.setStatusTip('Open a new file')

        #Save action initialization
        #!!NOT FUNCTIONAL!!
        saveAction = QtGui.QAction('&Save File', self)
        saveAction.setShortcut('Ctrl+S')
        saveAction.setStatusTip('Save the current file')

        #New action initialization
        #!!NOT FUNCTIONAL!!
        newAction = QtGui.QAction('&New File', self)
        newAction.setShortcut('Ctrl+N')
        newAction.setStatusTip('Create a new file')

        #Print action initialization
        #!!NOT FUNCTIONAL!!
        printAction = QtGui.QAction('&Print File', self)
        printAction.setShortcut('Ctrl+P')
        printAction.setStatusTip('Print the current file')

        #Close action initialization
        #!!NOT FUNCTIONAL!!
        closeAction = QtGui.QAction('&Close File', self)
        closeAction.setShortcut('Ctrl+C')
        closeAction.setStatusTip('Close the current file')

        #Status bar initialization
        self.statusBar().showMessage('Ready')

        #Tool bar initialization
        self.toolbar = self.addToolBar('Exit')
        self.toolbar.addAction(exitAction)

        #Menu bar initialization
        menubar = self.menuBar()
        fileMenu = menubar.addMenu('&File')
        fileMenu.addAction(newAction)
        fileMenu.addAction(openAction)
        fileMenu.addAction(saveAction)
        fileMenu.addAction(printAction)
        fileMenu.addAction(closeAction)
        fileMenu.addAction(exitAction)

        editMenu = menubar.addMenu('&Edit')
        toolsMenu = menubar.addMenu('&Tools')
        viewMenu = menubar.addMenu('&View')
        helpMenu = menubar.addMenu('&Help')

        self.setGeometry(300, 300, 500, 300)
        self.setWindowTitle('RM Sensor Logger')
        self.setWindowIcon(QtGui.QIcon('logo.png'))
        basicPlotWidget(self)
        self.show()

#This function creates a widget containing 2 plots with random numbers
def basicPlotWidget(win):
    area = DockArea()
    win.setCentralWidget(area)
    win.resize(1200,500)
    win.setWindowTitle('graph_test')

    d1 = Dock("Graph 1", size=(400, 500))
    d2 = Dock("Graph 2", size=(400, 500))
    d3 = Dock("Graph 3", size=(400, 500))
    area.addDock(d1, 'left')
    area.addDock(d2, 'right')
    area.addDock(d3, 'right')

    data = db.DataBase()
    data.parse_file('test_buffer.txt')

    times = data.get_elapsed_times()
    values = data.get_sensor_values('temperature')
    print(times)
    print(values)

    w1 = pg.PlotWidget(title="Temperature plot")
    w1.plot(times, values)
    d1.addWidget(w1)

    w2 = pg.PlotWidget(title="Oil Pressure plot")
    w2.plot(data.get_elapsed_times(), data.get_sensor_values('oil_pressure'))
    d2.addWidget(w2)

    w3 = pg.PlotWidget(title="Accelerometer plot")
    w3.plot(data.get_elapsed_times(), data.get_sensor_values('accelerometer'))
    d3.addWidget(w3)

def main():
    app = QtGui.QApplication(sys.argv)
    mw = GUI_window()
    #basicPlotWidget(mw)
    #scatterPlot(mw)
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
