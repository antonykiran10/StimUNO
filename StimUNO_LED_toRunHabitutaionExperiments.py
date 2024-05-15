# Importing Libraries
import serial
from psychopy import visual, event
from psychopy.visual.windowwarp import Warper
import time as time

import time
import threading

def format_time(seconds):
    minutes, seconds = divmod(seconds, 60)
    return f"{int(minutes):02d}:{int(seconds):02d}"

def start_timer():
    start_time = time.time()
    while not exit_event.is_set():
        elapsed_time = time.time() - start_time
        formatted_time = format_time(elapsed_time)
        print(f"Elapsed Time: {formatted_time}", end="\r")
        time.sleep(0.1)  # Update every 0.1 seconds

exit_event = threading.Event()



# parameters
acclimatisation_time = 60# in seconds
num_of_dark_flashes = 60
darkflash_duration = 1 # in seconds
inter_stim_interval = 60 # in seconds

arduino = serial.Serial(port='COM12', baudrate=115200, timeout=.1)
p = 6.89


def driver(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    signal = arduino.readline()
    return signal

blah = 0
blah = input('Do you want to start the experiment (y/n):')
flag = 0
initial_time = time.time()

timer_thread = threading.Thread(target=start_timer)
timer_thread.start()

time.sleep(acclimatisation_time)
count = 0
initial_time = time.time()
while count < num_of_dark_flashes:
    a = int(driver('y'))
    time.sleep(darkflash_duration)
    a = int(driver('y'))
    count += 1
    print(count)
    time.sleep(inter_stim_interval)

exit_event.set()
timer_thread.join()

print("Total time taken is ", (time.time() - initial_time)/60, ' mins')
print("\nExperiment complete.")

        
