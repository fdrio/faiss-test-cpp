#include "service.h"
FaissService::FaissService(std::size_t dimension) {
  this->index = std::make_unique<faiss::IndexFlatL2>(dimension);
}

grpc::Status FaissService::Index(grpc::ServerContext *context, const QueryVector *req,Response *resp){
    const Vector& query = req->query();
    for(const auto& value: query.values()){
        std::cout<<value<<" ";
    }
    std::cout<<std::endl;
    return grpc::Status::OK
    ;
}
