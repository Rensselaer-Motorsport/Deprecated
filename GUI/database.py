# Rensselaer Motorsports 2014/2015

# Author : Mitchell Mellone
# Version : 0.2.0
# Most Recent Edits : 12-12-14
# Description : A datastructure that will read sensor data from a text file generated
# from the sensor_buffer and hold it for display on the GUI

import numpy as np

class DataBase:
    def __init__(self):
        #The first entry in sensors will be a tuple of the elapsed time values (starting at 1)
        #After that each key is a sensor name, followed by the value of that sensor at the time
        #     time indicated in the same index in the elapsed time tuple
        self.sensors = {}
        self.sensors[time] = ()

        #the date and time will be the date and time of the first sensor reading
        self.date = "2000-01-31"
        self.time = "00:00:00.000000"


    def parse_file(self, file_name):
        #open the input file
        f = open(file_name, 'r')

        #read in the names of all the sensors and input into dictionary
        sensorLine = f.readline()
        sensorList = sensorLine.split()
        for sensor in sensorList:
            self.sensors[sensor] = ()

        #read in all sensor data
        prev_time = 0
        for line in f:
            valueList = line.split()
            if prev_time == 0:
                self.date = valueList[1]
                self.time = prev_time = valueList[2]
            self.sensors[time].append(elapsed_time(prev_time, valueList[2]))
            for i in range(2, len(valueList)):
                sensors[sensorList[i]].append(valueList[i])

    def elapsed_time(self, prev_time, current_time):
        prev_time_in_sec = float(prev_time[0:2])*3600 + float(prev_time[3:5])*60 + float(prev_time[6:])
        current_time_in_sec = float(current_time[0:2])*3600 + float(current_time[3:5])*60 + float(current_time[6:])
        return current_time_in_sec - elapsed_time_in_sec
