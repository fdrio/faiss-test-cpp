#include "service.h"
#include <grpcpp/support/status.h>
FaissService::FaissService(std::size_t dimension) {
  this->index = std::make_unique<faiss::IndexFlatL2>(dimension);
}

grpc::Status FaissService::Index(grpc::ServerContext *context, const DataSet *req, ::google::protobuf::Empty *resp){
    auto data = req->data();
    for (const auto& vec: data){
       for(const auto& val: vec.values()){
            std::cout<<val<< " ";
        }
        std::cout<<std::endl;
    }

    return grpc::Status::OK;
    //const Vector& query = req->query();
    //for(const auto& value: query.values()){
    //    std::cout<<value<<" ";
    //}
    //std::cout<<std::endl;
    //return grpc::Status::OK
    //;
}
