// std
#include <iostream>

// boost
#include <boost/filesystem.hpp>

// impro
#include <impro/data/arraypoint3d.hpp>

using namespace std;
using namespace boost;
using namespace cv;

namespace impro { namespace data
{

Data* ArrayPoint3d::newPtr()
{
    return new ArrayPoint3d();
}

Data* ArrayPoint3d::clone()
{
    ArrayPoint3d *data = new ArrayPoint3d();
    data->vec_ = vec_;
    return data;
}

void ArrayPoint3d::clone(Data &data)
{
    ArrayPoint3d &data__ = dynamic_cast<ArrayPoint3d&>(data);
    data__.vec_ = vec_;
}

void ArrayPoint3d::save(const string &dir,
                        const string &id)
{
    string fullPath(dir);
    fullPath.append("/").append(id);
    ofstream outputFile(fullPath.c_str());
    for(size_t i = 0; i < vec_.size(); ++i)
        outputFile << vec_.at(i).x << " " << vec_.at(i).y << " " << vec_.at(i).z << std::endl;

}

void ArrayPoint3d::load(const string &dir,
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
            Point3d v(d1, d2, d3);
            vec_.push_back(v);
        }
        ifs.close();
    }
}

void ArrayPoint3d::remove(const string &dir,
                          const string &id)
{
    std::string fullPath(dir);
    fullPath.append("/").append(id);
    boost::filesystem::path pathToRemove(fullPath);
    boost::filesystem::remove(pathToRemove);
}

uint ArrayPoint3d::serialize(std::vector<uchar> &raw,
                             uint offset)
{
    uint nBufVec = vec_.size() * 3;
    double *bufVec = new double[nBufVec];
    for(int i = 0; i < vec_.size(); ++i)
    {
        bufVec[0 + i * 3] = vec_.at(i).x;
        bufVec[1 + i * 3] = vec_.at(i).y;
        bufVec[2 + i * 3] = vec_.at(i).z;
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

uint ArrayPoint3d::deserialize(std::vector<uchar> &raw,
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
        vec_[i] = Point3d(bufVec[0 + i * 3], bufVec[1 + i * 3], bufVec[2 + i * 3]);

    return offset + nNBufUCharVec + nBufUCharVec[0];
}

} }
