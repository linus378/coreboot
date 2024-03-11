#!/bin/bash

for i in *.bin;

do
       	mkdir $(basename -s .bin $i); 
	cd $(basename -s .bin $i);
       	ifdtool -x ../$i; cd ../;
done
