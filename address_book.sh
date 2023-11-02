#!/bin/bash
# Shell programming: Write a program to implement an address book with the options given below:
# a) Create an address book. b) View the address book. c) Insert a record. d) Delete a record. e) Modify a record. f) Exit

echo "Enter Address Book Name: "
read fname

if [ ! -e "$fname" ]; then
    touch "$fname"
    echo -e "Address Book Created....\n"
    echo -e "ID\tNAME\tMOB_NO\tSALARY" >> "$fname"
else
    echo -e "Address Book '$fname' already exists.\n"
fi

while true; do
    echo -e "******ADDRESS BOOK****** :\n"
    echo -e "\ta. View Address Book"
    echo -e "\tb. Insert a Record"
    echo -e "\tc. Delete a Record"
    echo -e "\td. Modify a Record"
    echo -e "\te. Exit from Address Book"
    echo -e "Enter your choice: "
    read ch

    case $ch in
    a)
        cat "$fname"
        ;;
    b)
        echo -e "Enter ID of Employee: "
        read eid
        echo -e "Enter Name of Employee: "
        read ename
        echo -e "Enter Mobile No. of Employee: "
        read emob
        echo -e "Enter Salary of Employee: "
        read esal
        echo -e "$eid\t$ename\t$emob\t$esal" >> "$fname"
        ;;
    c)
        echo -e "Enter Employee ID to be Deleted: "
        read eid
        if grep -qw "$eid" "$fname"; then
            grep -wv "$eid" "$fname" > temp
            mv temp "$fname"
            echo "Record Deleted"
        else
            echo "Error: Record does not exist!"
        fi
        ;;
    d)
        echo -e "Enter Employee ID to be Modified: "
        read eid
        if grep -qw "$eid" "$fname"; then
            grep -wv "$eid" "$fname" > temp
            mv temp "$fname"
            echo -e "Enter Modified Record"
            echo -e "Enter ID of Employee: "
            read eid
            echo -e "Enter Name of Employee: "
            read ename
            echo -e "Enter Mobile No. of Employee: "
            read emob
            echo -e "Enter Salary of Employee: "
            read esal
            echo -e "$eid\t$ename\t$emob\t$esal" >> "$fname"
        else
            echo "Error: Record does not exist!"
        fi
        ;;
    e)
        echo -e "Thank You\n"
        exit
        ;;
    *)
        echo -e "Please enter the correct choice\n"
        ;;
    esac
done