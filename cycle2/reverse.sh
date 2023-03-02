read -p "Enter a number " num

len=${#num}

while [ $num -gt 0 ] 
do 
	digit=$((num%10))
	echo -n $digit
	num=$((num/10))
done
