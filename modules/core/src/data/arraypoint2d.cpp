// std
#include <fstream>
#include <filesystem>
#include <memory>

// impro
#include <impro/data/arraypoint2d.hpp>

using namespace std;
using namespace cv;

namespace impro { namespace data
{

shared_ptr<Data> ArrayPoint2d::newPtr()
{
    ArrayPoint2d *data = new ArrayPoint2d();
    return shared_ptr<Data>(data);
}

shared_ptr<Data> ArrayPoint2d::clone()
{
    ArrayPoint2d *data = new ArrayPoint2d();
    data->vec_ = vec_;
    return shared_ptr<Data>(data);
}

void ArrayPoint2d::clone(Data &data)
{
    ArrayPoint2d &data__ = dynamic_cast<ArrayPoint2d&>(data);
    data__.vec_ = vec_;
}

void ArrayPoint2d::save(const string &dir,
                        const string &id)
{
    string fullPath(dir);
    fullPath.append("/").append(id);
    ofstream ofs(fullPath.c_str());
    for(size_t i = 0; i < vec_.size(); ++i)
        ofs << vec_.at(i).x << " "
            << vec_.at(i).y << std::endl;

}

void ArrayPoint2d::load(const string &dir,
                        const string &id)
{
    string fullPath(dir);
    fullPath.append("/").append(id);
    vec_.clear();
    ifstream ifs(fullPath.c_str());
    if (ifs.is_open())
    {
        double x, y;
        while(ifs >> x && ifs >> y)
        {
            Point2d pt(x, y);
            vec_.push_back(pt);
        }
        ifs.close();
    }
}

void ArrayPoint2d::remove(const string &dir,
                          const string &id)
{
    std::string fullPath(dir);
    fullPath.append("/").append(id);
    filesystem::path pathToRemove(fullPath);
    filesystem::remove(pathToRemove);
}

uint ArrayPoint2d::serialize(std::vector<uchar> &raw,
                             uint offset)
{
    uint nBufVec = vec_.size() * 2;
    double *bufVec = new double[nBufVec];
    for(int i = 0; i < vec_.size(); ++i)
    {
        bufVec[0 + i * 2] = vec_.at(i).x;
        bufVec[1 + i * 2] = vec_.at(i).y;
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

uint ArrayPoint2d::deserialize(std::vector<uchar> &raw,
                               uint offset)
{
    uint *nBufUCharVec = reinterpret_cast<uint*>(&raw[offset]);
    uint nNBufUCharVec = sizeof(nBufUCharVec[0]);
    uint nBufVec = nBufUCharVec[0] / sizeof(double);
    double *bufVec = reinterpret_cast<double*>(&raw[offset + nNBufUCharVec]);;
    uint nVec = nBufVec / 2;
    vec_.clear();
    vec_.resize(nVec);
    for(int i = 0; i < nVec; ++i)
        vec_[i] = Point2d(bufVec[0 + i * 2], bufVec[1 + i * 2]);

    return offset + nNBufUCharVec + nBufUCharVec[0];
}

} }

