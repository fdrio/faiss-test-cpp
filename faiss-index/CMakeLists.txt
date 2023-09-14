cmake_minimum_required(VERSION 3.10)
project(faiss-test-cpp)

set(CMAKE_CXX_STANDARD 11)
set(BIN_NAME index_and_search)
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


find_package (Python COMPONENTS Interpreter Development)
find_package(Protobuf REQUIRED)

add_executable(${BIN_NAME} ${SOURCE_FILES})
add_subdirectory(${LIB_DIR}/json)
add_subdirectory(${LIB_DIR}/faiss)

protobuf_generate(TARGET ${BIN_NAME} LANGUAGE cpp PROTOC_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto_gen PROTOS ${PROTO_FILES})

target_include_directories(${BIN_NAME} PRIVATE ${PROTOC_OUT_DIR})
target_include_directories(${BIN_NAME} PRIVATE ${INCLUDE_DIR})
target_link_libraries(${BIN_NAME} PRIVATE nlohmann_json::nlohmann_json faiss protobuf::libprotobuf)
target_compile_options(${BIN_NAME} PRIVATE -Wall -Wextra)
