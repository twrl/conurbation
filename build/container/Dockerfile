FROM ubuntu:zesty
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update && \
    apt-get install -qqy curl apt-utils
RUN echo "deb http://apt.llvm.org/zesty/ llvm-toolchain-zesty main" >> /etc/apt/sources.list.d/llvm.list && \
    echo "deb-src http://apt.llvm.org/zesty/ llvm-toolchain-zesty main" >> /etc/apt/sources.list.d/llvm.list && \
    echo "deb http://apt.llvm.org/zesty/ llvm-toolchain-zesty-4.0 main" >> /etc/apt/sources.list.d/llvm.list && \
    echo "deb-src http://apt.llvm.org/zesty/ llvm-toolchain-zesty-4.0 main" >> /etc/apt/sources.list.d/llvm.list && \
    curl http://apt.llvm.org/llvm-snapshot.gpg.key | apt-key add - && \
    apt-get update && \
    apt-get install -qqy default-jdk-headless ant python git clang-4.0 lldb-4.0 llvm-4.0 clang-format-4.0 lld-4.0 nasm autoconf automake libpcre2-dev libpcre3-dev
RUN apt-get install -y python-dev make
ENV CC=clang-4.0 CXX=clang++-4.0 CFLAGS=-w LDSHARED="clang-4.0 -pthread -shared -Wl,-O1 -Wl,-Bsymbolic-functions -Wl,-Bsymbolic-functions -Wl,-z,relro -fno-strict-aliasing -DNDEBUG -g -fwrapv -O2 -Wall -Wstrict-prototypes -Wdate-time -D_FORTIFY_SOURCE=2 -g -fdebug-prefix-map=/build/python2.7-ZZaKJ6/python2.7-2.7.13=. -fstack-protector -Wformat -Werror=format-security -fuse-ld=bfd -w -Wall -Wextra -Wdeclaration-after-statement -g -gdwarf-2 -fno-omit-frame-pointer"
RUN git clone https://github.com/facebook/watchman.git && \
    cd watchman && \
    git checkout v4.7.0 && \
    ./autogen.sh && \
    ./configure && \
    make && \
    make install && \
    cd ..
RUN git clone https://github.com/facebook/buck.git && \
    cd buck && \
    git checkout v2017.03.29.01 &&\
    ant && \
    cd ..
ENV PATH="/buck/bin:${PATH}"
VOLUME /conurbation
EXPOSE 8080
WORKDIR /conurbation
CMD buck build all
