#!/bin/bash
node shanshui.js
cairosvg shanshui.svg -s 1.755 -f png -o shanshui.png
convert shanshui.png -resize 1872x1404 -gamma 3 -brightness-contrast -5 -background white -flatten -depth 8 shanshui0.bmp
convert shanshui.png -resize 1872x1404 -gamma 3 -background white -flatten -depth 8 shanshui1.bmp
epd shanshui0.bmp
epd shanshui1.bmp

