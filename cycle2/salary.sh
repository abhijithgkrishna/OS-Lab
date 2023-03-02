read -p "Enter basic pay" pay
echo $pay
if [[ $pay -gt 1500 ]]; then
	hra=$((pay/10))
	da=$((90*pay/100))
else
	hra=500
	da=$((98*pay/100))
fi

salary=$((pay+hra+da))
echo $hra
echo $da
echo salary is $salary