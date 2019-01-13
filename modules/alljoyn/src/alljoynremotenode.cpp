// std
#include <string>
#include <iostream> // debug

// boost
#include <boost/foreach.hpp>

// impro
#include <impro/private/alljoynspace.hpp>
#include <impro/private/alljoynremotechannel.hpp>
#include <impro/private/alljoynremotenode.hpp>
#include <impro/private/alljoynremoteobject.hpp>
#include <impro/private/alljoynutil.hpp>

using namespace std;
using namespace ajn;

namespace impro
{

AlljoynRemoteNode::AlljoynRemoteNode(const string &id,
                                     Space &space,
                                     TransportMask transportMask,
                                     SessionId sessionId)

    : RemoteNode(id, space),
      AlljoynRemoteObject(AlljoynUtil::NodeServiceName(id),
                          AlljoynUtil::NodeServicePath(id),
                          AlljoynUtil::NODE_SESSION_PORT,
                          transportMask,
                          sessionId,
                          (dynamic_cast<AlljoynSpace&>(space)).getBus() )
{
}

AlljoynRemoteNode::~AlljoynRemoteNode()
{
    // Clear channels
    BOOST_FOREACH(RemoteChannelMap::value_type &item, channels_)
    {
        AlljoynRemoteChannel *channel = item.second;
        if(channel)
        {
            delete channel;
            channel = NULL;
        }
    }
    channels_.clear();
}

RemoteChannel& AlljoynRemoteNode::getChannel(const string &channelId)
{
    return *channels_.at(channelId);
}

bool AlljoynRemoteNode::hasChannel(const string &channelId)
{
    if(channels_.find(channelId) != channels_.end())
        return true;
    else
        return false;
}

RemoteChannel& AlljoynRemoteNode::registerChannel(const string &dataType,
                                                  const string &channelId,
                                                  unsigned int limit,
                                                  SessionPort sessionPort,
                                                  TransportMask transport,
                                                  SessionId sessionId)
{
    if(channels_.find(channelId) == channels_.end())
    {
        AlljoynRemoteChannel *channel = new AlljoynRemoteChannel(dataType,
                                                                 channelId,
                                                                 limit,
                                                                 *this,
                                                                 sessionPort,
                                                                 transport,
                                                                 sessionId);
        channels_.insert(RemoteChannelMap::value_type(channelId, channel));
    }
    return *channels_.at(channelId);
}

}
