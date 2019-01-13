#include <impro/data/imageacc.hpp>

using namespace std;
using namespace cv;

namespace impro { namespace data
{

Data* ImageAcc::newPtr()
{
    return new ImageAcc();
}

Data* ImageAcc::clone()
{
    ImageAcc *data = new ImageAcc();
    image_.clone(data->image_);
    acc_.clone(data->acc_);
    return data;
}

void ImageAcc::clone(Data &data)
{
    ImageAcc &_data = dynamic_cast<ImageAcc&>(data);
    image_.clone(_data.image_);
    acc_.clone(_data.acc_);
}

void ImageAcc::save(const string &dir,
                    const string &id)
{
    string imageId = id;
    imageId.append(".jpg");
    image_.save(dir, imageId);
    string accId = id;
    accId.append(".acc");
    acc_.save(dir, accId);
}

void ImageAcc::load(const string &dir,
                    const string &id)
{
    string imageId = id;
    imageId.append(".jpg");
    image_.load(dir, imageId);
    string accId = id;
    accId.append(".acc");
    acc_.load(dir, accId);
}

void ImageAcc::remove(const string &dir,
                      const string &id)
{
    string imageId = id;
    imageId.append(".jpg");
    image_.remove(dir, imageId);
    string accId = id;
    accId.append(".acc");
    acc_.remove(dir, accId);
}

uint ImageAcc::serialize(std::vector<uchar> &raw,
                         uint offset)
{
    offset = image_.serialize(raw, offset);
    offset = acc_.serialize(raw, offset);
    return offset;
}

uint ImageAcc::deserialize(std::vector<uchar> &raw,
                           uint offset)
{
    offset = image_.deserialize(raw, offset);
    offset = acc_.deserialize(raw, offset);
    return offset;
}

} }

