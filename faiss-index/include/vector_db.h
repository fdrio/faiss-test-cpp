#include "service.h"
#include <grpcpp/grpcpp.h>
#include <iostream>
#include <string>

class VectorDB {
public:
  VectorDB(std::size_t dimension, std::string address,
           std::shared_ptr<grpc::ServerCredentials> credentials =
               grpc::InsecureServerCredentials());
  void start();

private:
  std::string address;
  grpc::ServerBuilder builder;
  FaissService faiss_service;
  std::unique_ptr<grpc::Server> server;
};
