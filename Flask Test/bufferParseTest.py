#bufferParseTest.py

import sensor_buffer

sensorDict = sensor_buffer.SensorBuffer();

sensorDict.addSensor("accelerometer1")
sensorDict.addSensor("accelerometer2")
sensorDict.addSensor("accelerometer3")
sensorDict.addSensor("brake_temp1")
sensorDict.addSensor("brake_temp2")
sensorDict.addSensor("tire_temp1")
sensorDict.addSensor("tire_temp2")
sensorDict.addSensor("brake_temp3")
sensorDict.addSensor("brake_temp4")
sensorDict.addSensor("tire_temp3")
sensorDict.addSensor("tire_temp4")
sensorDict.addSensor("accelerometer4")

sensorDict.addSensorValue("accelerometer1", 1.1)
sensorDict.addSensorValue("accelerometer1", 1.2)
sensorDict.addSensorValue("accelerometer2", 2.1)
sensorDict.addSensorValue("accelerometer2", 2.2)
sensorDict.addSensorValue("accelerometer3", 3.1)
sensorDict.addSensorValue("accelerometer3", 3.2)
sensorDict.addSensorValue("accelerometer4", 4.1)
sensorDict.addSensorValue("accelerometer4", 4.2)
sensorDict.addSensorValue("tire_temp1", 0.111)
sensorDict.addSensorValue("tire_temp1", 0.112)
sensorDict.addSensorValue("tire_temp2", 0.121)
sensorDict.addSensorValue("tire_temp2", 0.122)
sensorDict.addSensorValue("tire_temp3", 131)
sensorDict.addSensorValue("tire_temp3", 132)
sensorDict.addSensorValue("tire_temp4", 141)
sensorDict.addSensorValue("tire_temp4", 142)
sensorDict.addSensorValue("brake_temp1", 11)
sensorDict.addSensorValue("brake_temp1", 120)
sensorDict.addSensorValue("brake_temp2", 21)
sensorDict.addSensorValue("brake_temp2", 22)
sensorDict.addSensorValue("brake_temp3", 31)
sensorDict.addSensorValue("brake_temp3", 32)
sensorDict.addSensorValue("brake_temp4", 41)
sensorDict.addSensorValue("brake_temp4", 42)

sensorDict.getSensors("bufferParseTest.txt")
sensorDict.getValues("bufferParseTest.txt")

sensorDict.addSensorValue("accelerometer1", 1.3)
sensorDict.addSensorValue("accelerometer2", 2.3)
sensorDict.addSensorValue("accelerometer3", 3.3)
sensorDict.addSensorValue("accelerometer4", 4.3)
sensorDict.addSensorValue("brake_temp1", 131)
sensorDict.addSensorValue("brake_temp2", 23)
sensorDict.addSensorValue("brake_temp3", 33)
sensorDict.addSensorValue("brake_temp4", 43)
sensorDict.addSensorValue("tire_temp1", 113)
sensorDict.addSensorValue("tire_temp2", 123)
sensorDict.addSensorValue("tire_temp3", 133)
sensorDict.addSensorValue("tire_temp4", 143)

sensorDict.getValues("bufferParseTest.txt")

sensorDict.addSensorValue("accelerometer1", 1.2)
sensorDict.addSensorValue("brake_temp1", 132)
sensorDict.getValues("bufferParseTest.txt")

sensorDict.addSensorValue("accelerometer1", 1.29)
sensorDict.addSensorValue("brake_temp1", 129)
sensorDict.getValues("bufferParseTest.txt")

sensorDict.addSensorValue("accelerometer1", 1.27)
sensorDict.addSensorValue("brake_temp1", 132)
sensorDict.getValues("bufferParseTest.txt")

sensorDict.addSensorValue("accelerometer1", 1.31)
sensorDict.addSensorValue("brake_temp1", 127)
sensorDict.getValues("bufferParseTest.txt")

sensorDict.addSensorValue("accelerometer1", 1.34)
sensorDict.addSensorValue("brake_temp1", 120)
sensorDict.getValues("bufferParseTest.txt")

sensorDict.addSensorValue("accelerometer1", 1.33)
sensorDict.addSensorValue("brake_temp1", 122)
sensorDict.getValues("bufferParseTest.txt")

sensorDict.addSensorValue("accelerometer1", 1.07)
sensorDict.addSensorValue("brake_temp1", 124)
sensorDict.getValues("bufferParseTest.txt")
