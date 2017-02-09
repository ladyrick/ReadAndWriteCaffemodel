
#ifndef READANDWRITECAFFEMODEL_READCAFMOD_H
#define READANDWRITECAFFEMODEL_READCAFMOD_H

#include <string>
#include <fstream>
#include <fcntl.h>
#include <glog/logging.h>
#include <google/protobuf/message.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/io/zero_copy_stream_impl.h>
#include <google/protobuf/text_format.h>
#include <google/protobuf/message.h>
#include "proto/caffe.pb.h"


using std::string;
using std::fstream;
using std::ios;

using google::protobuf::io::FileInputStream;
using google::protobuf::io::FileOutputStream;
using google::protobuf::io::ZeroCopyInputStream;
using google::protobuf::io::CodedInputStream;
using google::protobuf::io::ZeroCopyOutputStream;
using google::protobuf::io::CodedOutputStream;
using google::protobuf::Message;


class readCafmod {
private:
    caffe::NetParameter proto;
    string filename;

public:
    readCafmod(string filename);

    caffe::NetParameter *ReadProtoFromBinaryFile();

    caffe::NetParameter *ReadProtoFromTextFile();

    string getFilename();

    void setFilename(string filename);
};

class writeCafmod {
private:
    caffe::NetParameter *param;
    string filename;

public:
    writeCafmod(caffe::NetParameter *param);

    void WriteProtoToBinaryFile(string filename);

    void WriteProtoToTextFile(string filename);

    void setParam(caffe::NetParameter *param);

    caffe::NetParameter *getParam();
};


#endif //READANDWRITECAFFEMODEL_READCAFMOD_H
