FROM ubuntu:focal

ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update

#lsb-core software-properties-common gpg-agent zlib1g-dev \
#ninja-build unzip python3-pip xz-utils \
RUN apt-get install -yq --no-install-recommends \
  apt-transport-https vim gcc g++ binutils ca-certificates \
  gdb cmake gpg-agent lsb-core software-properties-common \
  git file wget curl sudo python3 make

RUN wget https://apt.llvm.org/llvm.sh -O /tmp/llvm.sh
RUN chmod +x /tmp/llvm.sh
RUN /tmp/llvm.sh 13
RUN rm -rf /tmp/llvm.sh

RUN apt-get autoremove -yq
RUN apt-get clean -yqq

RUN useradd -ms /bin/bash tp
WORKDIR /home/tp
RUN adduser tp sudo
# Don't do this at home
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers
USER tp
