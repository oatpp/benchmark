#!/bin/bash

threads=$1
connections=$2
duration=$3
repetitions=$4
sleep_seconds=$5
port_oatpp=$6
port_oatpp_async=$7
port_go=$8

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

run_test $port_oatpp "results_oatpp.txt"
run_test $port_oatpp_async "results_oatpp_async.txt"
run_test $port_go "results_go.txt"