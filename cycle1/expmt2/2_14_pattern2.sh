read -p "Enter number of rows" n
if [ $((n%2)) -eq 0 ]
then
    r=$((n/2))
else
    r=$((n/2+1))
fi
c=0
for (( i=1; i<=n; i++ ))
do
    j=1
    while [ $j -le $((r-c-1)) ]		
    do
        echo -n " "
        j=$((j+1))
    done
    while [ $j -le $((r+c)) ]
    do
        echo -n "*"
        j=$((j+1))
    done
    if [ $i -lt $r ]
    then
        c=$((c+1))
    else if [ $i -eq $r ]
    then
        if ! [ $((n%2)) -eq 0 ]
        then
            c=$((c-1))
        fi
    else
        c=$((c-1))
    fi
    fi
    echo ""
done