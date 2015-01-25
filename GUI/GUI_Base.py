# Rensselaer Motorsports 2014

# Author : Mitchell Mellone
# Version : 0.1.3
# Most Recent Edits : 12-12-14
# Description : Base class for a GUI using the pyQt library that will display
# information from the sensors on the car in a clear and readable way

import sys
from PyQt4 import QtGui, QtCore
import numpy as np
import pyqtgraph as pg

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
        self.show()

#This function creates a widget containing 2 plots with random numbers
def basicPlotWidget(mw):
    cw = QtGui.QWidget()
    mw.setCentralWidget(cw)
    l = QtGui.QVBoxLayout()
    cw.setLayout(l)

    pw = pg.PlotWidget(name='Plot1')
    l.addWidget(pw)
    pw2 = pg.PlotWidget(name='Plot2')
    l.addWidget(pw2)

    ## Create an empty plot curve to be filled later, set its pen
    p1 = pw.plot()
    p1.setPen((200,200,100))

    ## Add in some extra graphics
    rect = QtGui.QGraphicsRectItem(QtCore.QRectF(0, 0, 1, 5e-11))
    rect.setPen(QtGui.QPen(QtGui.QColor(100, 200, 100)))
    pw.addItem(rect)

    pw.setLabel('left', 'Value', units='V')
    pw.setLabel('bottom', 'Time', units='s')
    pw.setXRange(0, 2)
    pw.setYRange(0, 1e-10)

    yd, xd = rand(10000)
    p1.setData(y=yd, x=xd)

def scatterPlot(mw):
    cw = QtGui.QWidget()
    mw.setCentralWidget(cw)
    l = QtGui.QVBoxLayout()
    cw.setLayout(l)

    sp = pg.ScatterPlotWidget()
    l.addWidget(sp)

    x = np.array([(1.0, 2), (3.0, 4)], dtype=[('x', float), ('y', int)])
    sp.setData(x)

#Creates a set of random numbers for help with testing
def rand(n):
    data = np.random.random(n)
    data[int(n*0.1):int(n*0.13)] += .5
    data[int(n*0.18)] += 2
    data[int(n*0.1):int(n*0.13)] *= 5
    data[int(n*0.18)] *= 20
    data *= 1e-12
    return data, np.arange(n, n+len(data)) / float(n)

def main():
    app = QtGui.QApplication(sys.argv)
    mw = GUI_window()
    #basicPlotWidget(mw)
    scatterPlot(mw)
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
