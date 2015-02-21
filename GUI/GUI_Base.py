# Rensselaer Motorsports 2014

# Author : Mitchell Mellone
# Version : 0.4.0
# Most Recent Edits : 2-20-15
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
        self.area = DockArea()
        self.setCentralWidget(self.area)
        self.popup_win = None
        self.data = db.DataBase()
        self.data_elements = {}
        self.current_plots = []
        self.data.parse_file('test_buffer.txt')


    def initUI(self):
        #Exit action initialization
        exitAction = QtGui.QAction(QtGui.QIcon('exit.png'), '&Exit', self)
        exitAction.setShortcut('Ctrl+Q')
        exitAction.setStatusTip('Exit application')
        exitAction.triggered.connect(QtGui.qApp.quit)

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
        self.setWindowTitle('RM Data Analysis')
        self.setWindowIcon(QtGui.QIcon('rmlogo.png'))
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
        self.initPlotTools()
        self.popup_win.close()

    def plot(self, win, graph_title):
        win.resize(850,500)

        d1 = Dock(graph_title, size=(600, 500))
        self.area.addDock(d1, 'left')
        times = self.data.get_elapsed_times()
        values = self.data.get_sensor_values(str(graph_title))
        self.data_elements[graph_title + "plot"] = pg.PlotWidget(title=graph_title)
        self.data_elements[graph_title + "plot"].plot(times, values)
        ymin = min(values)
        if ymin > 0:
            ymin = 0
        ymax = max(values)
        if ymax < 0:
            ymax =0
        xpadding = times[len(times)-1] * 0.1
        ypadding = abs(ymax-ymin) * 0.1
        self.data_elements[graph_title + "plot"].setLimits(xMin=0-xpadding, xMax=times[len(times)-1]+xpadding, yMin=ymin-ypadding, yMax=ymax+ypadding)
        self.data_elements[graph_title + "plot"].setRange(xRange=(0, times[len(times)-1]), yRange=(ymin, ymax), padding=0.0)
        self.data_elements[graph_title + "plot"].showGrid(x=True, y=True, alpha = 0.5)
        self.current_plots.append((str(graph_title), self.data_elements[graph_title + "plot"]))
        d1.addWidget(self.data_elements[graph_title + "plot"])

        d2 = Dock(graph_title + " table", size=(250, 500))
        self.area.addDock(d2, 'right')
        self.data_elements[graph_title + "table"] = QtGui.QTableWidget(len(times), 2)
        for i, (t, v) in enumerate(zip(times, values)):
            newTimeItem = QTableWidgetItem(str(t))
            newValueItem = QTableWidgetItem(str(v))
            self.data_elements[graph_title + "table"].setItem(i, 0, newTimeItem)
            self.data_elements[graph_title + "table"].setItem(i, 1, newValueItem)
        headers = ['Time', graph_title]
        self.data_elements[graph_title + "table"].setHorizontalHeaderLabels(headers)
        d2.addWidget(self.data_elements[graph_title + "table"])

    def initPlotTools(self):
        setRangeAction = QtGui.QAction(QtGui.QIcon('graph.png'), '&Set Range', self)
        setRangeAction.setStatusTip('Set the range to display in the graph')
        setRangeAction.triggered.connect(self.initPlotToolsPopup)
        self.toolbar.addAction(setRangeAction)

    def initPlotToolsPopup(self):
        self.popup_win = RangeSelect(self, self.current_plots)
        self.popup_win.setGeometry(QRect(200, 200, 350, 200))
        btn = QPushButton('Select Range', self.popup_win)
        btn.setGeometry(QRect(87, 150, 175, 40))
        self.connect(btn, SIGNAL("clicked()"), self.initPlotToolsButton)
        self.popup_win.show()

    def initPlotToolsButton(self):
        plotName = self.popup_win.getPlotName()
        newXRange = (self.popup_win.getXMin(), self.popup_win.getXMax())
        newYRange = (self.popup_win.getYMin(), self.popup_win.getYMax())
        self.data_elements[plotName + "plot"].setRange(xRange=newXRange, yRange=newYRange, padding=0.0)
        self.popup_win.close()

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

class RangeSelect(QWidget):
    def __init__(self, win, current_plots):
        QWidget.__init__(self)
        self.options = []
        self.plot_items = []
        for plots in current_plots:
            self.options.append(plots[0])
            self.plot_items.append(plots[1])

        self.dropdown_box = QtGui.QComboBox(self)
        self.dropdown_box.addItems(self.options)
        self.dropdown_box.setMinimumWidth(150)
        self.dropdown_box.move(100, 10)
        self.dropdown_box.show()

        self.xminLabel = QtGui.QLabel("min x", self)
        self.xminLabel.move(25, 50)
        self.xmin = QtGui.QLineEdit(self)
        self.xmin.move(75, 50)

        self.xmaxLabel = QtGui.QLabel("max x", self)
        self.xmaxLabel.move(200, 50)
        self.xmax = QtGui.QLineEdit(self)
        self.xmax.move(250, 50)

        self.yminLabel = QtGui.QLabel("min y", self)
        self.yminLabel.move(25, 100)
        self.ymin = QtGui.QLineEdit(self)
        self.ymin.move(75, 100)

        self.ymaxLabel = QtGui.QLabel("max y", self)
        self.ymaxLabel.move(200, 100)
        self.ymax = QtGui.QLineEdit(self)
        self.ymax.move(250, 100)

        self.xmin.setMaxLength(8)
        self.xmin.setMaximumWidth(60)
        self.xmax.setMaxLength(8)
        self.xmax.setMaximumWidth(60)
        self.ymin.setMaxLength(8)
        self.ymin.setMaximumWidth(60)
        self.ymax.setMaxLength(8)
        self.ymax.setMaximumWidth(60)

        self.dropdown_box.connect(self.dropdown_box, SIGNAL("currentIndexChanged(int)"), self.updateLineEdits)
        self.updateLineEdits()

        self.xmin.show()
        self.xmax.show()
        self.ymin.show()
        self.ymax.show()
        self.xminLabel.show()
        self.xmaxLabel.show()
        self.yminLabel.show()
        self.ymaxLabel.show()

    def updateLineEdits(self):
        i = self.options.index(self.dropdown_box.currentText())
        currRange = self.plot_items[i].viewRange() #returns current views visible range in format [[xmin, xmax], [ymin, ymax]]
        self.xmin.setText(str(currRange[0][0]))
        self.xmax.setText(str(currRange[0][1]))
        self.ymin.setText(str(currRange[1][0]))
        self.ymax.setText(str(currRange[1][1]))

    def getPlotName(self):
        return self.dropdown_box.currentText()

    def getXMin(self):
        return float(self.xmin.text())

    def getXMax(self):
        return float(self.xmax.text())

    def getYMin(self):
        return float(self.ymin.text())

    def getYMax(self):
        return float(self.ymax.text())

def main():
    app = QtGui.QApplication(sys.argv)
    mw = GUI_window()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
