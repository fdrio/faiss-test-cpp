#include "constants.h"
#include "proto/faiss.grpc.pb.h"
#include "proto/faiss.pb.h"
#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <grpc++/grpc++.h>
#include <iostream>
#include <memory>
#include <vector>
class FaissClient {
public:
  FaissClient(std::shared_ptr<grpc::Channel> channel)
      : stub{RouteFaissIndex::NewStub(channel)} {}
  ::google::protobuf::Empty Index(const std::vector<Vector> data) {
    grpc::ClientContext context;
    ::google::protobuf::Empty response;
    auto writer = stub->Index(&context, &response);
    for (const auto &vector : data) {
      writer->Write(vector);
    }
    writer->WritesDone();
    ::grpc::Status status = writer->Finish();
    if (status.ok()) {
      std::cout << "OK" << std::endl;
    } else {
      std::cerr << "RPC failed" << std::endl;
    }
    return response;
  }

  std::unique_ptr<::grpc::ClientReader<Indices>>
  Query(::grpc::ClientContext *context, Vector vector) {
    std::unique_ptr<grpc::ClientReader<Indices>> reader(
        stub->Query(context, vector));
    Indices res;
    while (reader->Read(&res)) {
      std::cout << "Closest K = " << K_NEIGHBORS << " are at indices: ";
      for (const auto &val : res.values()) {
        std::cout << val << " ";
      }
      std::cout << std::endl;
    }

    grpc::Status status = reader->Finish();
    if (status.ok()) {
      std::cout << "Server streaming call completed successfully." << std::endl;
    } else {
      std::cerr << "Error: " << status.error_code() << ": "
                << status.error_message() << std::endl;
    }

    return reader;
  }

private:
  std::unique_ptr<RouteFaissIndex::Stub> stub;
};

int main() {
  const std::string target = "0.0.0.0:50051";
  std::shared_ptr<grpc::Channel> channel =
      grpc::CreateChannel(target, grpc::InsecureChannelCredentials());
  FaissClient client = FaissClient{channel};
  srand(static_cast<unsigned>(time(nullptr)));
  std::vector<Vector> data;
  for (std::size_t i = 0; i < DATABSE_SIZE; i++) {
    Vector vec;
    for (std::size_t j = 0; j < DIMENSION; j++)
      vec.mutable_values()->Add(static_cast<float>(rand()) /
                                static_cast<float>(RAND_MAX));
    data.emplace_back(vec);
  }
  // Index
  client.Index(data);

  // Query
  Vector query_vector;
  for (std::size_t j = 0; j < DIMENSION; j++)
    query_vector.mutable_values()->Add(static_cast<float>(rand()) /
                                       static_cast<float>(RAND_MAX));

  grpc::ClientContext context;
  client.Query(&context, query_vector);
}
