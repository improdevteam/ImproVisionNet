// boost
#include <fstream>
#include <filesystem>
#include <memory>

// impro
#include <impro/data/imageaccpts.hpp>

using namespace std;
using namespace cv;

namespace impro { namespace data
{

shared_ptr<Data> ImageAccPts::newPtr()
{
    ImageAccPts *data = new ImageAccPts();
    return shared_ptr<Data>(data);
}

shared_ptr<Data> ImageAccPts::clone()
{
    ImageAccPts *data = new ImageAccPts();
    image_.clone(data->image_);
    acc_.clone(data->acc_);
    pts_.clone(data->pts_);
    return shared_ptr<Data>(data);
}

void ImageAccPts::clone(Data &data)
{
    ImageAccPts &_data = dynamic_cast<ImageAccPts&>(data);
    image_.clone(_data.image_);
    acc_.clone(_data.acc_);
    pts_.clone(_data.pts_);
}

void ImageAccPts::save(const string &dir,
                           const string &id)
{
    string imageId = id;
    imageId.append(".jpg");
    image_.save(dir, imageId);
    string accId = id;
    accId.append(".acc");
    acc_.save(dir, accId);
    string ptsId = id;
    ptsId.append(".pts");
    pts_.save(dir, ptsId);
}

void ImageAccPts::load(const string &dir,
                        const string &id)
{
    string imageId = id;
    imageId.append(".jpg");
    image_.load(dir, imageId);
    string accId = id;
    accId.append(".acc");
    acc_.load(dir, accId);
    string ptsId = id;
    ptsId.append(".pts");
    pts_.load(dir, ptsId);
}

void ImageAccPts::remove(const string &dir,
                          const string &id)
{
    string imageId = id;
    imageId.append(".jpg");
    image_.remove(dir, imageId);
    string accId = id;
    accId.append(".acc");
    acc_.remove(dir, accId);
    string ptsId = id;
    ptsId.append(".pts");
    pts_.remove(dir, ptsId);
}

uint ImageAccPts::serialize(std::vector<uchar> &raw,
                      uint offset)
{
    offset = image_.serialize(raw, offset);
    offset = acc_.serialize(raw, offset);
    offset = pts_.serialize(raw, offset);
    return offset;
}

uint ImageAccPts::deserialize(std::vector<uchar> &raw,
                        uint offset)
{
    offset = image_.deserialize(raw, offset);
    offset = acc_.deserialize(raw, offset);
    offset = pts_.deserialize(raw, offset);
    return offset;
}

} }

