for name in $@; do
	echo filename is: $name
	tr [:lower:] [:upper:] < $name
	echo ""
done