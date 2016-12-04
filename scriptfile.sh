#!/bin/bash
if filename=$(ls *.sch);then
	echo "Found a Schematic File"
	echo "With Name :$filename"
else
	echo "Couldn't find any Schematic file"
	exit 1
fi

name=${filename%.*}
#echo $name

gnetlist -g spice-sdb -o $name.sp $name.sch>/dev/null

if [ $? -eq 0 ]; then
	echo "Netlist Generated from the Schematic File"
	echo "File Generated : $name.sp"
else
	echo "Couldn't able to generate Netlist FIle"
	exit 1
fi
make
