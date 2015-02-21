# Rensselaer Motorsports 2014

# Author : Mitchell Mellone
# Version : 0.4.0.5
# Most Recent Edits : 2-21-15
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
        self.area = DockArea()
        self.setCentralWidget(self.area)
        self.popup_win = None
        self.data = db.DataBase()
        self.figures = {}
        self.current_plots = []
        self.data.parse_file('test_buffer.txt')
        self.plot_docks = []
        self.table_docks = []

    def initUI(self):
        #Exit action initialization
        exitAction = QtGui.QAction(QtGui.QIcon('exit.png'), '&Exit', self)
        exitAction.setShortcut('Ctrl+Q')
        exitAction.setStatusTip('Exit application.')
        exitAction.triggered.connect(QtGui.qApp.quit)

        addSensorData = QtGui.QAction(QtGui.QIcon('green+.png'), '&Add Graph', self)
        addSensorData.setShortcut('Ctrl+A')
        addSensorData.setStatusTip('Add a plot and table of data from a sensor.')
        addSensorData.triggered.connect(self.selectDataPopup)

        #Status bar initialization
        self.statusBar().showMessage('Ready')

        #Tool bar initialization
        self.toolbar = self.addToolBar('Exit')
        self.toolbar.addAction(exitAction)
        self.toolbar.addAction(addSensorData)

        #Menu bar initialization
        menubar = self.menuBar()
        self.file_menu = menubar.addMenu('&File')
        self.file_menu.addAction(addSensorData)
        self.file_menu.addAction(exitAction)

        self.edit_menu = menubar.addMenu('&Edit')
        self.tools_menu = menubar.addMenu('&Tools')
        self.view_menu = menubar.addMenu('&View')
        self.help_menu = menubar.addMenu('&Help')

        self.setGeometry(300, 300, 500, 300)
        self.setWindowTitle('RM Data Analysis')
        self.setWindowIcon(QtGui.QIcon('rmlogo.png'))
        self.show()

#----------------------------------------------------------------------------------------------------------------------------------------------------
#------------------------------------------------------------ADD PLOTS AND TABLES-------------------------------------------------------------
#----------------------------------------------------------------------------------------------------------------------------------------------------
    '''
    selectDataPopup creates a pop up that prompts the user on what data to display
    '''
    def selectDataPopup(self):
        self.popup_win = DataSelect()
        self.popup_win.setGeometry(QRect(200, 200, 200, 100))
        btn = QPushButton('Select Data To Display', self.popup_win)
        btn.setGeometry(QRect(12, 50, 175, 40))
        self.connect(btn, SIGNAL("clicked()"), self.selectDataButton)
        self.popup_win.show()

    def selectDataButton(self):
        if len(self.current_plots) == 0:
            self.initPlotTools()
        self.plot(self, self.popup_win.getState())
        self.popup_win.close()

    def plot(self, win, graph_title):
        win.resize(850,500)

        d1 = Dock(graph_title, size=(600, 500), closable=True)
        self.area.addDock(d1, 'above')
        # if len(self.plot_docks) > 0:
        #     self.area.moveDock(d1, "above", self.plot_docks[0])
        times = self.data.get_elapsed_times()
        values = self.data.get_sensor_values(str(graph_title))
        self.figures[graph_title + "plot"] = pg.PlotWidget(title=graph_title)
        self.figures[graph_title + "plot"].plot(times, values)
        ymin = self.data.get_min_sensor_value(str(graph_title))
        if ymin > 0:
            ymin = 0
        ymax = self.data.get_max_sensor_value(str(graph_title))
        if ymax < 0:
            ymax = 0
        xpadding = times[len(times)-1] * 0.1
        ypadding = abs(ymax-ymin) * 0.1
        tmax = self.data.get_max_sensor_value('time')
        self.figures[graph_title + "plot"].setLimits(xMin=0-xpadding, xMax=times[len(times)-1]+xpadding, yMin=ymin-ypadding, yMax=ymax+ypadding)
        self.figures[graph_title + "plot"].setRange(xRange=(0, tmax), yRange=(ymin, ymax), padding=0.0)
        self.figures[graph_title + "plot"].showGrid(x=True, y=True, alpha = 0.5)
        self.current_plots.append((str(graph_title), self.figures[graph_title + "plot"]))
        d1.addWidget(self.figures[graph_title + "plot"])
        self.plot_docks.append(d1)

        d2 = Dock(graph_title + " table", size=(250, 500), closable=True)
        self.area.addDock(d2, 'above')
        if len(self.table_docks) > 0:
            self.area.moveDock(d2, "above", self.table_docks[0])
        self.figures[graph_title + "table"] = QtGui.QTableWidget(len(times), 2)
        for i, (t, v) in enumerate(zip(times, values)):
            newTimeItem = QTableWidgetItem(str(t))
            newValueItem = QTableWidgetItem(str(v))
            self.figures[graph_title + "table"].setItem(i, 0, newTimeItem)
            self.figures[graph_title + "table"].setItem(i, 1, newValueItem)
        headers = ['Time', graph_title]
        self.figures[graph_title + "table"].setHorizontalHeaderLabels(headers)
        d2.addWidget(self.figures[graph_title + "table"])
        self.table_docks.append(d2)

#----------------------------------------------------------------------------------------------------------------------------------------------------
#-------------------------------------------------------------------VIEW FUNCTIONS-------------------------------------------------------------------
#----------------------------------------------------------------------------------------------------------------------------------------------------
    '''
    initPlotTools will create 5 actions to adust the view range of a graph and set them in the view_menu
    The 5 actions are:
        Set View Range:  Allows the user to select the min and max x and y values on the plot window (no padding)
        Fit Data:        Automatically sets the view range to the min and max x and y points in the data (with padding)
        Fit Data Height: Automatically sets the min and max y values to the min and max y points in the data (with padding)
        Fit Data Width:  Automatically sets the min and max x values to the min and max x points in the data (with padding)
        Default View:    Sets view to see all of the data points as well as the x and y axis'
    '''
    def initPlotTools(self):
        #creates and adds setViewRange
        setViewRangeAction = QtGui.QAction('&Set View Range', self) #initializes action
        setViewRangeAction.setStatusTip('Set the x and y view range on desired plot.') #sets tip to show in status bar and when hovering
        setViewRangeAction.triggered.connect(self.setViewRangePopup) #calls function that creates popup when action is selected
        self.view_menu.addAction(setViewRangeAction) #adds action to the view menu

        #creates and adds fitData
        fitDataAction = QtGui.QAction('&Fit Data', self)
        fitDataAction.setStatusTip('Zooms to show all the data.')
        fitDataAction.triggered.connect(self.fitDataPopup)
        self.view_menu.addAction(fitDataAction)

        #creates and adds fitDataHeight
        fitDataHeightAction = QtGui.QAction('&Fit Data Height', self)
        fitDataHeightAction.setStatusTip('Zooms the y-axis to fit the data.')
        fitDataHeightAction.triggered.connect(self.fitDataHeightPopup)
        self.view_menu.addAction(fitDataHeightAction)

        #creates and adds fitDataWidth
        fitDataWidthAction = QtGui.QAction('&Fit Data Width', self)
        fitDataWidthAction.setStatusTip('Zooms the x-axis to fit the data.')
        fitDataWidthAction.triggered.connect(self.fitDataWidthPopup)
        self.view_menu.addAction(fitDataWidthAction)

        #creates and adds defaultView
        defaultViewAction = QtGui.QAction('&Default View', self)
        defaultViewAction.setStatusTip('Returns to the default view, shows all data and x- and y-axis.')
        defaultViewAction.triggered.connect(self.defaultViewPopup)
        self.view_menu.addAction(defaultViewAction)

    '''
    setViewRangePopup initializes the popup window that allows the user to set the view range
    It uses the RangeSelect class (declared and initialized below)
    The button added takes the data written in the pop-up's text boxes resizes the plot view range accordingly
    '''
    def setViewRangePopup(self):
        self.popup_win = RangeSelect(self, self.current_plots) #initialize the popup window
        self.popup_win.setGeometry(QRect(200, 200, 350, 200)) #set the popup's position (first 2 parameters), and width/height (second 2 parameters)
        btn = QPushButton('Select Range', self.popup_win) #declare and initialize the select button
        btn.setGeometry(QRect(87, 150, 175, 40)) #set the button's position and width/height
        self.connect(btn, SIGNAL("clicked()"), self.setViewRangeButton) #call setViewRangeButton function when the button is pressed
        self.popup_win.show() #show the popup window on screen

    #setViewRangeButton is run when button is pressed
    def setViewRangeButton(self):
        plotName = self.popup_win.getPlotName() #get the plot we are changing
        newXRange = (self.popup_win.getXMin(), self.popup_win.getXMax()) #get new x range
        newYRange = (self.popup_win.getYMin(), self.popup_win.getYMax()) #get new y range
        self.figures[plotName + "plot"].setRange(xRange=newXRange, yRange=newYRange, padding=0.0) #change the view range in the appropriate plot
        self.popup_win.close() #close the popup window after changes are made

    '''
    The following functions perform the other automatic range select features described above
    They all behave in similar ways to the setViewRange functions
    '''
    #controls fit data
    def fitDataPopup(self):
        self.popup_win = SelectPlot(self, self.current_plots)
        self.popup_win.setGeometry(QRect(200, 200, 200, 100))
        btn = QPushButton('Fit Data', self.popup_win)
        btn.setGeometry(QRect(25, 40, 150, 40))
        self.connect(btn, SIGNAL("clicked()"), self.fitDataButton)
        self.popup_win.show()
    def fitDataButton(self):
        plotName = self.popup_win.getPlotName()
        ymin = self.data.get_min_sensor_value(str(plotName))
        ymax = self.data.get_max_sensor_value(str(plotName))
        tmax = self.data.get_max_sensor_value('time')
        self.figures[plotName + "plot"].setRange(xRange=(0, tmax), yRange=(ymin, ymax))
        self.popup_win.close()

    #controls fit data height
    def fitDataHeightPopup(self):
        self.popup_win = SelectPlot(self, self.current_plots)
        self.popup_win.setGeometry(QRect(200, 200, 200, 100))
        btn = QPushButton('Fit Data Height', self.popup_win)
        btn.setGeometry(QRect(25, 40, 150, 40))
        self.connect(btn, SIGNAL("clicked()"), self.fitDataHeightButton)
        self.popup_win.show()
    def fitDataHeightButton(self):
        plotName = self.popup_win.getPlotName()
        ymin = self.data.get_min_sensor_value(str(plotName))
        ymax = self.data.get_max_sensor_value(str(plotName))
        self.figures[plotName + "plot"].setYRange(min=ymin, max=ymax)
        self.popup_win.close()

    #controls fit data width
    def fitDataWidthPopup(self):
        self.popup_win = SelectPlot(self, self.current_plots)
        self.popup_win.setGeometry(QRect(200, 200, 200, 100))
        btn = QPushButton('Fit Data Width', self.popup_win)
        btn.setGeometry(QRect(25, 40, 150, 40))
        self.connect(btn, SIGNAL("clicked()"), self.fitDataWidthButton)
        self.popup_win.show()
    def fitDataWidthButton(self):
        plotName = self.popup_win.getPlotName()
        tmax = self.data.get_max_sensor_value('time')
        self.figures[plotName + "plot"].setXRange(min=0, max=tmax)
        self.popup_win.close()

    #controls default view
    def defaultViewPopup(self):
        self.popup_win = SelectPlot(self, self.current_plots)
        self.popup_win.setGeometry(QRect(200, 200, 200, 100))
        btn = QPushButton('Set to Default View', self.popup_win)
        btn.setGeometry(QRect(25, 40, 150, 40))
        self.connect(btn, SIGNAL("clicked()"), self.defaultViewButton)
        self.popup_win.show()
    def defaultViewButton(self):
        plotName = self.popup_win.getPlotName()
        ymin = self.data.get_min_sensor_value(str(plotName))
        if ymin > 0:
            ymin = 0
        ymax = self.data.get_max_sensor_value(str(plotName))
        if ymax < 0:
            ymax = 0
        tmax = self.data.get_max_sensor_value('time')
        self.figures[plotName + "plot"].setRange(xRange=(0, tmax), yRange=(ymin, ymax))
        self.popup_win.close()

#----------------------------------------------------------------------------------------------------------------------------------------------------
#-------------------------------------------------------------Classes for Popup Windows--------------------------------------------------------------
#----------------------------------------------------------------------------------------------------------------------------------------------------
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
    #win is the main window, current_plots are the plots currently displayed in the main window
    def __init__(self, win, current_plots):
        QWidget.__init__(self) #calls parent class constructor
        self.options = [] #list of choices for dropdown box
        self.plot_items = [] #holds the actual plot_items currently displayed
        for plots in current_plots:
            self.options.append(plots[0])
            self.plot_items.append(plots[1])

        #initialize the dropdown box (QComboBox), add names of current plots (options), set size/position
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

    #return what is currently in the dropdown_box
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

#Uses a dropdown box to prompt user to select a plot that is currently displayed
class SelectPlot(QWidget):
    #win is the main window, current_plots are the plots currently displayed in the main window
    def __init__(self, win, current_plots):
        QWidget.__init__(self) #calls parent class constructor
        self.options = [] #list of choices for dropdown box
        self.plot_items = [] #holds the actual plot_items currently displayed
        for plots in current_plots:
            self.options.append(plots[0])
            self.plot_items.append(plots[1])

        #initialize the dropdown box (QComboBox), add names of current plots (options), set size/position
        self.dropdown_box = QtGui.QComboBox(self)
        self.dropdown_box.addItems(self.options)
        self.dropdown_box.setMinimumWidth(150)
        self.dropdown_box.move(25, 10)
        self.dropdown_box.show()

    #return what is currently in the dropdown_box
    def getPlotName(self):
        return self.dropdown_box.currentText()

def main():
    app = QtGui.QApplication(sys.argv)
    mw = GUI_window()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
