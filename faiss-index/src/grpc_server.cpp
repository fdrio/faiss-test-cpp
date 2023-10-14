#include "grpc_server.h"

FaissService::FaissService(std::size_t dimension) {
  this->index = std::make_unique<faiss::IndexFlatL2>(dimension);
}

grpc::Status FaissService::GetID(grpc::ServerContext* context,
                                 const QueryRequest* req,
                                 QueryResponse* resp) {
  int32_t id = req->id();
  resp->set_id(id);
  return grpc::Status::OK;
}
