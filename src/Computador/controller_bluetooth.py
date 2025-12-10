import pygame
import serial
import serial.tools.list_ports
import time

# -- config --
BAUD_RATE = 9600
DEADZONE = 0.05        
SEND_INTERVAL = 0.05 

def find_hc05_port():
    ports = serial.tools.list_ports.comports()
    for p in ports:
        desc = (p.description or "").lower()
        device = (p.device or "").lower()
        if "hc-05" in desc or "hc05" in desc or "hc-05" in device:
            return p.device
    return None


port = find_hc05_port()
if not port:
    print("Port não encontrado!")
    exit()

print(f"Conectando ao port: {port}...")

try:
    ser = serial.Serial(port, BAUD_RATE, timeout=1)
    time.sleep(2) 
except serial.SerialException as e:
    print(f"Falha ao abrir serial port: {e}")
    exit()

pygame.init()
pygame.joystick.init()

if pygame.joystick.get_count() == 0:
    print("Controle não encontrado!")
    exit()

js = pygame.joystick.Joystick(0)

print(f"Controle detectado: {js.get_name()}")

clock = pygame.time.Clock()
last_sent_time = 0
prev_x, prev_y, prev_z = 0, 0, 0

running = True
try:
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        x = js.get_axis(0)
        y = js.get_axis(1)
        z = js.get_axis(2) 

        if abs(x) < DEADZONE: x = 0
        if abs(y) < DEADZONE: y = 0
        if abs(z) < DEADZONE: z = 0 

        current_time = time.time()
        if (x != prev_x or y != prev_y or z != prev_z) and (current_time - last_sent_time > SEND_INTERVAL):
            try:
                msg = f"{x:.3f},{y:.3f},{z:.3f}\n".encode() 
                ser.write(msg)
                last_sent_time = current_time
                prev_x, prev_y, prev_z = x, y, z
                print(f"Enviado: {x}, {y}, {z}")
            except Exception as e:
                print(f"Serial error: {e}")
                break

        clock.tick(60) 

finally:
    print("Acabando...")
    ser.close()
    pygame.quit()
