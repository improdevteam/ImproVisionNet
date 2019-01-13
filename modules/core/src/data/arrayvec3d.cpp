// std
#include <iostream>

// boost
#include <boost/filesystem.hpp>

// opencv
#include <opencv2/highgui.hpp>

// impro
#include <impro/data/arrayvec3d.hpp>

using namespace std;
using namespace boost;
using namespace cv;

namespace impro { namespace data
{

Data* ArrayVec3d::newPtr()
{
    return new ArrayVec3d();
}

Data* ArrayVec3d::clone()
{
    ArrayVec3d *data = new ArrayVec3d();
    data->vec_ = vec_;
    return data;
}

void ArrayVec3d::clone(Data &data)
{
    ArrayVec3d &data__ = dynamic_cast<ArrayVec3d&>(data);
    data__.vec_ = vec_;
}

void ArrayVec3d::save(const string &dir,
                      const string &id)
{
    string fullPath(dir);
    fullPath.append("/").append(id);
    ofstream outputFile(fullPath.c_str());
    for(size_t i = 0; i < vec_.size(); ++i)
        outputFile << vec_.at(i)[0] << " " << vec_.at(i)[1] << " " << vec_.at(i)[2] << std::endl;

}

void ArrayVec3d::load(const string &dir,
                      const string &id)
{
    string fullPath(dir);
    fullPath.append("/").append(id);
    vec_.clear();
    ifstream ifs(fullPath.c_str());
    if (ifs.is_open())
    {
        double d1, d2, d3;
        while(ifs >> d1 && ifs >> d2 && ifs >> d3)
        {
            Vec3d v(d1, d2, d3);
            vec_.push_back(v);
        }
        ifs.close();
    }
}

void ArrayVec3d::remove(const string &dir,
                        const string &id)
{
    std::string fullPath(dir);
    fullPath.append("/").append(id);
    boost::filesystem::path pathToRemove(fullPath);
    boost::filesystem::remove(pathToRemove);
}

uint ArrayVec3d::serialize(std::vector<uchar> &raw,
                           uint offset)
{
    uint nBufVec = vec_.size() * 3;
    double *bufVec = new double[nBufVec];
    for(int i = 0; i < vec_.size(); ++i)
    {
        bufVec[0 + i * 3] = vec_.at(i)[0];
        bufVec[1 + i * 3] = vec_.at(i)[1];
        bufVec[2 + i * 3] = vec_.at(i)[2];
    }
    uint nBufUCharVec = nBufVec * sizeof(double);
    uint nNBufUcharVec = sizeof(nBufUCharVec);
    uchar *ptrNBufUCharVec = reinterpret_cast<uchar*>(&nBufUCharVec);
    uchar *bufUCharVec = reinterpret_cast<uchar*>(&bufVec[0]);

    for(int i = 0; i < nNBufUcharVec; ++i)
        raw.push_back(ptrNBufUCharVec[i]);
    for(int i = 0; i < nBufUCharVec; ++i)
        raw.push_back(bufUCharVec[i]);

    return offset + nNBufUcharVec + nBufUCharVec;
}

uint ArrayVec3d::deserialize(std::vector<uchar> &raw,
                             uint offset)
{
    uint *nBufUCharVec = reinterpret_cast<uint*>(&raw[offset]);
    uint nNBufUCharVec = sizeof(nBufUCharVec[0]);
    uint nBufVec = nBufUCharVec[0] / sizeof(double);
    double *bufVec = reinterpret_cast<double*>(&raw[offset + nNBufUCharVec]);;
    uint nVec = nBufVec / 3;
    vec_.clear();
    vec_.resize(nVec);
    for(int i = 0; i < nVec; ++i)
        vec_[i] = Vec3d(bufVec[0 + i * 3], bufVec[1 + i * 3], bufVec[2 + i * 3]);

    return offset + nNBufUCharVec + nBufUCharVec[0];
}

} }
