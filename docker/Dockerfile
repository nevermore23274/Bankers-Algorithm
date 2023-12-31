# Specifies base image
FROM ubuntu:22.04

# Timezone config
ENV DEBIAN_FRONTEND=noninteractive 
ENV TZ=America/New_York
RUN ln -snf /usr/share/zoneinfo/$TZ /etc/localtime && \
    echo $TZ > /etc/timezone

# Install C++ tools
RUN apt-get update -y && \
    apt-get install -y wget build-essential libssl-dev gdb valgrind strace ltrace && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Install static version of CMAKE
RUN wget https://github.com/Kitware/CMake/releases/download/v3.27.7/cmake-3.27.7.tar.gz && \
    tar -xzvf cmake-3.27.7.tar.gz && \
    cd cmake-3.27.7 && \
    ./bootstrap && \
    make -j$(nproc) && \
    make install && \
    cd .. && \
    rm -rf cmake-3.27.7 && \
    rm cmake-3.27.7.tar.gz

# Set the default working directory
WORKDIR /assignment4

# Set the script as the entrypoint
ENTRYPOINT ["/assignment4/auto-run.sh"]