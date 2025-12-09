import pygame
import serial
import time
import math

# ---------------- Serial Setup ----------------
SERIAL_PORT = "/dev/rfcomm0"   # change for your device
BAUD_RATE = 9600

ser = serial.Serial(SERIAL_PORT, BAUD_RATE)
time.sleep(2)

# ---------------- Pygame Setup ----------------
pygame.init()
WIDTH, HEIGHT = 400, 400
screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("Virtual Joystick")

clock = pygame.time.Clock()

# Joystick properties
center = (WIDTH // 2, HEIGHT // 2)
base_radius = 120
knob_radius = 30
knob_pos = list(center)
dragging = False

def send_joystick(x, y):
    """
    Send joystick values (-100 to 100) to Arduino as:
    X:val Y:val\n
    """
    msg = f"{x},{y}\n".encode()
    ser.write(msg)
    print("Sent:", msg)

# ---------------- Main Loop ----------------
while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            ser.close()
            exit()

        elif event.type == pygame.MOUSEBUTTONDOWN:
            # Check if user clicked inside knob
            mx, my = event.pos
            if math.dist((mx, my), knob_pos) <= knob_radius:
                dragging = True

        elif event.type == pygame.MOUSEBUTTONUP:
            dragging = False
            knob_pos = list(center)
            send_joystick(0, 0)

        elif event.type == pygame.MOUSEMOTION and dragging:
            mx, my = event.pos
            dx = mx - center[0]
            dy = my - center[1]

            # Limit the knob inside the base circle
            dist = math.hypot(dx, dy)
            if dist > base_radius:
                scale = base_radius / dist
                dx *= scale
                dy *= scale

            knob_pos = [center[0] + dx, center[1] + dy]

            # Normalize values to -100 .. +100
            norm_x = int((dx / base_radius) * 100)
            norm_y = int((dy / base_radius) * 100)

            send_joystick(norm_x, norm_y)

    # ---------------- Draw ----------------
    screen.fill((30, 30, 30))

    # Base circle
    pygame.draw.circle(screen, (80, 80, 80), center, base_radius, 4)

    # Knob
    pygame.draw.circle(screen, (200, 200, 200), knob_pos, knob_radius)

    pygame.display.flip()
    clock.tick(60)
