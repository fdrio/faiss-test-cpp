FROM debian:latest as build

RUN apt update && apt upgrade 
RUN apt install build-essential clang protobuf-compiler cmake libblas-dev libomp-dev liblapack-dev swig python3-dev python3-pip python3-venv git -y
RUN python3 -m venv /opt/env
RUN . /opt/env/bin/activate
RUN ./opt/env/bin/pip3 install numpy
ENV VIRTUAL_ENV /opt/env
ENV PATH "$VIRTUAL_ENV/bin:$PATH"
RUN mkdir projects
WORKDIR projects
RUN git init
COPY ./faiss-index /projects/faiss-index
RUN git submodule add https://github.com/nlohmann/json.git faiss-index/lib/json
RUN git submodule add https://github.com/facebookresearch/faiss.git faiss-index/lib/faiss
RUN git submodule add https://github.com/protocolbuffers/protobuf.git faiss-index/lib/protobuf
RUN mkdir faiss-index/build
# Python sucks
RUN cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \ 
    -DFAISS_ENABLE_GPU=OFF \
    -DCMAKE_FIND_PACKAGE_PREFER_CONFIG=TRUE \
    -B faiss-index/build \ 
    ./faiss-index
RUN cd faiss-index/build && make -j

FROM debian:stable-slim
RUN apt update && apt upgrade 
RUN apt install build-essential libblas-dev libomp-dev liblapack-dev swig python3-dev python3-pip python3-venv -y
COPY --from=build /projects/faiss-index/build/index_and_search /
CMD ["/index_and_search"]
