// boost
#include <boost/filesystem.hpp>

// impro
#include <impro/data/imageptsbool.hpp>

using namespace std;
using namespace cv;

namespace impro { namespace data
{

Data* ImagePtsBool::newPtr()
{
    return new ImagePtsBool();
}

Data* ImagePtsBool::clone()
{
    ImagePtsBool *data = new ImagePtsBool();
    image_.clone(data->image_);
    pts_.clone(data->pts_);
    data->bool_ = bool_;
    return data;
}

void ImagePtsBool::clone(Data &data)
{
    ImagePtsBool &_data = dynamic_cast<ImagePtsBool&>(data);
    image_.clone(_data.image_);
    pts_.clone(_data.pts_);
    _data.bool_ = bool_;
}

void ImagePtsBool::save(const string &dir,
                        const string &id)
{
    string imageId = id;
    imageId.append(".jpg");
    image_.save(dir, imageId);
    string ptsId = id;
    ptsId.append(".pts");
    pts_.save(dir, ptsId);
    string fullPath(dir);
    fullPath.append("/").append(id).append(".bool");
    ofstream outputFile(fullPath.c_str());
    outputFile << bool_ << std::endl;
}

void ImagePtsBool::load(const string &dir,
                        const string &id)
{
    string imageId = id;
    imageId.append(".jpg");
    image_.load(dir, imageId);
    string ptsId = id;
    ptsId.append(".pts");
    pts_.load(dir, ptsId);

    string fullPath(dir);
    fullPath.append("/").append(id).append(".bool");
    ifstream ifs(fullPath.c_str());
    if (ifs.is_open())
    {
        ifs >> bool_;
        ifs.close();
    }
}

void ImagePtsBool::remove(const string &dir,
                          const string &id)
{
    string imageId = id;
    imageId.append(".jpg");
    image_.remove(dir, imageId);
    string ptsId = id;
    ptsId.append(".pts");
    pts_.remove(dir, ptsId);

    std::string fullPath(dir);
    fullPath.append("/").append(id).append(".bool");
    boost::filesystem::path pathToRemove(fullPath);
    boost::filesystem::remove(pathToRemove);
}

uint ImagePtsBool::serialize(std::vector<uchar> &raw,
                      uint offset)
{
    offset = image_.serialize(raw, offset);
    offset = pts_.serialize(raw, offset);
    raw.push_back(bool_);
    offset++;
    return offset;
}

uint ImagePtsBool::deserialize(std::vector<uchar> &raw,
                        uint offset)
{
    offset = image_.deserialize(raw, offset);
    offset = pts_.deserialize(raw, offset);
    bool_ = raw.at(offset);
    offset++;
    return offset;
}

} }
