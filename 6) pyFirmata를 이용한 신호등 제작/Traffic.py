from pyfirmata import Arduino, util
import time

port='COM6'
pinCarG =13
pinCarY =12
pinCarR =11

pinHumanG =10
pinHumanR =9

pinHumanSw =8
TIME_USE_HUMAN =2

BLINK_COUNT =5

prevTime=0

board=Arduino(port)
time.sleep(1)

board.get_pin('d:9:o')
board.get_pin('d:8:o')
board.get_pin('d:7:o')
board.get_pin('d:6:o')
board.get_pin('d:5:o')
board.get_pin('d:4:i')

iterater = util.Iterator(board)
iterater.start()

def initLED():
    board.digital[pinCarG].write(1)
    board.digital[pinCarY].write(0)
    board.digital[pinCarR].write(0)

    board.digital[pinHumanG].write(0)
    board.digital[pinHumanR].write(1)

    millis = ((time.time()))
    prevTime = millis

def changeLED():
    time.sleep(2)
    board.digital[pinCarG].write(0)
    board.digital[pinCarY].write(1)
    time.sleep(2)

    board.digital[pinCarY].write(0)
    board.digital[pinCarR].write(1)

    board.digital[pinHumanR].write(0)
    board.digital[pinHumanG].write(1)

    time.sleep(TIME_USE_HUMAN * 1)

    for i in (0,BLINK_COUNT):
        board.digital[pinHumanG].write(0)
        time.sleep(0.5)
        board.digital[pinHumanG].write(1)
        time.sleep(0.5)
    initLED()

while(True):
   initLED()
    sw = board.digital[pinHumanSw].read()
    if sw == 0 and board.digital[pinCarG].read() == 1:
        changeLED()
    else:
        millis = ((time.time()))
        currentTime = millis
        if (currentTime - prevTime > 10):
            changeLED()

board.exit()