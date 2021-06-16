#!/usr/bin/env python

import os

while True:
    for i in range(100):
        os.system("epd output/ss_%d_0.bmp" % i)
        os.system("epd output/ss_%d_1.bmp" % i)
	    time.sleep(120)

