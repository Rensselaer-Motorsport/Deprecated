import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtGui
import pyqtgraph.console
import numpy as np
import DataBase as db

from pyqtgraph.dockarea import *

app = QtGui.QApplication([])
win = QtGui.QMainWindow()
area = DockArea()
win.setCentralWidget(area)
win.resize(1000,500)
win.setWindowTitle('graph_test')

d1 = Dock("Graph 1", size=(500, 500))
d2 = Dock("Graph 2", size=(500, 500))
area.addDock(d1, 'left')
area.addDock(d2, 'right')

data = db.DataBase()
data.parse_file('')

w1 = pg.PlotWidget(title="Dock 1 plot")
w1.plot((1, 2, 3, 4, 5, 6), (6, 5, 4, 3, 2, 1))
d1.addWidget(w1)

w2 = pg.PlotWidget(title="Dock 2 plot")
w2.plot((1, 2, 3, 4, 5, 6), (1, 2, 3, 4, 5, 6))
d2.addWidget(w2)
win.show()

if __name__ == '__main__':
    import sys
    if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
        QtGui.QApplication.instance().exec_()
