#!/bin/bash
mkdir lab
cd lab
read -p "Please choose whether to create a file or delete a file (type in (C) for create, type in (D) for delete): " RES
if [ "$RES" = "C" ]; then
    touch {1..10}.c
elif [ "$RES" = "D" ]; then
    rm *.c
else
    echo "Invalid option. Please type 'C' for create or 'D' for delete."
fi
ls