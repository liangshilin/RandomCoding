FROM ubuntu:20.04

RUN /bin/bash -c 'mv /etc/apt/sources.list /etc/apt/sources.list_backup'

COPY ./grpc.zip /root/
COPY ./sources.list /etc/apt/

ARG DEBIAN_FRONTEND=noninteractive
RUN /bin/bash -c 'apt-get update'
RUN /bin/bash -c 'apt-get -y install build-essential autoconf libtool pkg-config; \
apt-get -y install cmake git; \
apt-get -y install unzip; \
cd /root/ && unzip grpc.zip' 

RUN /bin/bash -c 'apt-get -y install build-essential autoconf libtool pkg-config; apt-get install -y libssl-dev'

# git clone -b 1.33.2 https://github.com/grpc/grpc;

RUN /bin/bash -c 'cd /root/grpc && mkdir -p "cmake/build"; \
cd /root/grpc/cmake/build && cmake -DCMAKE_BUILD_TYPE=Release -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DgRPC_SSL_PROVIDER=package ../.. && \
make -j4 install'