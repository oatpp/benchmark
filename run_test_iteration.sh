#!/bin/bash

threads=$1
connections=$2
duration=$3
repetitions=$4
sleep_seconds=$5
#ports=$...

run_test() {

    server_port=$1
    results_file=$2

    echo "threads=$threads, connections=$connections, duration=$duration, repetitions=$repetitions:"

    echo "-----------------------------------------------------------------------------------------" >> $results_file
    echo "threads=$threads, connections=$connections:" >> $results_file

    for ((i=1; i<=$repetitions; i++)); do
        echo "testing server at port=$server_port"
        echo "" >> $results_file
        wrk -t$threads -c$connections -d$duration "http://127.0.0.1:$server_port/" >> $results_file
        sleep $sleep_seconds
    done

    echo "" >> $results_file
    echo ""

}

argc=$#
argv=($@)

for (( j=5; j<argc; j++ )); do
    port="${argv[j]}"
    echo "port = $port"
    run_test $port "results_$port.txt"
done