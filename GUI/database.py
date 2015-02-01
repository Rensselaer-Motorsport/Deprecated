# Rensselaer Motorsports 2014/2015

# Author : Mitchell Mellone
# Version : 0.4.0
# Most Recent Edits : 2/1/15
# Description : A datastructure that will read sensor data from a text file generated
# from the sensor_buffer and hold it for display on the GUI

class DataBase:
    def __init__(self):
        #The first entry in sensors will be a tuple of the elapsed time values (starting at 1)
        #After that each key is a sensor name, followed by the value of that sensor at the time
        #     time indicated in the same index in the elapsed time tuple
        self.sensors = {}
        self.sensors['time'] = ()

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
                self.date = valueList[0]
                self.time = prev_time = valueList[1]
            self.sensors['time'] += ((self.elapsed_time(prev_time, valueList[1])), )
            print self.sensors['time']
            prev_time = valueList[1]
            for i in range(2, len(valueList)):
                self.sensors[sensorList[i-2]] += ((valueList[i]), )

    def elapsed_time(self, prev_time, current_time):
        prev_time_in_sec = float(prev_time[0:2])*3600 + float(prev_time[3:5])*60 + float(prev_time[6:])
        current_time_in_sec = float(current_time[0:2])*3600 + float(current_time[3:5])*60 + float(current_time[6:])
        return current_time_in_sec - prev_time_in_sec

    def get_elapsed_times(self):
        return self.sensors['time']

    def get_sensor_values(self, sensor_name):
        return self.sensors[sensor_name]
