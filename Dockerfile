FROM gcc:11.1.0

WORKDIR "/usr/bin"

RUN wget https://github.com/Kitware/CMake/releases/download/v3.26.3/cmake-3.26.3.tar.gz \
&& tar -xf cmake-3.26.3.tar.gz && rm cmake-3.26.3.tar.gz && cd cmake-3.26.3 && ./configure && make && make install

RUN wget https://github.com/westes/flex/files/981163/flex-2.6.4.tar.gz \
&& tar -xf flex-2.6.4.tar.gz && rm flex-2.6.4.tar.gz && cd flex-2.6.4 && ./configure && make && make install

RUN wget https://ftp.gnu.org/gnu/bison/bison-3.8.tar.gz \
&& tar -xf bison-3.8.tar.gz && rm bison-3.8.tar.gz && cd bison-3.8 && ./configure && make && make install

WORKDIR "/root"