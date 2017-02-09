#include <iostream>
#include "src/Cafmod.h"
#include "src/processFunction.h"

DEFINE_string(input, "", "input caffemodel file");
DEFINE_string(txtout, "", "output txt file name like *.prototxt");
DEFINE_string(binout, "", "output binary file name like *.caffemodel");
DEFINE_double(power, 1.0, "the power");
DEFINE_string(layername, "", "layer name");

#ifndef GFLAGS_GFLAGS_H_
namespace gflags = google;
#endif  // GFLAGS_GFLAGS_H_

int main(int argc, char *argv[]) {

    FLAGS_alsologtostderr = 1;
    google::InitGoogleLogging(argv[0]);
    google::InstallFailureSignalHandler();
    gflags::SetVersionString("1.0");
    gflags::SetUsageMessage("usage: ./ReadAndWriteCaffemodel.bin [-flags]");
    gflags::ParseCommandLineFlags(&argc, &argv, false);
    if (argc == 1) {
        gflags::ShowUsageWithFlagsRestrict(argv[0], "src/main");
        return -1;
    }
    CHECK_GT(FLAGS_input.size(), 0) << "no input file ";
    CHECK_GT(FLAGS_binout.size() + FLAGS_txtout.size(), 0) << "no output file";

    readCafmod rc(FLAGS_input);//输入的权值文件

    caffe::NetParameter *proto = rc.ReadProtoFromBinaryFile();

    for (int i = 0; i < proto->layer_size(); i++) {
        caffe::LayerParameter *thisLayer = proto->mutable_layer(i);
        if (thisLayer->name() == FLAGS_layername) {
            for (int j = 0; j < thisLayer->blobs_size(); j++) {
                caffe::BlobProto *thisBlob = thisLayer->mutable_blobs(j);
                for (int k = 0; k < thisBlob->data_size(); k++) {
                    float thisData = thisBlob->data(k);
                    float processedData = myProcessFunction(thisData, (float) FLAGS_power);
                    thisBlob->set_data(k, processedData);
                }
            }
        }
    }

    for (int i = 0; i < proto->layers_size(); i++) {
        caffe::V1LayerParameter *thisLayer = proto->mutable_layers(i);
        if (thisLayer->name() == FLAGS_layername) {
            for (int j = 0; j < thisLayer->blobs_size(); j++) {
                caffe::BlobProto *thisBlob = thisLayer->mutable_blobs(j);
                for (int k = 0; k < thisBlob->data_size(); k++) {
                    float thisData = thisBlob->data(k);
                    float processedData = myProcessFunction(thisData, (float) FLAGS_power);
                    thisBlob->set_data(k, processedData);
                }
            }
        }
    }

    writeCafmod wc(proto);
    if (FLAGS_txtout.size() > 0)
        wc.WriteProtoToTextFile(FLAGS_txtout);//生成文本文件
    if (FLAGS_binout.size() > 0)
        wc.WriteProtoToBinaryFile(FLAGS_binout);//生成二进制文件
    return 0;
}
