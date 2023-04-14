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

    grating=visual.GratingStim(
        win=win0,
        size=[1280,720],
        units="pix",
        sf=2/230,    # x/y implies x cycles per y pixels; https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3939076/
        ori=0,   # unit is in degree
        tex="sqr"   # type of grating sqr or sin
        )
    flag+=1

    while command:
        start = time.process_time()
        grating.pos=(-100,0)
        grating.draw()
        win0.flip()
        # event.waitKeys()
        while True:
            if command == 1:
                break
        win0.flip()
        # time.sleep(3)
        start = time.time()
        # event.waitKeys()
        while True:
            grating.setPhase(0.06,'+')
            grating.draw()
            win0.flip()
            # event.waitKeys()
            # time.sleep(.01)
            if time.process_time() - start >= 10:
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
        
