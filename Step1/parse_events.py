import pandas as pd # type: ignore
import datetime

f = open("events.txt")
lines = f.readlines()
data = {}
keys = ["event_type", "scan_code", "name", "time", "device", "is_keypad"]
for key in keys:
    data[key] = []

# create a dictionary that holds all the values for each key
for line in lines:
    # remove the {}
    if line == "":
        break
    brackets_index = []
    new_line = line[1:line.find("}")]
    entries = new_line.split(",")
    for entry in entries:
        # find the key-value pair
        temp_key = entry.split(":")[0].strip()
        temp_val = entry.split(":")[1].strip()
        # removes the "" if present
        if temp_key.find('"') != -1:
            temp_key = temp_key[1:-1]
        if temp_val.find('"') != -1:
            temp_val = temp_val[1:-1]
        # turn vals into the right type
        if temp_val.isnumeric(): temp_val = int(temp_val)
        # in this case, it's a datetime, so we store the seconds
        elif temp_val.find(".") != -1: 
            temp_val = datetime.timedelta(seconds=float(temp_val)).seconds
        elif temp_val == "false": temp_val = False
        elif temp_val == "true": temp_val = True
        # add the val to the dataframe under the correct key 
        data[temp_key].append(temp_val)

df = pd.DataFrame(data)
print(df)