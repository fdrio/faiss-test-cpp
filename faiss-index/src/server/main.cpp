#include "vector_db.h"


//void init_server(){
//size_t d = 64;      // dimension
//  size_t nb = 100000; // database size
//  size_t nq = 10000;  // nb of queries
//  // QueryVector q;
//  // std::cout << "Size of query vector message " << sizeof(q) << std::endl;
//  float *xb = new float[d * nb];
//  float *xq = new float[d * nq];
//  for (size_t i = 0; i < nb; i++) {
//    for (size_t j = 0; j < d; j++)
//      xb[d * i + j] = drand48();
//    xb[d * i] += i / 1000.;
//  }
//  for (size_t i = 0; i < nq; i++) {
//    for (size_t j = 0; j < d; j++)
//      xq[d * i + j] = drand48();
//    xq[d * i] += i / 1000.;
//  }
//
//  //vector_db.start_index();
//  const std::string server_address{"0.0.0.0:50051"};
//  FaissService faiss_server(d);
//  grpc::ServerBuilder builder;
//  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
//  builder.RegisterService(&faiss_server);
//  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
//  std::cout<<"Starting RPC Server at: "<< server_address<<std::endl;
//  server->Wait(); 
//
//}


int main() {
    std::size_t dimension = 64;
    const std::string server_address{"0.0.0.0:50051"};
    VectorDB vector_db(dimension, server_address, grpc::InsecureServerCredentials());
    vector_db.start();
    //init_server();      
}


    //RouteFaissIndexImpl faiss_rpc_server(server_address); 
    //faiss::IndexFlatL2 index(d);
  //index.is_trained ? "true" : "false";

  //// Indexing
  //{
  //  std::cout << "Index is trained: " << is_trained << std::endl;
  //  std::cout << "Total number of indexed vectors: " << index.ntotal
  //            << std::endl;
  //  std::cout << "Adding vectors to the index" << std::endl;
  //  index.add(nb, xb);
  //  std::cout << "Total number of indexed vectors: " << index.ntotal
  //            << std::endl;
  //}

  // Searching
  //{
  //  size_t k = 4;
  //  float *distances = new float[k * nq];
  //  faiss::idx_t *indices = new faiss::idx_t[k * nq];
  //  // use nq and xq to use all query vectors
  //  index.search(nq, xq, k, distances, indices);

  //  // Print the vectors
  //  for (size_t i = 0; i < k; i++) {
  //    std::cout << "[";
  //    for (size_t j = 0; j < d; j++) {
  //      std::string delimeter = "";
  //      if (j < d - 1) {
  //        delimeter = " , ";
  //      }
  //      std::cout << distances[i * k + j] << delimeter;
  //    }
  //    std::cout << "]" << std::endl;
  //  }
  //  delete[] distances;
  //  delete[] indices;
  //}

