#include "src/Cafmod.h"

const int kProtoReadBytesLimit = INT_MAX;  // Max size of 2 GB minus 1 byte.

readCafmod::readCafmod(string filename) {
    this->filename = filename;
}

caffe::NetParameter *readCafmod::ReadProtoFromBinaryFile() {
    const char *filename = this->filename.c_str();

    int fd = open(filename, O_RDONLY);
    CHECK_NE(fd, -1) << "File not found: " << filename;
    ZeroCopyInputStream *raw_input = new FileInputStream(fd);
    CodedInputStream *coded_input = new CodedInputStream(raw_input);
    coded_input->SetTotalBytesLimit(kProtoReadBytesLimit, 536870912);

    bool success = this->proto.ParseFromCodedStream(coded_input);

    delete coded_input;
    delete raw_input;
    close(fd);
    return &(this->proto);
}

caffe::NetParameter *readCafmod::ReadProtoFromTextFile() {
    const char *filename = this->filename.c_str();
    int fd = open(filename, O_RDONLY);
    CHECK_NE(fd, -1) << "File not found: " << filename;
    FileInputStream *input = new FileInputStream(fd);
    google::protobuf::TextFormat::Parse(input, &(this->proto));
    delete input;
    close(fd);
    return &(this->proto);
}

string readCafmod::getFilename() {
    return this->filename;
}

void readCafmod::setFilename(string filename) {
    this->filename = filename;
}

writeCafmod::writeCafmod(caffe::NetParameter *param) {
    this->param = param;
}

void writeCafmod::WriteProtoToBinaryFile(string filename) {
    fstream output(filename.c_str(), ios::out | ios::trunc | ios::binary);
    CHECK(param->SerializeToOstream(&output));
}

void writeCafmod::WriteProtoToTextFile(string filename) {
    int fd = open(filename.c_str(), O_WRONLY | O_CREAT | O_TRUNC, 0644);
    FileOutputStream *output = new FileOutputStream(fd);
    CHECK(google::protobuf::TextFormat::Print(*param, output));
    delete output;
    close(fd);
}

void writeCafmod::setParam(caffe::NetParameter *param) {
    this->param = param;
}

caffe::NetParameter *writeCafmod::getParam() {
    return this->param;
}