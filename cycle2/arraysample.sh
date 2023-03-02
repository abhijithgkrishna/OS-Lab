myarray=()

for i in $@; do
	myarray+=($i)
done

for (( i = ${#myarray[@]}; i >= 0; i-- )); do
	echo ${myarray[$i]}
done