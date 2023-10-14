#include <faiss/IndexFlat.h>

#include <cstddef>
#include <memory>
#include <mutex>

#include "proto/faiss.grpc.pb.h"
#include "proto/faiss.pb.h"
class FaissService final : public RouteFaissIndex::Service {
 private:
  mutable std::mutex mutex;
  std::unique_ptr<faiss::IndexFlatL2> index;

 public:
  FaissService(std::size_t dimension);
  grpc::Status GetID(grpc::ServerContext* context,
                     const QueryRequest* req,
                     QueryResponse* resp);
};
