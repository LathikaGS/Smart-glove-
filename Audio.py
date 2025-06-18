import serial
import pyttsx3
import time

engine = pyttsx3.init()

ser = serial.Serial('COM13', 9600, timeout=1)  
time.sleep(2)  

print("Listening for gestures...")

while True:
    if ser.in_waiting > 0:
        line = ser.readline().decode('utf-8').strip()
        print("Received:", line)

        # Speak gesture if it contains the keyword
        if "Gesture:" in line:
            gesture = line.replace("Gesture:", "").strip()
            engine.say(gesture)
            engine.runAndWait()