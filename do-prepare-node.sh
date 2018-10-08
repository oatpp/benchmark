#!/bin/sh

apt-get update

apt-get install apache2-utils -y
apt-get install build-essential libssl-dev git -y

git clone https://github.com/wg/wrk.git wrk
cd wrk/
make
sudo cp wrk /usr/local/bin
cd ..

wget http://ftp.openbsd.org/pub/OpenBSD/LibreSSL/libressl-2.7.4.tar.gz
tar -xzvf libressl-2.7.4.tar.gz

cd libressl-2.7.4
./configure --prefix="/root/opt/libressl"
make
make install
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/root/opt/libressl/lib
cd ..


#git clone --recurse-submodules https://github.com/oatpp/benchmark
#ulimit -n 100000
#sysctl -w net.ipv4.ip_local_port_range="16196 60999"
#-D OATPP_ASYNC_HTTP_CONNECTION_HANDLER_THREAD_NUM_DEFAULT= 3 \