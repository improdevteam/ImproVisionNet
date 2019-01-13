// boost
#include <boost/filesystem.hpp>
#include <boost/range/algorithm/remove.hpp>

// impro
#include <impro/datatype.hpp>
#include <impro/data.hpp>
#include <impro/node.hpp>
#include <impro/channel.hpp>
#include <impro/channelobserver.hpp>

using namespace std;
using namespace boost;

namespace impro
{

// Class Node ------------------------------------------------
Channel::Channel(const std::string &dataType,
                 const std::string &id,
                 unsigned int limit,
                 Node &node)
    : dataType_(dataType),
      id_(id),
      limit_(limit > 0 ? limit : 1),
      node_(node),
      idx_(0)
{
    dir_ = node_.getDir();
    dir_.append("/").append(id_);
    filesystem::path d(dir_);
    if(!filesystem::exists(d))
        filesystem::create_directories(d);

    data_ = DataType::DataTypes_.at(dataType_)->newPtr();
}

Data* Channel::current()
{
    return data_->clone();
}

Data* Channel::prev(unsigned int n)
{
    if(limit_ == 0)
        return data_->clone();

    unsigned int idx = 0;
    if(n > idx_ && total() == limit_)
        idx = idx_ + limit_ - n;
    else if(n < idx_)
        idx = idx_ - n;
    Data *data = data_->newPtr();
    string dataId = dataIds_.at(idx);
    data->load(dir_, dataId);
    return data;
}

Data* Channel::at(unsigned int n)
{
    Data *data = data_->newPtr();
    string dataId = dataIds_.at(n);
    data->load(dir_, dataId);
    return data;
}

void Channel::current(Data &data)
{
    data_->clone(data);
}

void Channel::prev(Data &data, unsigned int n)
{
    if(limit_ == 0)
        data_->clone(data);
    else
    {
        unsigned int idx = 0;
        if(n > idx_ && total() == limit_)
            idx = idx_ + limit_ - n;
        else if(n < idx_)
            idx = idx_ - n;
        string dataId = dataIds_.at(idx);
        data.load(dir_, dataId);
    }
}

void Channel::at(Data &data, unsigned int n)
{
    string dataId = dataIds_.at(n);
    data.load(dir_, dataId);
}

string Channel::currentDataId()
{
    if(limit_ == 0)
        return string("");

    return dataIds_.at(idx_);
}

string Channel::prevDataId(unsigned int n)
{
    if(limit_ == 0)
        return string("");

    unsigned int idx = 0;
    if(total() == limit_)
        idx = idx_ + limit_ - n;
    else if(n < idx_)
        idx = idx_ - n;
    return dataIds_.at(idx);
}

string Channel::atDataId(unsigned int n)
{
    return  dataIds_.at(n);
}

unsigned int Channel::total()
{
    return dataIds_.size();
}

void Channel::subscribe(ChannelObserver *observer)
{
    observers_.push_back(observer);
}

void Channel::unsubscribe(ChannelObserver *observer)
{
    observers_.erase(boost::remove(observers_, observer), observers_.end());
}

void Channel::setLimit(unsigned limit)
{
    // ToDo: Important!! resize dataIds_

    limit_ = limit;
}

void Channel::save(const std::string &dataId,
                   Data &data)
{
    data.clone(*data_);

    data_->save(dir_, dataId);

    unsigned int n = total();
    if(n < limit_)
    {
        dataIds_.push_back(dataId);
        idx_ = n;
    }
    else
    {
        idx_ = ++idx_ == limit_ ? 0 : idx_;
        data_->remove(dir_, dataIds_.at(idx_));
        dataIds_[idx_] = dataId;
    }

    // Notify observer in the same process
    for(unsigned int i = 0; i < observers_.size(); ++i)
        observers_.at(i)->dataReceived(*this);
}

void Channel::save(const string &dataId,
                   std::vector<uchar> &raw)
{
//    Data* data = data_->newPtr();
//    data->deserialize(raw);
//    data->clone(*data_);
//    delete data;

    data_->deserialize(raw);

    data_->save(dir_, dataId);

    unsigned int n = total();
    if(n < limit_)
    {
        dataIds_.push_back(dataId);
        idx_ = n;
    }
    else
    {
        idx_ = ++idx_ == limit_ ? 0 : idx_;
        data_->remove(dir_, dataIds_.at(idx_));
        dataIds_[idx_] = dataId;
    }

    // Notify observer in the same process
    for(unsigned int i = 0; i < observers_.size(); ++i)
        observers_.at(i)->dataReceived(*this);
}

// Class LocalChannel ------------------------------------------------
LocalChannel::LocalChannel(const std::string &dataType,
                             const std::string &id,
                             unsigned int limit,
                             Node &node)
    : Channel(dataType, id, limit, node)
{
}

LocalChannel::~LocalChannel()
{
}

// Class RemoteChannel ------------------------------------------------
RemoteChannel::RemoteChannel(const std::string &dataType,
                           const std::string &id,
                           unsigned int limit,
                           Node &node)
    : Channel(dataType, id, limit, node)
{
}

RemoteChannel::~RemoteChannel()
{
}



}
