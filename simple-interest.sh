#!/usr/bin/env bash

# Calculate simple interest from principal, annual rate, and time in years.

read -r -p "Enter the principal amount: " principal
read -r -p "Enter the annual rate of interest (%): " rate
read -r -p "Enter the time period (years): " time

# Validate that inputs are non-empty numbers.
if [[ ! "$principal" =~ ^[0-9]+([.][0-9]+)?$ ||
      ! "$rate" =~ ^[0-9]+([.][0-9]+)?$ ||
      ! "$time" =~ ^[0-9]+([.][0-9]+)?$ ]]; then
  echo "Error: Please enter valid non-negative numbers for principal, rate, and time." >&2
  exit 1
fi

interest=$(awk -v p="$principal" -v r="$rate" -v t="$time" 'BEGIN { printf "%.2f", (p * r * t) / 100 }')
printf "Simple interest: %s\n" "$interest"
