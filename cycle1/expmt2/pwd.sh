echo "Enter your password:"
read password

if [[ ${#password} -lt 8 || $password != *[[:lower:]]* || $password != *[[:upper:]]* || $password != *[[:digit:]]* || $password != *[_]* ]]; then
  echo "Weak Password"
else
  echo "Strong Password"
fi