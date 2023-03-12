read -p "Enter n: " n
f=0
while [ $f -eq 0 ]
do
    n=$((n+1))
    for (( i=2; i*i<=n; i++ ))
    do 
        if [ $((n%i)) -eq 0 ]
        then
            f=1
            break
        fi
    done
    if [ $f -eq 0 ]
    then
        r=0
        num=$n
        while [ $num -gt 0 ] 
        do
        r=$((r*10+num%10))
        num=$((num/10))
        done
        if [ $r -eq $n ]
        then
            f=1
            echo "The next palindromic prime number is $n"
        else
            f=0
        fi
    else
        f=0
        
    fi
done