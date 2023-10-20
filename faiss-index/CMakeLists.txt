cmake_minimum_required(VERSION 3.10)
project(faiss-rpc-index)

set(CMAKE_CXX_STANDARD 11)
set(SERVER_BIN_NAME db_server)
set(CLIENT_BIN_NAME client)
set(SRC_DIR ${CMAKE_SOURCE_DIR}/src )
set(LIB_DIR ${CMAKE_SOURCE_DIR}/lib)
set(TESTS_DIR ${CMAKE_SOURCE_DIR}/tests)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)
set(PROTO_DIR ${CMAKE_SOURCE_DIR}/proto)
set(PROTOC_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto_gen)
set (CMAKE_CXX_STANDARD 14)

file(GLOB SOURCE_FILES ${SRC_DIR}/*.cpp)
file(GLOB PROTO_FILES ${PROTO_DIR}/*.proto)
file(MAKE_DIRECTORY ${PROTOC_OUT_DIR})


find_package (Python COMPONENTS Interpreter Development NumPy)
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)

add_executable(${SERVER_BIN_NAME} ${SOURCE_FILES} ${SRC_DIR}/server/main.cpp)
add_executable(${CLIENT_BIN_NAME} ${SOURCE_FILES} ${SRC_DIR}/client/main.cpp)
add_subdirectory(${LIB_DIR}/json)
add_subdirectory(${LIB_DIR}/faiss)

protobuf_generate(TARGET ${SERVER_BIN_NAME} LANGUAGE cpp PROTOC_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto_gen PROTOS ${PROTO_FILES})
protobuf_generate(
    TARGET ${SERVER_BIN_NAME} 
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=\$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
    # PLUGIN_OPTIONS "generate_mock_code=true"
    PROTOS ${PROTO_FILES}
    PROTOC_OUT_DIR "${PROTOC_OUT_DIR}"
)

protobuf_generate(TARGET ${CLIENT_BIN_NAME} LANGUAGE cpp PROTOC_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto_gen PROTOS ${PROTO_FILES})
protobuf_generate(
    TARGET ${CLIENT_BIN_NAME} 
    LANGUAGE grpc
    GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
    PLUGIN "protoc-gen-grpc=\$<TARGET_FILE:gRPC::grpc_cpp_plugin>"
    # PLUGIN_OPTIONS "generate_mock_code=true"
    PROTOS ${PROTO_FILES}
    PROTOC_OUT_DIR "${PROTOC_OUT_DIR}"
)



target_include_directories(${SERVER_BIN_NAME} PRIVATE ${PROTOC_OUT_DIR})
target_include_directories(${SERVER_BIN_NAME} PRIVATE ${INCLUDE_DIR})
target_link_libraries(${SERVER_BIN_NAME} PRIVATE nlohmann_json::nlohmann_json faiss protobuf::libprotobuf gRPC::grpc++ gRPC::grpc++_reflection)
target_compile_options(${SERVER_BIN_NAME} PRIVATE -Wall -Wextra)

target_include_directories(${CLIENT_BIN_NAME} PRIVATE ${PROTOC_OUT_DIR})
target_include_directories(${CLIENT_BIN_NAME} PRIVATE ${INCLUDE_DIR})
target_link_libraries(${CLIENT_BIN_NAME} PRIVATE nlohmann_json::nlohmann_json faiss protobuf::libprotobuf gRPC::grpc++ gRPC::grpc++_reflection)
target_compile_options(${CLIENT_BIN_NAME} PRIVATE -Wall -Wextra)
