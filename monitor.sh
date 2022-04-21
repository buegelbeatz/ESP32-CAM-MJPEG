#!/bin/bash

# 115200

speed="$1"

if [ "$speed" == "" ];then
 speed=115200
fi

pio device monitor  -b $speed
