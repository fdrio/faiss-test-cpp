#include <faiss/IndexFlat.h>

#include <cstddef>
#include <memory>
#include <mutex>
#include <iostream>
#include "proto/faiss.grpc.pb.h"
#include "proto/faiss.pb.h"
class FaissService final : public RouteFaissIndex::Service {
private:
  mutable std::mutex mutex;
  std::unique_ptr<faiss::IndexFlatL2> index;

public:
    FaissService(std::size_t dimension);
    grpc::Status Index(grpc::ServerContext *context, grpc::ServerReader<::Vector> *req, ::google::protobuf::Empty *resp); 
};
