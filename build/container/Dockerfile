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
    apt-get install -qqy default-jdk-headless ant python-minimal git clang-4.0 lldb-4.0 llvm-4.0 clang-format-4.0 lld-4.0 nasm
RUN git clone https://github.com/facebook/buck.git && \
    cd buck && \
    ant && \
    cd ..
ENV PATH="/buck/bin:${PATH}"
VOLUME /conurbation
EXPOSE 8080
WORKDIR /conurbation
CMD buck build kernel
