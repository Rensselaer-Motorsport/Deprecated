#database_test.py

import database as db

ds = db.DataBase()

ds.parse_file('bufferParseTest2.txt')
print ds.get_elapsed_times()
print ds.get_sensor_values('tire_temp4')
