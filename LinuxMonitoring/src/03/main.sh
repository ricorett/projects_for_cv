#!/bin/bash

# Check if the correct number of parameters are provided
if [ "$#" -ne 1 ]; then
  echo "Usage: $0 <deletion_method>"
  echo "1: By log file"
  echo "2: By creation date and time"
  echo "3: By name mask"
  exit 1
fi

DELETION_METHOD=$1
LOG_FILE="../02/script_log.txt"

# Function to delete by log file
delete_by_log_file() {
  if [ ! -f "$LOG_FILE" ]; then
    echo "Log file not found."
    exit 1
  fi

  while IFS= read -r line; do
    path=$(echo "$line" | awk '{print $3}')
    if [ -d "$path" ]; then
      rm -rf "$path"
      echo "Deleted folder: $path"
    elif [ -f "$path" ]; then
      rm -f "$path"
      echo "Deleted file: $path"
    fi
  done < <(grep -E "Created (folder|file):" "$LOG_FILE")
}

# Function to delete by creation date and time
delete_by_date_time() {
  echo "Enter start date and time (format: YYYY-MM-DD HH:MM):"
  read -r start_date_time
  echo "Enter end date and time (format: YYYY-MM-DD HH:MM):"
  read -r end_date_time

  start_epoch=$(date -d "$start_date_time" +%s)
  end_epoch=$(date -d "$end_date_time" +%s)

  find /tmp -type d -newermt "@$start_epoch" ! -newermt "@$end_epoch" -exec rm -rf {} + 2>/dev/null
  find /tmp -type f -newermt "@$start_epoch" ! -newermt "@$end_epoch" -exec rm -f {} + 2>/dev/null

  echo "Deleted all files and folders created between $start_date_time and $end_date_time"
}

# Function to delete by name mask
delete_by_name_mask() {
  echo "Enter the name mask (e.g., az_150723):"
  read -r name_mask

  find /tmp -maxdepth 1 -type d -name "${name_mask}*" -exec rm -rf {} + 2>/dev/null
  find /tmp -maxdepth 1 -type f -name "${name_mask}*" -exec rm -f {} + 2>/dev/null

  echo "Deleted all files and folders with name mask: $name_mask"
}

# Main script logic based on the deletion method
case $DELETION_METHOD in
  1)
    delete_by_log_file
    ;;
  2)
    delete_by_date_time
    ;;
  3)
    delete_by_name_mask
    ;;
  *)
    echo "Invalid deletion method. Please use 1, 2, or 3."
    exit 1
    ;;
esac

echo "Deletion process completed."

