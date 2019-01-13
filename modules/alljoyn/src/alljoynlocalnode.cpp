// std
#include <string>
#include <iostream> // debug

// boost
#include <boost/format.hpp>
#include <boost/foreach.hpp>

// impro
#include <impro/private/alljoynlocalnode.hpp>
#include <impro/private/alljoynlocallistener.hpp>
#include <impro/private/alljoynspace.hpp>
#include <impro/private/alljoynutil.hpp>
#include <impro/private/alljoynlocalchannel.hpp>

using namespace std;
using namespace boost;
using namespace ajn;

namespace impro
{

AlljoynLocalNode::AlljoynLocalNode(const std::string &id,
                                   Space &space)
    : LocalNode(id, space),
      AlljoynLocalObject(AlljoynUtil::NodeServicePath(id).c_str(),
                    (dynamic_cast<AlljoynSpace&>(space)).getBus() )
{
    const InterfaceDescription *iface = bus->GetInterface(AlljoynUtil::NODE_INTERFACE.c_str());
    QStatus status = AddInterface(*iface);
    if (status != ER_OK)
        cerr << format("Failed to Add interface: %1%(%2%)\n")
                       % AlljoynUtil::NODE_INTERFACE
                       % QCC_StatusText(status); // debug

    ajnSessionPort_ = AlljoynUtil::NODE_SESSION_PORT;
    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES,
                     false,
                     SessionOpts::PROXIMITY_ANY,
                     TRANSPORT_TCP | TRANSPORT_LOCAL);

    status = bus->BindSessionPort(ajnSessionPort_, opts, *listener_);
    if (ER_OK != status)
        cerr << format("BindSessionPort failed.(%1%)\n")
                       % QCC_StatusText(status); // debug

    ajnServiceName_ = AlljoynUtil::NodeServiceName(id);
}

AlljoynLocalNode::~AlljoynLocalNode()
{
    // Clear channels
    BOOST_FOREACH(LocalChannelMap::value_type &item, channels_)
    {
        AlljoynLocalChannel *channel = item.second;
        if(channel)
        {
            delete channel;
            channel = NULL;
        }
    }
    channels_.clear();
}

LocalChannel& AlljoynLocalNode::registerChannel(const string &dataType,
                                                 const string &channelId,
                                                 unsigned int limit)
{
    if(channels_.find(channelId) == channels_.end())
    {
        AlljoynLocalChannel *channel = new AlljoynLocalChannel(dataType, channelId, limit, *this);
        channels_.insert(LocalChannelMap::value_type(channelId, channel));
        channel->advertise();
    }
    return *channels_.at(channelId);
}

LocalChannel& AlljoynLocalNode::getChannel(const string &channelId)
{
    return *channels_.at(channelId);
}

bool AlljoynLocalNode::hasChannel(const string &channelId)
{
    if(channels_.find(channelId) != channels_.end())
        return true;
    else
        return false;
}



}
