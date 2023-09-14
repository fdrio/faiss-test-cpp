#include "faiss/MetricType.h"
#include <cstdio>
#include <faiss/IndexFlat.h>
#include <proto/query_vector.pb.h> 
#include <cstddef>
#include <iostream>
#include <random>
#include <string>
#include <iostream>
#include <cstddef>
int main() {
  size_t d = 64;       // dimension
  size_t nb = 100000;  // database size
  size_t nq = 10000;   // nb of queries
  QueryVector q;
  std::cout<<"Size of query vector message "<< sizeof(q)<<std::endl;
  float* xb = new float[d * nb];
  float* xq = new float[d * nq];
  for (size_t i = 0; i < nb; i++) {
    for (size_t j = 0; j < d; j++)
      xb[d * i + j] = drand48();
    xb[d * i] += i / 1000.;
  }
  for (size_t i = 0; i < nq; i++) {
    for (size_t j = 0; j < d; j++)
      xq[d * i + j] = drand48();
    xq[d * i] += i / 1000.;
  }
    
  faiss::IndexFlatL2 index(d);
    std::string is_trained = index.is_trained ? "true" : "false";

  // Indexing
  {
    std::cout << "Index is trained: " << is_trained << std::endl;
    std::cout << "Total number of indexed vectors: " << index.ntotal
              << std::endl;
    std::cout << "Adding vectors to the index" << std::endl;
    index.add(nb, xb);
    std::cout << "Total number of indexed vectors: " << index.ntotal
              << std::endl;
  }

  // Searching
  {
        size_t k = 4;
        float * distances = new float[k*nq];
        faiss::idx_t * indices = new faiss::idx_t[k*nq];
        //use nq and xq to use all query vectors
        index.search(nq, xq, k, distances, indices); 
        
        // Print the vectors
        for(size_t i=0; i<k;i++){
            std::cout<<"[";
            for(size_t j=0; j<d;j++){
                std::string delimeter = "";
                if(j < d-1 ){
                    delimeter =" , ";
                }
                std::cout<<distances[i*k+j]<<delimeter;
            }
            std::cout<<"]"<<std::endl;
        }
        delete [] distances;
        delete [] indices;

    }
}
