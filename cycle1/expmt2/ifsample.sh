#!/bin/bash

read -p "Enter a number " x
read -p "Enter a number " y


# var=$((x-y))
# echo $var
if [[ $((x%2)) -eq 0 ]]; then
	echo $x is even
else 
	echo $x is odd
fi

if [[ $x -gt $y ]]
then
	echo $x greater than $y
elif [[ $x -lt $y ]]; then
	echo $x is less than $y
elif [[ $x -eq $x ]]; then
	echo $x is equal to $y	
fi
