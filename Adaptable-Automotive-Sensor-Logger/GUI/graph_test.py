import pyqtgraph as pg
from pyqtgraph.Qt import QtCore, QtGui
import pyqtgraph.console
import numpy as np
import database as db

from pyqtgraph.dockarea import *

app = QtGui.QApplication([])
win = QtGui.QMainWindow()
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

win.show()

if __name__ == '__main__':
    import sys
    if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
        QtGui.QApplication.instance().exec_()
