from pynput import keyboard
import serial
import time
from pynput.keyboard import Key, Listener
import keyboard
from tkinter import Tk, Label
from tkinter import *
from tkinter.ttk import *

xInt = None
yInt = None


arduino = serial.Serial(port="COM5", baudrate='9600', timeout=0.01)

modeOfOperation = input("""
How would you like to control your turret? 
Type 1 for debug mode or press 2 for automatic mouse control.""")


def writeCoords(x, y, laz):
    if x > 180 or x < 0 or y > 180 or y < 0:
        print("NOPE! Invalid coord. Max coord value: 180")
    else:
        stringX = str(x)
        stringY = str(y)
        stringLaz = str(laz)
        coords = "X" + stringX + "Y" + stringY + "L" + stringLaz  # This line adds delimiters that allow the arduino to parse the sent commands
        print("Coordinates sent: " + coords)
        arduino.write(bytes(coords, encoding="utf-8"))


if modeOfOperation == '1':
    while True:
        xInt = int(input("X: "))
        yInt = int(input("Y: "))
        LazerInt = int(input("L: "))
        writeCoords(xInt, yInt, LazerInt)
        print("Coordinates sent.")
        time.sleep(0.1)

if modeOfOperation == '2':
            
            
    class TrackingWindow(Toplevel):
            
            
        def __init__(self, master=None):  # Sets default parameters
            super().__init__(master=master)
            self.title("Laser Positioner")
            self.geometry("200x200")
            label = Label(self, text="Hover mouse and type L")
            label.pack()
          
            
        def callback(e):  # Executes whenever you move the mouse on the window
            x = e.x  # L/R mouse position, left is low
            y = e.y  # U/D mouse position
            las = 1  # Default laser state is off
            if keyboard.is_pressed("l"):
                las = 0
            print("Pointer is currently at %d, %d" %(x,y))
            xInt = round(x / 5)
            yInt = round(y / 5)
            writeCoords(xInt, yInt, las)
            print("")
            time.sleep(0.1)
            
            
        master = Tk()
        master.geometry("900x900")
        master.resizable(False, False)
        master.bind("<Motion>", callback)
        mainloop()