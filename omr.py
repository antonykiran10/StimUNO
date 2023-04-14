# import serial
from psychopy import visual, event
from psychopy.visual.windowwarp import Warper
import time as time

win0=visual.Window(
        size=(700,700),
        screen = 1,
        fullscr=True,
        units="pix",
        color=[1,1,1],
        monitor="exp",
        useFBO = False
)

grating=visual.GratingStim(
    win=win0,
    size=[1280,720],
    units="pix",
    sf=2/230,    # x/y implies x cycles per y pixels; https://www.ncbi.nlm.nih.gov/pmc/articles/PMC3939076/
    ori=0,   # unit is in degree
    tex="sqr"   # type of grating sqr or sin
    )
# win0.getMovieFrame(buffer='back')

start = time.process_time()
grating.pos=(-100,0)
grating.draw()
win0.flip()
# event.waitKeys()
win0.flip()
# time.sleep(3)
start = time.time()
# event.waitKeys()
while (time.time() - start) <= 15:
    grating.setPhase(0.05,'-')
    grating.draw()
    win0.flip()
    # win0.getMovieFrame()
    # print(time.time())
    # event.waitKeys()
    # time.sleep(.01)
# event.waitKeys()

# win0.saveMovieFrames(fileName='C:\\Users\\anton\\OneDrive\\Desktop\\testMovie.mp4')
