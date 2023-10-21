#include "service.h"
#include "constants.h"
#include <algorithm>
#include <cstdio>
#include <exception>
#include <iostream>
FaissService::FaissService(std::size_t dimension) {
  this->index = std::make_unique<faiss::IndexFlatL2>(dimension);
}

::grpc::Status FaissService::Index(grpc::ServerContext *context,
                                   grpc::ServerReader<::Vector> *reader,
                                   ::google::protobuf::Empty *resp) {
  Vector vec;
  while (reader->Read(&vec)) {
    auto values = vec.mutable_values()->data();
    std::vector<float> v(values, values + DIMENSION);
    std::copy(v.begin(), v.end(), std::back_inserter(this->collector));
  }
  this->index->add(DATABASE_SIZE, this->collector.data());
  return ::grpc::Status::OK;
}

grpc::Status FaissService::Query(grpc::ServerContext *context,
                                 const Vector *vector,
                                 grpc::ServerWriter<Indices> *writer) {

  auto query_vec_values = vector->values().data();
  faiss::idx_t *result_indices = new faiss::idx_t[K_NEIGHBORS * NUM_QUERIES];
  float *result_distances = new float[K_NEIGHBORS * NUM_QUERIES];
  this->index->search(NUM_QUERIES, query_vec_values, K_NEIGHBORS,
                      result_distances, result_indices);
  Indices indices;
  for (int j = 0; j < K_NEIGHBORS; j++)
    indices.mutable_values()->Add(result_indices[j]);
  grpc::WriteOptions options;
  writer->WriteLast(indices, options);
  delete[] result_indices;
  delete[] result_distances;
  return ::grpc::Status::OK;
}
