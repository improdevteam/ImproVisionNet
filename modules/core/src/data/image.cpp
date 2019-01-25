// std
#include <fstream>
#include <filesystem>
#include <memory>

// opencv
#include <opencv2/highgui.hpp>

// impro
#include <impro/data/image.hpp>

using namespace std;
using namespace cv;

namespace impro { namespace data
{

shared_ptr<Data> Image::newPtr()
{
    Image *data = new Image();
    return shared_ptr<Data>(data);
}

shared_ptr<Data> Image::clone()
{
    Image *data = new Image();
    data->mat_ = mat_.clone();
    return shared_ptr<Data>(data);
}

void Image::clone(Data &data)
{
    Image &data__ = dynamic_cast<Image&>(data);
    data__.mat_ = mat_.clone();
}

void Image::save(const string &dir,
                 const string &id)
{
    string fullPath(dir);
    fullPath.append("/").append(id);
    imwrite(fullPath.c_str(), mat_);
}

void Image::load(const string &dir,
                 const string &id)
{
    string fullPath(dir);
    fullPath.append("/").append(id);
    mat_ = imread(fullPath.c_str(), IMREAD_ANYCOLOR);
}

void Image::remove(const string &dir,
                   const string &id)
{
    std::string fullPathToDelete(dir);
    fullPathToDelete.append("/").append(id);
    filesystem::path pathToDelete(fullPathToDelete);
    filesystem::remove(pathToDelete);
}

uint Image::serialize(std::vector<uchar> &raw,
                      uint offset)
{
    vector<uchar> bufMat;
    imencode(".jpg", mat_, bufMat);
    uint nBufMat = bufMat.size();
    uint nNBufMat = sizeof(nBufMat);
    uchar *ptrNBufMat = reinterpret_cast<uchar*>(&nBufMat);

    for(uint i = 0; i < nNBufMat; ++i)
        raw.push_back(ptrNBufMat[i]);
    for(uint i = 0; i < nBufMat; ++i)
        raw.push_back(bufMat.at(i));

    return offset + nNBufMat + nBufMat;
}

uint Image::deserialize(std::vector<uchar> &raw,
                        uint offset)
{
    uint *nBufMat = reinterpret_cast<uint*>(&raw[offset]);
    uint nNBufMat = sizeof(nBufMat[0]);
    vector<uchar> bufMat;
    for(uint i = offset; i < nBufMat[0]; ++i)
        bufMat.push_back(raw[i + nNBufMat]);
    mat_ = imdecode(bufMat, IMREAD_ANYCOLOR);

    return offset + nNBufMat + nBufMat[0];
}


}}
