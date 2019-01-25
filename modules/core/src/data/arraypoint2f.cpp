// std
#include <fstream>
#include <filesystem>
#include <memory>

// impro
#include <impro/data/arraypoint2f.hpp>

using namespace std;
using namespace cv;

namespace impro { namespace data
{

shared_ptr<Data> ArrayPoint2f::newPtr()
{
    ArrayPoint2f *data = new ArrayPoint2f();
    return shared_ptr<Data>(data);
}

shared_ptr<Data> ArrayPoint2f::clone()
{
    ArrayPoint2f *data = new ArrayPoint2f();
    data->vec_ = vec_;
    return shared_ptr<Data>(data);
}

void ArrayPoint2f::clone(Data &data)
{
    ArrayPoint2f &data__ = dynamic_cast<ArrayPoint2f&>(data);
    data__.vec_ = vec_;
}

void ArrayPoint2f::save(const string &dir,
                        const string &id)
{
    string fullPath(dir);
    fullPath.append("/").append(id);
    ofstream outputFile(fullPath.c_str());
    for(size_t i = 0; i < vec_.size(); ++i)
        outputFile << vec_.at(i).x << " "
                   << vec_.at(i).y << std::endl;

}

void ArrayPoint2f::load(const string &dir,
                        const string &id)
{
    string fullPath(dir);
    fullPath.append("/").append(id);
    vec_.clear();
    ifstream ifs(fullPath.c_str());
    if (ifs.is_open())
    {
        float x, y;
        while(ifs >> x && ifs >> y)
        {
            Point2f pt(x, y);
            vec_.push_back(pt);
        }
        ifs.close();
    }
}

void ArrayPoint2f::remove(const string &dir,
                          const string &id)
{
    std::string fullPath(dir);
    fullPath.append("/").append(id);
    filesystem::path pathToRemove(fullPath);
    filesystem::remove(pathToRemove);
}

uint ArrayPoint2f::serialize(std::vector<uchar> &raw,
                             uint offset)
{
    uint nBufVec = vec_.size() * 2;
    float *bufVec = new float[nBufVec];
    for(int i = 0; i < vec_.size(); ++i)
    {
        bufVec[0 + i * 2] = vec_.at(i).x;
        bufVec[1 + i * 2] = vec_.at(i).y;
    }
    uint nBufUCharVec = nBufVec * sizeof(float);
    uint nNBufUcharVec = sizeof(nBufUCharVec);
    uchar *ptrNBufUCharVec = reinterpret_cast<uchar*>(&nBufUCharVec);
    uchar *bufUCharVec = reinterpret_cast<uchar*>(&bufVec[0]);

    for(int i = 0; i < nNBufUcharVec; ++i)
        raw.push_back(ptrNBufUCharVec[i]);
    for(int i = 0; i < nBufUCharVec; ++i)
        raw.push_back(bufUCharVec[i]);

    return offset + nNBufUcharVec + nBufUCharVec;
}

uint ArrayPoint2f::deserialize(std::vector<uchar> &raw,
                               uint offset)
{
    uint *nBufUCharVec = reinterpret_cast<uint*>(&raw[offset]);
    uint nNBufUCharVec = sizeof(nBufUCharVec[0]);
    uint nBufVec = nBufUCharVec[0] / sizeof(float);
    float *bufVec = reinterpret_cast<float*>(&raw[offset + nNBufUCharVec]);;
    uint nVec = nBufVec / 2;
    vec_.clear();
    vec_.resize(nVec);
    for(int i = 0; i < nVec; ++i)
        vec_[i] = Point2f(bufVec[0 + i * 2], bufVec[1 + i * 2]);

    return offset + nNBufUCharVec + nBufUCharVec[0];
}

} }

