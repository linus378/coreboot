#!/bin/bash


for x in /sys/class/sound/card0/hw*;

do
       	cat "$x/init_pin_configs" > pin_"$(basename "$x")";

done
