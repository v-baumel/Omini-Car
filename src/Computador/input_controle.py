import pygame
import sys

pygame.init()
pygame.joystick.init()

if pygame.joystick.get_count() == 0:
    print("No controller detected!")
    sys.exit()

js = pygame.joystick.Joystick(0)
js.init()

clock = pygame.time.Clock()

throttle = 0.0
THROTTLE_SPEED = 60.0  # percent per second
DEADZONE = 0.1         # ignore tiny trigger noise

FACE_BUTTONS = {
    0: "Square",
    1: "Cross",
    2: "Circle",
    3: "Triangle",
}

def normalize_trigger(v):
    """
    Convert common axis ranges into 0.0..1.0 trigger value.
    - If axis is in [-1, 1], transform to [0,1] by (v+1)/2.
    - If axis already in [0,1], keep it.
    - Clamp final value to [0,1].
    """
    if v < -0.2:            # probable -1..1 range
        v = (v + 1.0) / 2.0
    # else assume it's already 0..1 or tiny negative -> clamp
    return max(0.0, min(1.0, v))

def read_triggers_fallback(js):
    """
    Read common trigger axis indices and return (l2, r2) normalized.
    Prefer indices 4 and 5, but if they look inactive we'll try 2 and 3.
    """
    # try common indices first
    axes = {}
    for i in range(js.get_numaxes()):
        axes[i] = js.get_axis(i)

    # primary guess
    l2 = normalize_trigger(axes.get(4, 0.0))
    r2 = normalize_trigger(axes.get(5, 0.0))

    # if both nearly zero, try other usual indices (2 and 3)
    if l2 <= 0.05 and r2 <= 0.05:
        cand2 = normalize_trigger(axes.get(2, 0.0))
        cand3 = normalize_trigger(axes.get(3, 0.0))

        # heuristics: assign larger candidate to whichever trigger likely corresponds
        # prefer cand2 -> L2, cand3 -> R2 (common mapping), but only if bigger than current
        if cand2 > l2:
            l2 = cand2
        if cand3 > r2:
            r2 = cand3

    return l2, r2

while True:
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()

        if event.type == pygame.JOYBUTTONDOWN:
            if event.button in FACE_BUTTONS:
                if event.button == 2:
                    throttle = 0
                print(f"{FACE_BUTTONS[event.button]} pressed")

        elif event.type == pygame.JOYBUTTONUP:
            if event.button in FACE_BUTTONS:
                print(f"{FACE_BUTTONS[event.button]} released")

    # Read left joystick (kept but not printed)
    left_x = js.get_axis(0)
    left_y = js.get_axis(1)
    # ... you can use left_x / left_y in your logic

    # Read triggers with fallback + normalization
    l2, r2 = read_triggers_fallback(js)

    # Apply deadzone
    if l2 < DEADZONE:
        l2 = 0.0
    if r2 < DEADZONE:
        r2 = 0.0

    dt = clock.get_time() / 1000.0  # seconds since last frame

    # Increase / decrease throttle
    if r2 > 0.0:
        throttle += THROTTLE_SPEED * r2 * dt
    if l2 > 0.0:
        throttle -= THROTTLE_SPEED * l2 * dt

    

    throttle = max(0.0, min(100.0, throttle))

    #print(f"Throttle: {throttle:.1f}%  (L2: {l2:.2f}, R2: {r2:.2f})")

    clock.tick(15)
