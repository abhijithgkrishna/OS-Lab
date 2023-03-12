if [ $# -ne 1 ]; then
  echo "Usage: summarize_directory <directory>"
  exit 1
fi
directory=$(realpath $1)
files=$(find "$directory" -type f)
num_files=$(echo "$files" | wc -l)
extensions=$(echo "$files" | awk -F. '{if (NF>1) {print $NF}}' | sort -u)
echo "Total number of files: $num_files"
echo "List of file extensions:"
echo "$extensions"
for ext in $extensions; do
  count=$(echo "$files" | awk -F. -v ext="$ext" '$NF == ext {count++} END {print count}')
  echo "$ext: $count"
done
