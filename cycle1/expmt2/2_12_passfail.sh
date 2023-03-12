while read line; do
    roll_number=$(echo $line | cut -d ' ' -f 1)
    marks1=$(echo $line | cut -d ' ' -f 2)
    marks2=$(echo $line | cut -d ' ' -f 3)
    marks3=$(echo $line | cut -d ' ' -f 4)
    if [ $marks1 -ge 50 ] && [ $marks2 -ge 50 ] && [ $marks3 -ge 50 ]; then
        result="pass"
    else
        result="fail"
    fi
    echo "$roll_number $result"
done < marks.txt