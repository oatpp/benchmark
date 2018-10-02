#!/bin/sh

threads=$1
duration=$2
repetitions=$3
port_oatpp=$4
port_oatpp_async=$5
port_go=$6

run_test() {
    connections=$1
    sleep_seconds=$2
    ./run_test_iteration.sh $threads $connections $duration $repetitions $sleep_seconds $port_oatpp $port_oatpp_async $port_go
}

## clear results

> results_oatpp.txt
> results_oatpp_async.txt
> results_go.txt

## test( $conn  $sleep )

run_test 2      5
run_test 10     5
run_test 50     5
run_test 100    10
run_test 500    10
run_test 1000   30
run_test 2500   30
run_test 5000   30
run_test 10000  60
run_test 15000  60
run_test 20000  60
run_test 25000  90
run_test 30000  90
