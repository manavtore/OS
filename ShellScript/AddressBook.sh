#!/bin/bash

address_book="address_book.txt"

# Function to add a new contact
add_contact() {
    echo "Enter the following information for the new contact:"
    read -p "Name: " name
    read -p "Phone number: " phone
    read -p "Email: " email

    echo "$name:$phone:$email" >> "$address_book"
    echo "Contact added: $name"
}

# Function to view all contacts
view_contacts() {
    if [ -s "$address_book" ]; then
        echo "Address Book:"
        awk -F: '{printf "Name: %-20s Phone: %-15s Email: %s\n", $1, $2, $3}' "$address_book"
    else
        echo "Address book is empty."
    fi
}

# Main menu
while true; do
    echo "Address Book Menu:"
    echo "1. Add Contact"
    echo "2. View Contacts"
    echo "3. Exit"
    read -p "Enter your choice (1/2/3): " choice

    case "$choice" in
        1)
            add_contact
            ;;
        2)
            view_contacts
            ;;
        3)
            echo "Exiting address book."
            exit 0
            ;;
        *)
            echo "Invalid choice. Please select 1, 2, or 3."
            ;;
    esac
done
