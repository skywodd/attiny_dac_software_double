#!/usr/bin/python

# Image source
IMGSRC = 'screen.png'

# ---------------------------------------------------------------------

import Image

print 'Checking source image ... '
img = Image.open(IMGSRC)
pixels = list(img.getdata())
if len(pixels) != 32*32 :
    print 'Source image must be 32x32px in 8 bits color (B & W)'
    exit(-1)

fo_x = open('samples_x.txt', 'w+')
fo_y = open('sample_y.txt', 'w+')

count = 1

for i in range(0, 32*32):
    if pixels[i] == 0:
        if (count%10) == 0:
            fo_x.write("\n")
            fo_y.write("\n")
            
        fo_x.write(str((i % 32)*8) + ', ')
        fo_y.write(str(((int)(i / 32))*8) + ', ')
        count += 1

print 'Samples count : %d' % (count - 1)

fo_x.close()
fo_y.close()

print 'Done ...'
