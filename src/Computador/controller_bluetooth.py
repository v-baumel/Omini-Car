import pygame
import serial
import time

# -- config --
BAUD_RATE = 9600
DEADZONE = 0.08
MIN_SEND_INTERVAL = 0.1   # tempo mínimo entre envios
MAX_SEND_INTERVAL = 1.0   # tempo máximo entre envios (heartbeat)

port = "/dev/rfcomm0"

print(f"Conectando à porta: {port}...")

try:
    ser = serial.Serial(port, BAUD_RATE)
    time.sleep(2)
except serial.SerialException as e:
    print(f"Falha ao abrir porta serial: {e}")
    exit()

pygame.init()
pygame.joystick.init()

js = pygame.joystick.Joystick(0)
if not js:
    print("Controle não encontrado!")
    exit()

clock = pygame.time.Clock()
prev_x, prev_y, prev_z = 0.0, 0.0, 0.0
last_send_time = time.time()

def changed(a, b, eps=0.01):
    return abs(a - b) > eps

running = True
try:
    while running:
        now = time.time()

        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        x = js.get_axis(0)
        y = -js.get_axis(1)
        z = js.get_axis(3)

        if abs(x) < DEADZONE: x = 0.0
        if abs(y) < DEADZONE: y = 0.0
        if abs(z) < DEADZONE: z = 0.0

        value_changed = (
            changed(x, prev_x) or
            changed(y, prev_y) or
            changed(z, prev_z)
        )

        min_ok = (now - last_send_time) >= MIN_SEND_INTERVAL
        max_ok = (now - last_send_time) >= MAX_SEND_INTERVAL

        if (value_changed and min_ok) or max_ok:
            msg = f"{x:.3f},{y:.3f},{z:.3f};".encode()
            ser.write(msg)

            prev_x, prev_y, prev_z = x, y, z
            last_send_time = now

            print(f"Enviado: {msg.decode().strip()}")

        clock.tick(60)

finally:
    print("Acabando...")
    ser.close()
    pygame.quit()
