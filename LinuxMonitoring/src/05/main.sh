#!/bin/bash

# Function to sort all entries by response code
sort_by_response_code() {
    sudo awk '{print $0}' nginx_log_*.log | sort -k9
}

# Function to find all unique IPs
unique_ips() {
    sudo awk '{print $1}' nginx_log_*.log | sort | uniq
}

# Function to find all requests with errors (response codes 4xx or 5xx)
requests_with_errors() {
    sudo awk '$9 ~ /^4[0-9][0-9]$/ || $9 ~ /^5[0-9][0-9]$/' nginx_log_*.log
}

# Function to find all unique IPs among the erroneous requests
unique_ips_with_errors() {
    sudo awk '$9 ~ /^4[0-9][0-9]$/ || $9 ~ /^5[0-9][0-9]$/{print $1}' nginx_log_*.log | sort | uniq
}

# Check if the correct number of parameters are provided
if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <option>"
    echo "Options:"
    echo "  1 - All entries sorted by response code"
    echo "  2 - All unique IPs found in the entries"
    echo "  3 - All requests with errors (response code 4xx or 5xx)"
    echo "  4 - All unique IPs found among the erroneous requests"
    exit 1
fi

# Process the parameter and call the appropriate function
option=$1
case $option in
    1)
        sort_by_response_code
        ;;
    2)
        unique_ips
        ;;
    3)
        requests_with_errors
        ;;
    4)
        unique_ips_with_errors
        ;;
    *)
        echo "Invalid option. Use 1, 2, 3 or 4."
        exit 1
        ;;
esac

