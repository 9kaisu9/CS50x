from cs50 import get_int

while True:
    height = get_int("Height: ")
    if height < 9 and height > 0:
        break


for row in range(height):
    for space in range(height - row - 1):
        print(" ", end="")
    for hash in range(row + 1):
        print("#", end="")
    print("  ", end="")
    for hash in range(row + 1):
        print("#", end="")
    print()