#! /bin/bash

declare -a expected;
expected=(0 9952 1 69705 1 11 1 7046 4 18672 2232 5 6 185);


for i in {1..13}; do
    echo "Running $i.sql";
    cat "$i.sql" | sqlite3 movies.db > "output$i.txt";
    lines=`wc -l < "output$i.txt"`;
    if [[ lines -eq ${expected[i]} ]]; then
        echo "Passes";
    else
        echo "Fails";
    fi
done
