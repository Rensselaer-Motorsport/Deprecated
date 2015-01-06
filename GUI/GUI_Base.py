# Rensselaer Motorsports 2014

# Author : Mitchell Mellone
# Version : 0.1.2
# Most Recent Edits : 12-12-14
# Description : Base class for a GUI using the pyQt library that will display
# information from the sensors on the car in a clear and readable way

import sys
from PyQt4 import QtGui

class GUI_window(QtGui.QMainWindow):
    def __init__(self):
        super(GUI_window, self).__init__()
        self.initUI()

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

def main():
    app = QtGui.QApplication(sys.argv)
    w = GUI_window()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
