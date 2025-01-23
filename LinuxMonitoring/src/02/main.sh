#!/bin/bash

# Check if the correct number of parameters are provided
if [ "$#" -ne 3 ]; then
  echo "Usage: $0 <folder_chars> <file_chars.ext> <file_size>"
  exit 1
fi

# Get the parameters
folder_chars=$1
file_chars=$2
file_size_str=$3

# Extract file name and extension separately
file_name=${file_chars%%.*}
file_extension=${file_chars##*.}

# Check for the correct length of parameters
if [[ ${#folder_chars} -gt 7 ]] || [[ ${#file_name} -gt 7 ]] || [[ ${#file_extension} -gt 3 ]]; then
  echo "Error: Incorrect length of parameters"
  exit 1
fi

# Extract the numerical part and unit of the file size
file_size_num=$(echo $file_size_str | grep -o -E '[0-9]+')
file_size_unit=$(echo $file_size_str | grep -o -E '[a-zA-Z]+')

# Convert file size to kilobytes if necessary
if [[ "$file_size_unit" =~ ^[Kk][Bb]$ ]]; then
  file_size_kb=$file_size_num
elif [[ "$file_size_unit" =~ ^[Mm][Bb]$ ]]; then
  file_size_kb=$((file_size_num * 1024))
else
  echo "Invalid file size unit. Use 'kb' for kilobytes or 'mb' for megabytes."
  exit 1
fi

# Check if the file size is valid and does not exceed 102400 KB (100 MB)
if ! [[ "$file_size_kb" =~ ^[0-9]+$ ]] || [ "$file_size_kb" -gt 102400 ]; then
  echo "File size must be a number and not more than 102400 KB (100 MB)"
  exit 1
fi

# Function to check for free space on root
check_free_space() {
  free_space=$(df -Pk / | awk 'NR==2 {print $4}')
  if [ "$free_space" -le 1048576 ]; then
    echo "Less than 1GB of free space remaining. Exiting."
    exit 0
  fi
}

# Create a function to generate a random string with given characters
generate_random_string() {
  local chars=$1
  local length=$2
  local result=""
  while [ "${#result}" -lt "$length" ]; do
    result="${result}${chars:RANDOM%${#chars}:1}"
  done
  echo "$result"
}

# Initialize log file and record start time
log_file="script_log.txt"
start_time=$(date +%s)
echo "Script started at $(date)" > "$log_file"

# Start creating folders and files
folder_count=0

while [ $folder_count -lt 100 ]; do
  check_free_space

  # Generate folder name
  folder_name=$(generate_random_string "$folder_chars" 5)_$(date +%d%m%y)
  folder_path="/tmp/${folder_name}"
  mkdir -p "$folder_path"

  # Log folder creation
  echo "Created folder: $folder_path at $(date)" >> "$log_file"

  # Generate a random number of files for the folder
  file_count=$((RANDOM % 10 + 1))
  for ((i=0; i<file_count; i++)); do
    check_free_space

    # Generate file name
    file_name=$(generate_random_string "$file_name" 5)_$(date +%d%m%y).$file_extension
    file_path="${folder_path}/${file_name}"

    # Create file with the specified size
    dd if=/dev/zero of="$file_path" bs=1024 count=$file_size_kb 2>/dev/null

    # Log file creation
    echo "Created file: $file_path at $(date) with size ${file_size_kb}KB" >> "$log_file"
  done

  folder_count=$((folder_count + 1))
done

# Record end time
end_time=$(date +%s)
echo "Script ended at $(date)" >> "$log_file"
echo "Total running time: $(($end_time - $start_time)) seconds" >> "$log_file"

# Display start, end time and total running time
echo "Script started at $(date -d @$start_time)"
echo "Script ended at $(date -d @$end_time)"
echo "Total running time: $(($end_time - $start_time)) seconds"

