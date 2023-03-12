read -p "Enter basic salary: " bs
if [ $bs -lt 1500 ]
then
	hra=`echo " scale=2; 0.1*$bs " | bc`
	da=`echo " scale=2; 0.9*$bs " | bc`
	bs=`echo " scale=2; $bs+$hra+$da " | bc`
	echo $bs
else
	hra=500
	da=`echo " scale=2; 0.98*$bs " | bc`
	bs=`echo " scale=2; $bs+$hra+$da " | bc`
	echo $bs
fi

