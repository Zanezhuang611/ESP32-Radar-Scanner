import pygame
import math
import serial

# --------------------------Initialize pygame---------------------------
pygame.init()

# Window size
WIDTH = 1000
HEIGHT = 600

screen = pygame.display.set_mode((WIDTH, HEIGHT))
pygame.display.set_caption("ESP32 Radar")

# Colors
BLACK = (0,0,0)
GREEN = (0,255,0)
RED = (255,0,0)

# Radar center
center_x = WIDTH // 2
center_y = HEIGHT

# Scan angle
angle = 0

#-------------------------Initialize Serial Data----------------------------
ser = serial.Serial('COM3',115200)

# Main loop
running = True

# Calculate radar display coordinates from target distance
def plot(angle,distance):

    x = distance * math.cos(math.radians(angle))

    y = distance * math.sin(math.radians(angle))

    return x,y

# Scan targets
targets = []

# Scale
scale = 15


#-------------------------------Main Loop------------------------------
while running:

    line = ser.readline().decode().strip()

    if "," in line:
        angle, distance = line.split(",")

        # Convert string to numeric
        angle = float(angle)
        distance = float(distance)


    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            running = False

    # Clear screen
    screen.fill(BLACK)

    # Draw radar circles
    pygame.draw.circle(
        screen,
        GREEN,
        (center_x, center_y),
        150,
        1
    )

    pygame.draw.circle(
        screen,
        GREEN,
        (center_x, center_y),
        300,
        1
    )

    pygame.draw.circle(
        screen,
        GREEN,
        (center_x, center_y),
        450,
        1
    )


    # Draw scan line
    length = 450

    end_x = center_x + length * math.cos(
        math.radians(angle)
    )

    end_y = center_y - length * math.sin(
        math.radians(angle)
    )

    pygame.draw.line(
        screen,
        GREEN,
        (center_x,center_y),
        (end_x,end_y),
        3
    )

    print(f"Angle:{angle}° Distance:{distance}cm")

    
    if distance < 20:
        
        x,y = plot(angle,distance)

        red_x = center_x + scale * x
        red_y = center_y - scale * y

        targets.append((red_x,red_y))

    else:
        targets.clear()

    for point in targets:

            pygame.draw.circle(screen,RED,(int(point[0]),int(point[1])),3)
        
    

    # Update display
    pygame.display.update()

pygame.quit()