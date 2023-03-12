read -p "first value : " a
read -p "second value : " b
read -p "third value : " c

if [[ $a -lt $b ]]; then
	if [[ $a -lt $c ]]; then
		echo $a
	else
		echo $c
	fi
else
	if [[ $b -lt $c ]]; then
		echo $b
	else
		echo $c
	fi
fi