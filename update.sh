#!/bin/bash
node shanshui.js
cairosvg shanshui.svg -s 1.755 -f png -o shanshui.png
convert shanshui.png -resize 1872x1404 -background white -flatten shanshui.bmp
