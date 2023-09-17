## Instructions

#### MacOS
##### Dependencies: 
- openmp (use brew install libomp)
- swig (use brew install swig)
##### Build
```./build_mac_bin.sh```

##### Run 
```./faiss-index/build/index_and_search```



#### Linux
##### Dependencies: 
- docker

##### Build
```sudo docker build -t faiss:latest .``` 

##### Run 
```sudo docker run --rm faiss:latest``` 

#### Windows
Install linux and GOTO to linux instructions 



### TODO
- [X] add dockerfile
- keep index alive in separate thread
-  index [sift dataset](http://corpus-texmex.irisa.fr/) 
-  test other indices
-  add gpu 
-  add rpc (use either grpc or capnproto)
-  add tests
