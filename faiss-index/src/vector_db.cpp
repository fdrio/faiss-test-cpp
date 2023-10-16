#include "vector_db.h"

VectorDB::VectorDB(std::size_t dimension, std::string address,
                   std::shared_ptr<grpc::ServerCredentials> credentials)
    : address{address}, faiss_service{dimension}, server{nullptr} {
  this->builder.AddListeningPort(address, credentials);
  this->builder.RegisterService(&faiss_service);
}

void VectorDB::start() {
  this->server = builder.BuildAndStart();
  // TODO add logging library
  std::cout << "Starting server at: " << this->address << std::endl;
  this->server->Wait();
}
