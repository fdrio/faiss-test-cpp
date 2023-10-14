#include <grpcpp/grpcpp.h>
#include <iostream>
#include <string>

#include "grpc_server.h"
class VectorDB {
 public:
  VectorDB(std::size_t dimension,
           std::string address,
           std::shared_ptr<grpc::ServerCredentials> credentials);
  void start();

 private:
  std::string address;
  grpc::ServerBuilder builder;
  FaissService faiss_service;
  std::unique_ptr<grpc::Server> server;
};
