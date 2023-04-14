# Importing Libraries
import serial
from psychopy import visual, event
from psychopy.visual.windowwarp import Warper
import time as time

arduino = serial.Serial(port='COM3', baudrate=115200, timeout=.1)
p = 6.89

win0=visual.Window(
        size=(700,700),
        screen = 1,
        fullscr=True,
        units="pix",
        color=[1,1,1],
        monitor="exp",
        useFBO = False
)

def driver(x):
    arduino.write(bytes(x, 'utf-8'))
    time.sleep(0.05)
    signal = arduino.readline()
    return signal

blah = 0
blah = input('Do you want to start the experiment (y/n):')
flag = 0
initial_time = time.time()
while flag < 5:
    # event.waitKeys()
    time.sleep(5)
    f = 0
    # blah = input('Do you want to start the experiment (y/n):') # Taking input from user
    command = int(driver(blah))

    circle1=visual.Circle(
    win=win0,
    radius=p,
    fillColor=[-1,-1,-1],
    lineColor=[-1,-1,-1],
    units='pix')
    flag+=1

    while command:
        # start = time. process_time()
        circle1.pos=(-100,-190)
        circle1.draw()
        while True:
            if command == 1:
                break
        win0.flip()
        # time.sleep(3)
        start = time.time()
        # event.waitKeys()
        while True:
            circle1.radius = circle1.radius + 2.2*2
            circle1.draw()
            win0.flip()
            time.sleep(.01)
            if circle1.radius >= 100:
                f = 1
                a = int(driver('y'))
                print(time.time() - start)
                # event.waitKeys()
                break
        if f == 1:
            win0.flip()
            break

print("Total time taken is ", time.time() - initial_time)
print("\nExperiment complete. Press any key to exit.")
event.waitKeys()
        
