#include <iostream>
#include "proto/faiss.pb.h"
#include "proto/faiss.grpc.pb.h"
#include <memory>
#include <grpc++/grpc++.h>
#include <cstddef>
#include <vector>

class FaissClient{
    public:
        FaissClient(std::shared_ptr<grpc::Channel> channel): stub{RouteFaissIndex::NewStub(channel)}{}
        Response Index(const QueryVector& query){
            grpc::ClientContext context;
            Response response;
            grpc::Status status = stub->Index(&context, query, &response);

            if(status.ok()){
                std::cout<<"Result: "<< response.results_size()<<std::endl;
            }else{
                std::cerr<<"RPC failed"<<std::endl;
            }
            return response;
        }
    private:
        std::unique_ptr<RouteFaissIndex::Stub> stub; 

};


int main(){
    std::string target = "0.0.0.0:50051";
    
    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(target, grpc::InsecureChannelCredentials());
    
    FaissClient client = FaissClient{channel};
    
    for(std::size_t i=1; i<=10;i++){
        QueryVector query_vec;
        Vector* vec = query_vec.mutable_query();
        vec->set_id(i);
        for(std::size_t j=1; j<=10; j++){
            vec->add_values(double(i*j));
        }
        Response response = client.Index(query_vec);
    }

}
