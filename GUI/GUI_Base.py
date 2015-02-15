# Rensselaer Motorsports 2014

# Author : Mitchell Mellone
# Version : 0.3.1
# Most Recent Edits : 2-9-15
# Description : Base class for a GUI using the pyQt library that will display
# information from the sensors on the car in a clear and readable way

import sys
from PyQt4 import QtGui, QtCore
import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtGui
import pyqtgraph.console
from pyqtgraph.dockarea import *
import numpy as np
from PyQt4.Qt import *
import database as db

class GUI_window(QtGui.QMainWindow):
    def __init__(self):
        super(GUI_window, self).__init__()
        self.initUI()
        # self.initGraphs()
        self.popup_win = None
        self.data = db.DataBase()
        self.data.parse_file('test_buffer.txt')

    def initUI(self):
        #Exit action initialization
        exitAction = QtGui.QAction(QtGui.QIcon('exit.png'), '&Exit', self)
        exitAction.setShortcut('Ctrl+Q')
        exitAction.setStatusTip('Exit application')
        exitAction.triggered.connect(QtGui.qApp.quit)

        selectDataAction = QtGui.QAction('&Select Data', self)
        selectDataAction = QtGui.QAction(QtGui.QIcon('graph.png'), '&Select Data', self)
        selectDataAction.setShortcut('Ctrl+S')
        selectDataAction.setStatusTip('Select data to display with a graph')
        selectDataAction.triggered.connect(self.selectDataPopup)

        #Status bar initialization
        self.statusBar().showMessage('Ready')

        #Tool bar initialization
        self.toolbar = self.addToolBar('Exit')
        self.toolbar.addAction(exitAction)
        self.toolbar.addAction(selectDataAction)

        #Menu bar initialization
        menubar = self.menuBar()
        fileMenu = menubar.addMenu('&File')
        fileMenu.addAction(selectDataAction)
        fileMenu.addAction(exitAction)

        editMenu = menubar.addMenu('&Edit')
        toolsMenu = menubar.addMenu('&Tools')
        viewMenu = menubar.addMenu('&View')
        helpMenu = menubar.addMenu('&Help')

        self.setGeometry(300, 300, 500, 300)
        self.setWindowTitle('RM Sensor Logger')
        self.setWindowIcon(QtGui.QIcon('rmlogo.png'))
        #basicPlotWidget(self)
        self.show()

    def selectDataPopup(self):
        self.popup_win = DataSelect()
        self.popup_win.setGeometry(QRect(200, 200, 200, 100))
        btn = QPushButton('Select Data To Display', self.popup_win)
        btn.setGeometry(QRect(12, 50, 175, 40))
        self.connect(btn, SIGNAL("clicked()"), self.selectDataButton)
        self.popup_win.show()

    def selectDataButton(self):
        self.plot(self, self.popup_win.getState())
        self.popup_win.close()

    def plot(self, win, graph_title):
        window = pg.GraphicsWindow(title="Graphics window")
        window.resize(1000,600)
        pg.setConfigOptions(antialias=True)

        x = self.data.get_elapsed_times()
        y = self.data.get_sensor_values(str(graph_title))
        p1 = window.addPlot(title="This is a graph", x=x, y=y)
        updatePlot()
        
        # area = DockArea()
        # win.setCentralWidget(area)
        # win.resize(600,500)
        # win.setWindowTitle(graph_title)
        #
        # d1 = Dock(graph_title, size=(600, 500))
        # area.addDock(d1)
        #
        # times = self.data.get_elapsed_times()
        # values = self.data.get_sensor_values(str(graph_title))
        #
        # w1 = pg.PlotWidget(title=graph_title)
        # w1.plot(times, values)
        # d1.addWidget(w1)

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

    w1 = pg.PlotWidget(title="Temperature plot")
    w1.plot(times, values)
    d1.addWidget(w1)

    w2 = pg.PlotWidget(title="Oil Pressure plot")
    w2.plot(data.get_elapsed_times(), data.get_sensor_values('oil_pressure'))
    d2.addWidget(w2)

    w3 = pg.PlotWidget(title="Accelerometer plot")
    w3.plot(data.get_elapsed_times(), data.get_sensor_values('accelerometer'))
    d3.addWidget(w3)

class DataSelect(QWidget):
    def __init__(self):
        QWidget.__init__(self)
        options = ['temperature', 'oil_pressure', 'accelerometer']
        self.dropdown_box = QtGui.QComboBox(self)
        self.dropdown_box.addItems(options)
        self.dropdown_box.setMinimumWidth(150)
        self.dropdown_box.move(25, 10)
        self.dropdown_box.show()

    def getState(self):
        return self.dropdown_box.currentText()

def main():
    app = QtGui.QApplication(sys.argv)
    mw = GUI_window()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
