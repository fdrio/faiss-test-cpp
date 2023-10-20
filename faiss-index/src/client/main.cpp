#include <cstdlib>
#include <iostream>
#include <memory>
#include <grpc++/grpc++.h>
#include <cstddef>
#include <vector>
#include "proto/faiss.grpc.pb.h"
#include "proto/faiss.pb.h"
#include "constants.h"
class FaissClient{
    public:
        FaissClient(std::shared_ptr<grpc::Channel> channel): stub{RouteFaissIndex::NewStub(channel)}{}
        ::google::protobuf::Empty Index(const std::vector<Vector> data){
            grpc::ClientContext context;
            ::google::protobuf::Empty response;
            auto writer = stub->Index(&context,&response);
            for(const auto& vector: data){
                writer->Write(vector);
                    
            }
            writer->WritesDone();
            ::grpc::Status status = writer->Finish();
            if(status.ok()){
                std::cout<<"OK"<<std::endl;
            }else{
                std::cerr<<"RPC failed"<<std::endl;
            }
            return response;
        }
    private:
        std::unique_ptr<RouteFaissIndex::Stub> stub; 

};


int main(){
    const std::string target = "0.0.0.0:50051";

    std::shared_ptr<grpc::Channel> channel = grpc::CreateChannel(target, grpc::InsecureChannelCredentials());
    
    FaissClient client = FaissClient{channel};
    std::vector<Vector> data;
    for(std::size_t i=0; i<DATABSE_SIZE;i++){
        Vector vec;
        for(std::size_t j=0; j<DIMENSION;j++)
            vec.mutable_values()->Add(drand48()); 
       
        data.emplace_back(vec);

        
        //data.mutable_data()->AddAllocated(vec.release());
        //Building the dataset

        //auto mutdata = data.mutable_data();
        //Vector* vec = query_vec.mutable_query();
        //vec->set_id(i);
        //for(std::size_t j=1; j<=10; j++){
        //    vec->add_values(double(i*j));
        //}
        //Response response = client.Index(query_vec);
    }
    client.Index(data);

}
