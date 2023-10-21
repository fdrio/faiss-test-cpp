#include <faiss/IndexFlat.h>

#include "proto/faiss.grpc.pb.h"
#include "proto/faiss.pb.h"
#include <cstddef>
#include <iostream>
#include <memory>
#include <mutex>
class FaissService final : public RouteFaissIndex::Service {
private:
  mutable std::mutex mutex;
  std::unique_ptr<faiss::IndexFlatL2> index;
  std::vector<float> collector;

public:
  FaissService(std::size_t dimension);
  grpc::Status Index(grpc::ServerContext *context,
                     grpc::ServerReader<::Vector> *reader,
                     ::google::protobuf::Empty *resp);
  grpc::Status Query(grpc::ServerContext *context, const Vector *vector,
                     grpc::ServerWriter<Indices> *writer);
};
