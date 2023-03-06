echo "Enter decimal number: "
read decimal_num

binary_num=$(echo "ibase=10;obase=2;$decimal_num" | bc)
hex_num=$(echo "ibase=10;obase=16;$decimal_num" | bc)

echo "Binary equivalent: $binary_num"
echo "Hexadecimal equivalent: $hex_num"
