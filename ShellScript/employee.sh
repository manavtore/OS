#!/bin/bash

EMP_FILE="emp.txt"

# Check if the employee file exists, if not, create it
[ -e "$EMP_FILE" ] || touch "$EMP_FILE"

# Menu
while true; do
    echo -e "\nEmployee Database Menu:"
    echo "1. Add Employee"
    echo "2. Modify Employee"
    echo "3. Display Employees"
    echo "4. Display Salaries"
    echo "5. Calculate Sum of Salaries"
    echo "6. Exit"
    read choice

    case $choice in
        1)
            # Add Employee
            echo "Enter employee ID:"
            read id

            echo "Enter employee name:"
            read name

            echo "Enter employee role:"
            read role

            echo "Enter salary for $name:"
            read salary

            echo "$id $name $role $salary" >> "$EMP_FILE"

            echo "Employee $name added with role $role and salary $salary"
            ;;

        2)
            # Modify Employee
            echo "Enter employee ID to modify:"
            read modify_id

            # Check if the ID exists in the file
            if grep -q "^$modify_id " "$EMP_FILE"; then
                echo "Enter new salary for employee ID $modify_id:"
                read new_salary

                # Update the salary for the specified ID
                sed -i "s/^$modify_id [^\ ]* /$modify_id $new_salary /" "$EMP_FILE"

                echo "Employee ID $modify_id modified with new salary $new_salary"
            else
                echo "Employee with ID $modify_id not found."
            fi
            ;;

        3)
            # Display Employees
            echo "Employee entries:"
            cat "$EMP_FILE"
            ;;

        4)
            # Display Salaries
            echo "Employee salaries:"
            awk '{ printf "%-15s %-15s %s\n", $2, $3, $4 }' "$EMP_FILE"
            ;;

        5)
            # Calculate Sum of Salaries
             sum=$(awk '{sum+=$4} END{printf "%.2f", sum}' "$EMP_FILE")
            echo "Sum of all employee salaries: $sum"
            ;;

        6)
            # Exit
            echo "Exiting..."
            exit
            ;;

        *)
            echo "Invalid choice. Please enter a number between 1 and 6."
            ;;
    esac
done

# awk '{ sum+=$1;print $1} END {print "Sum";print sum}' emp.txt