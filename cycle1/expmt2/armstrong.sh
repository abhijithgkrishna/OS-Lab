isarm () {
	num=$1
	pow=${#num}
	no=$num
	arm=0

	while [[ $num -gt 0 ]]; do
		dig=$((num%10))
		pos=$((dig**pow))
		arm=$((pos+arm))
		num=$((num/10))
	done

	if [[ $arm -eq $no ]]; then
		echo $arm
	
	fi

}

read -p "enter lower limit " a
read -p "enter higher limit " b

for (( i = $a; i < $b; i++ )); do
	isarm $i
done