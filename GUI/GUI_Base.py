# Rensselaer Motorsports 2014

# Author : Mitchell Mellone
# Version : 0.1.0
# Most Recent Edits : 12-12-14
# Description : Base class for a GUI using the pyQt library that will display
# information from the sensors on the car in a clear and readable way

import sys
from PyQt4 import QtGui

class GUI_window(QtGui.QWidget):
    def __init__(self):
        super(GUI_window, self).__init__()
        self.initUI()

    def initUI(self):
        self.setGeometry(300, 300, 250, 150)
        self.setWindowTitle('RM Sensor Logger')
        self.setWindowIcon(QtGui.QIcon('logo.png'))
        self.show()

def main():
    app = QtGui.QApplication(sys.argv)
    w = GUI_window()
    sys.exit(app.exec_())

if __name__ == '__main__':
    main()
