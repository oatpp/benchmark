#!/bin/sh

################################################################
## oatpp
################################################################

echo "testing oatpp"
> results_oatpp
echo "running... connections: 2"
echo "" >> results_oatpp
wrk -t2 -c2 -d20s "http://127.0.0.1:8000/" >> results_oatpp
sleep 20

echo "running... connections: 10"
echo "" >> results_oatpp
wrk -t2 -c10 -d20s "http://127.0.0.1:8000/" >> results_oatpp
sleep 20

echo "running... connections: 50"
echo "" >> results_oatpp
wrk -t2 -c50 -d20s "http://127.0.0.1:8000/" >> results_oatpp
sleep 20

echo "running... connections: 100"
echo "" >> results_oatpp
wrk -t2 -c100 -d20s "http://127.0.0.1:8000/" >> results_oatpp
sleep 20

echo "running... connections: 500"
echo "" >> results_oatpp
wrk -t2 -c500 -d20s "http://127.0.0.1:8000/" >> results_oatpp
sleep 20

echo "running... connections: 1000"
echo "" >> results_oatpp
wrk -t2 -c1000 -d20s "http://127.0.0.1:8000/" >> results_oatpp
sleep 30

echo "running... connections: 2500"
echo "" >> results_oatpp
wrk -t2 -c2500 -d20s "http://127.0.0.1:8000/" >> results_oatpp
sleep 30

echo "running... connections: 5000"
echo "" >> results_oatpp
wrk -t2 -c5000 -d20s "http://127.0.0.1:8000/" >> results_oatpp
sleep 60

echo "running... connections: 10000"
echo "" >> results_oatpp
wrk -t2 -c10000 -d20s "http://127.0.0.1:8000/" >> results_oatpp
sleep 60

echo "running... connections: 15000"
echo "" >> results_oatpp
wrk -t2 -c15000 -d20s "http://127.0.0.1:8000/" >> results_oatpp
sleep 60

echo "running... connections: 20000"
echo "" >> results_oatpp
wrk -t2 -c20000 -d20s "http://127.0.0.1:8000/" >> results_oatpp
sleep 60

echo "running... connections: 25000"
echo "" >> results_oatpp
wrk -t2 -c25000 -d20s "http://127.0.0.1:8000/" >> results_oatpp
sleep 60

echo "running... connections: 30000"
echo "" >> results_oatpp
wrk -t2 -c30000 -d20s "http://127.0.0.1:8000/" >> results_oatpp
sleep 120

################################################################
## go
################################################################

echo "testing go"
> results_go
echo "running... connections: 2"
echo "" >> results_go
wrk -t2 -c2 -d20s "http://127.0.0.1:9000/" >> results_go
sleep 20

echo "running... connections: 10"
echo "" >> results_go
wrk -t2 -c10 -d20s "http://127.0.0.1:9000/" >> results_go
sleep 20

echo "running... connections: 50"
echo "" >> results_go
wrk -t2 -c50 -d20s "http://127.0.0.1:9000/" >> results_go
sleep 20

echo "running... connections: 100"
echo "" >> results_go
wrk -t2 -c100 -d20s "http://127.0.0.1:9000/" >> results_go
sleep 20

echo "running... connections: 500"
echo "" >> results_go
wrk -t2 -c500 -d20s "http://127.0.0.1:9000/" >> results_go
sleep 20

echo "running... connections: 1000"
echo "" >> results_go
wrk -t2 -c1000 -d20s "http://127.0.0.1:9000/" >> results_go
sleep 30

echo "running... connections: 2500"
echo "" >> results_go
wrk -t2 -c2500 -d20s "http://127.0.0.1:9000/" >> results_go
sleep 30

echo "running... connections: 5000"
echo "" >> results_go
wrk -t2 -c5000 -d20s "http://127.0.0.1:9000/" >> results_go
sleep 60

echo "running... connections: 10000"
echo "" >> results_go
wrk -t2 -c10000 -d20s "http://127.0.0.1:9000/" >> results_go
sleep 60

echo "running... connections: 15000"
echo "" >> results_go
wrk -t2 -c15000 -d20s "http://127.0.0.1:9000/" >> results_go
sleep 60

echo "running... connections: 20000"
echo "" >> results_go
wrk -t2 -c20000 -d20s "http://127.0.0.1:9000/" >> results_go
sleep 60

echo "running... connections: 25000"
echo "" >> results_go
wrk -t2 -c25000 -d20s "http://127.0.0.1:9000/" >> results_go
sleep 60

echo "running... connections: 30000"
echo "" >> results_go
wrk -t2 -c30000 -d20s "http://127.0.0.1:9000/" >> results_go

echo "finished!"
