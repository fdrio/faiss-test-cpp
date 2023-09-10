git submodule update --init --recursive
cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=1 \
    -DFAISS_ENABLE_GPU=OFF\
    -DCMAKE_FIND_PACKAGE_PREFER_CONFIG=TRUE\
    -DCMAKE_CXX_COMPILER="$CXX"\
    -DCMAKE_C_COMPILER="$CC"\
    -DOpenMP_C_LIB_NAMES="omp" \
    -DOpenMP_omp_LIBRARY="/usr/local/opt/libomp/lib/libomp.dylib" \
    -DOpenMP_CXX_LIB_NAMES="omp" -DOpenMP_C_FLAGS=-fopenmp=libomp\
    -DOpenMP_CXX_FLAGS=-fopenmp=libomp\
    -B ./faiss-index/build\
    ./faiss-index
cd faiss-index/build && make -j && cd -
