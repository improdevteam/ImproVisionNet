#include <memory>
#include <impro/data/imagepts.hpp>

using namespace std;
using namespace cv;

namespace impro { namespace data
{

shared_ptr<Data> ImagePts::newPtr()
{
    ImagePts *data = new ImagePts();
    return shared_ptr<Data>(data);
}

shared_ptr<Data> ImagePts::clone()
{
    ImagePts *data = new ImagePts();
    image_.clone(data->image_);
    pts_.clone(data->pts_);
    return shared_ptr<Data>(data);
}

void ImagePts::clone(Data &data)
{
    ImagePts &_data = dynamic_cast<ImagePts&>(data);
    image_.clone(_data.image_);
    pts_.clone(_data.pts_);
}

void ImagePts::save(const string &dir,
                    const string &id)
{
    string imageId = id;
    imageId.append(".jpg");
    image_.save(dir, imageId);
    string ptsId = id;
    ptsId.append(".pts");
    pts_.save(dir, ptsId);
}

void ImagePts::load(const string &dir,
                    const string &id)
{
    string imageId = id;
    imageId.append(".jpg");
    image_.load(dir, imageId);
    string ptsId = id;
    ptsId.append(".pts");
    pts_.load(dir, ptsId);
}

void ImagePts::remove(const string &dir,
                      const string &id)
{
    string imageId = id;
    imageId.append(".jpg");
    image_.remove(dir, imageId);
    string ptsId = id;
    ptsId.append(".pts");
    pts_.remove(dir, ptsId);
}

uint ImagePts::serialize(std::vector<uchar> &raw,
                         uint offset)
{
    offset = image_.serialize(raw, offset);
    offset = pts_.serialize(raw, offset);
    return offset;
}

uint ImagePts::deserialize(std::vector<uchar> &raw,
                           uint offset)
{
    offset = image_.deserialize(raw, offset);
    offset = pts_.deserialize(raw, offset);
    return offset;
}

} }
