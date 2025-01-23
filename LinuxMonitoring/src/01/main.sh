#!/bin/bash

# Check if the correct number of arguments are passed
if [ "$#" -ne 6 ]; then
  echo "Usage: $0 <absolute_path> <num_subfolders> <folder_name_letters> <num_files> <file_name_letters.ext> <file_size_kb>"
  exit 1
fi

# Parse parameters
ABS_PATH=$1
NUM_SUBFOLDERS=$2
FOLDER_LETTERS=$3
NUM_FILES=$4
FILE_LETTERS_EXT=$5
FILE_SIZE_STR=$6

# Extract the numerical part and unit of the file size
FILE_SIZE_NUM=$(echo $FILE_SIZE_STR | grep -o -E '[0-9]+')
FILE_SIZE_UNIT=$(echo $FILE_SIZE_STR | grep -o -E '[a-zA-Z]+')

# Check the file size unit
if [ "$FILE_SIZE_UNIT" != "kb" ] && [ "$FILE_SIZE_UNIT" != "KB" ]; then
  echo "Invalid file size unit. Use 'kb' for kilobytes."
  exit 1
fi

# Check if the file size is valid and does not exceed 100 KB
if ! [[ "$FILE_SIZE_NUM" =~ ^[0-9]+$ ]] || [ "$FILE_SIZE_NUM" -gt 100 ]; then
  echo "File size must be a number and not more than 100 KB"
  exit 1
fi

FILE_SIZE=$FILE_SIZE_NUM

# Extract file name and extension
FILE_LETTERS=${FILE_LETTERS_EXT%.*}
FILE_EXT=${FILE_LETTERS_EXT##*.}

# Get the current date
DATE=$(date +%d%m%y)

# Create a log file
LOG_FILE="creation_log_$(date +%d%m%y%H%M%S).log"
touch $LOG_FILE

# Function to check available disk space and exit if less than 1GB
check_disk_space() {
  AVAIL_SPACE=$(df --output=avail / | tail -n 1)
  if [ "$AVAIL_SPACE" -le 1048576 ]; then
    echo "Less than 1GB of free space remaining. Exiting."
    exit 1
  fi
}

# Function to generate random names
generate_random_name() {
  local letters=$1
  local name_length=$2
  local result=""
  local letters_length=${#letters}

  for (( i=0; i<$name_length; i++ )); do
    result="${result}${letters:RANDOM%letters_length:1}"
  done

  echo "${result}_${DATE}"
}

# Create folders and files
for (( i=0; i<$NUM_SUBFOLDERS; i++ )); do
  check_disk_space
  FOLDER_NAME=$(generate_random_name $FOLDER_LETTERS 4)
  FOLDER_PATH="$ABS_PATH/$FOLDER_NAME"
  
  mkdir -p $FOLDER_PATH
  echo "Created folder: $FOLDER_PATH" >> $LOG_FILE
  
  for (( j=0; j<$NUM_FILES; j++ )); do
    check_disk_space
    FILE_NAME=$(generate_random_name $FILE_LETTERS 4).$FILE_EXT
    FILE_PATH="$FOLDER_PATH/$FILE_NAME"
    
    dd if=/dev/zero of=$FILE_PATH bs=1K count=$FILE_SIZE &> /dev/null
    if [ $? -eq 0 ]; then
      echo "Created file: $FILE_PATH, Size: ${FILE_SIZE}KB" >> $LOG_FILE
    else
      echo "Failed to create file: $FILE_PATH" >> $LOG_FILE
    fi
  done
done

echo "Script execution completed. Log file: $LOG_FILE"

