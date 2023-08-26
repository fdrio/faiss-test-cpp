## Instructions
```
git clone https://github.com/fdrio/faiss-test-cpp.git
cd faiss-test-cpp
git submodule --init --recursive
mkdir build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DFAISS_ENABLE_GPU=OFF -B build .
cd build 
make -j
./index_and_search

```

### TODO
- index [sift dataset](http://corpus-texmex.irisa.fr/) 
- test other indices
- add gpu 
- add rpc (use either grpc or capnproto)
