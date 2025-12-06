import pygame
import serial
import time

SERIAL_PORT = "/dev/rfcomm1"   # change to your HC-05 bound port
BAUD_RATE = 9600

ser = serial.Serial(SERIAL_PORT, BAUD_RATE)
time.sleep(2)  # wait for Arduino reset

pygame.init()
pygame.joystick.init()

if pygame.joystick.get_count() == 0:
    print("No controller detected!")
    exit()

js = pygame.joystick.Joystick(0)
js.init()

print("DS4 connected:", js.get_name())
n = 0

while True:



    for event in pygame.event.get():
        if event.type == pygame.JOYBUTTONDOWN:
            if event.button == 1:      # X
                ser.write(b"X")
                print("X pressed")

            elif event.button == 2:    # Circle / O
                ser.write(b"O")
                print("Circle (O) pressed")

            elif event.button == 0:    # Square
                ser.write(b"S")
                print("Square pressed")

            elif event.button == 3:    # Triangle
                ser.write(b"T")
                print("Triangle pressed")

    pygame.time.wait(10)
