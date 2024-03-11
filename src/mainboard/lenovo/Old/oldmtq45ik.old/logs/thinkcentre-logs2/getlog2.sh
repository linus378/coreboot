#!/bin/bash

for x in /proc/asound/card0/codec#*;

do
       	cat "$x" > "$(basename "$x")"; 
done
