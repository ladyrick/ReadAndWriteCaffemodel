cmake_minimum_required(VERSION 2.6)
project(ReadAndWriteCaffemodel)

set(CMAKE_CXX_STANDARD 11)

#预先编译proto文件，生成.cc和.h文件。
add_custom_command(
        OUTPUT ${PROJECT_BINARY_DIR}/proto/caffe.pb.cc ${PROJECT_BINARY_DIR}/proto/caffe.pb.h
        COMMAND mkdir -p proto && protoc -I=${PROJECT_SOURCE_DIR}/proto/ ${PROJECT_SOURCE_DIR}/proto/caffe.proto --cpp_out=${PROJECT_BINARY_DIR}/proto
)
#将生成文件的目录添加进include目录
include_directories(${PROJECT_BINARY_DIR})
include_directories(${PROJECT_SOURCE_DIR})


add_library(proto proto/caffe.pb.cc proto/caffe.pb.h)

aux_source_directory(src SOURCE_FILES)

add_executable(ReadAndWriteCaffemodel.bin ${SOURCE_FILES})

target_link_libraries(ReadAndWriteCaffemodel.bin glog gflags protobuf proto)