import serial
import time
import sys

# returns the bit at a certain digit of a byte
def getbit(byte, digit):
    binary_num = 2 ** (digit)
    return (byte & binary_num) >> (digit)

ser = serial.Serial(port="/dev/ttyACM0", baudrate=9600)

fin = open(sys.argv[1], "rb")
text = fin.read()
bits = []
nums = [7, 6, 5, 4, 3, 2, 1, 0]

# bits will be stored in array as biggest digit to smallest
for byte in text:
    for num in nums:
        bits.append(getbit(byte, num))

# takes bits and puts them back into a text file
fout = open("out.txt", "w")
for i in range(0, len(bits)-1, 8):
    char = 0
    for j in range(7, -1, -1):
        char += bits[i+(7-j)] * (2**j)
    fout.write(chr(char))

for bit in bits:
    ser.write(bit)
    print(bit)
    time.sleep(0.1)

fin.close()
fout.close()
