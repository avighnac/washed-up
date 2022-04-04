'''
1. Make a python application that takes an image file as input and prints out the hex value of every pixel (for example white: 0xffffff).
'''

from PIL import Image
import sys

def rgbtohex(r, g, b):
    return '0x{:02x}{:02x}{:02x}'.format(r, g, b)

def main():
    if len(sys.argv) == 2:
        f = open(sys.argv[1][:-4] + ".hexImage", "w")
        f.write("#include <vector>\nstd::vector<std::vector<unsigned int>> " + sys.argv[1][:-4] + " = {")

        image_name = sys.argv[1]
        img = Image.open(image_name)
        width, height = img.size
        for x in range(height):
            f.write("{")
            for y in range(width):
                if img.mode == 'RGBA':
                    r, g, b, transparency = img.getpixel((y, x))
                else:
                    r, g, b = img.getpixel((y, x))
                f.write(rgbtohex(r, g, b) + ", ")
            f.write('},\n')

        f.write("};")
    else:
        print("Usage: python hexImage.py <filename.format>")


if __name__ == '__main__':
    main()
