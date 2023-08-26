## Instructions
`
git clone https://github.com/fdrio/faiss-test-cpp.git
cd faiss-test-cpp
git submodule --init --recursive
mkdir build
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 -DFAISS_ENABLE_GPU=OFF -B build .
cd build 
make -j
./index_and_search
`
![Example Output] ./screenshot.png

### TODO
- test other indices
- add gpu 
- add rpc (use either grpc or capnproto)
