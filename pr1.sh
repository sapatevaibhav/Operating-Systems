#!/bin/bash

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
    echo -e "\t1. View Address Book"
    echo -e "\t2. Insert a Record"
    echo -e "\t3. Delete a Record"
    echo -e "\t4. Modify a Record"
    echo -e "\t5. Search a Record"
    echo -e "\t6. Exit from Address Book"
    echo -e "Enter your choice: "
    read ch

    case $ch in
    1)
        cat "$fname"
        ;;
    2)
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
    3)
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
    4)
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
    5)
        echo -e "Enter Employee ID to be Searched: "
        read eid
        if grep -qw "$eid" "$fname"; then
            grep -w "$eid" "$fname"
            echo "Record Found"
        else
            echo "Error: Record does not exist!"
        fi
        ;;
    6)
        echo -e "Thank You\n"
        exit
        ;;
    *)
        echo -e "Please enter the correct choice\n"
        ;;
    esac
done
