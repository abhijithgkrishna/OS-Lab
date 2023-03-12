echo $@
rev=" "
for n in $@ 
do
	rev=$n" "$rev
done
echo $rev