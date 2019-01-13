// std
#include <iostream> // for debug

// boost
#include <boost/format.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>

// alljoyn
#include <alljoyn/Status.h>

// impro
#include <impro/private/alljoynlocalnode.hpp>
#include <impro/private/alljoynremotenode.hpp>
#include <impro/private/alljoynremotechannel.hpp>
#include <impro/private/alljoynutil.hpp>
#include <impro/private/alljoynspace.hpp>

using namespace std;
using namespace boost;
using namespace ajn;

namespace impro
{

AlljoynSpace::AlljoynSpace(const string &spaceId,
                           const string &nodeId,
                           const string &dir)
    : Space(spaceId, dir)
{
    // Step1. Create BusAttachment
    bus_ = new BusAttachment(spaceId.c_str(), true);

    // Step2. Create Interface
    AlljoynUtil::CreateNodeInterface(*bus_);

    AlljoynUtil::CreateOutputChannelInterface(*bus_);

    // Step3. Initialize Alljoyn
    QStatus status = bus_->Start();
    if (ER_OK != status)
        cout << format("bus start failed.(%1%)\n")
                % QCC_StatusText(status); // debug

    status = bus_->Connect();
    if (ER_OK != status)
        cout << format("bus connect failed.(%1%)\n")
                % QCC_StatusText(status); // debug

    bus_->RegisterBusListener(*this);

    cout << format("AlljoynGlobalSpace start.(%1%)\n")
            % bus_->GetUniqueName().c_str(); // debug

    // Step4. Create LocalNode
    node_ = new AlljoynLocalNode(nodeId, *this);
    dynamic_cast<AlljoynLocalNode*>(node_)->advertise();

    // Step5. FindAdvertisedName (Node and Channel)
    status = bus_->FindAdvertisedName(AlljoynUtil::NODE_PREFIX.c_str());
    if (ER_OK != status)
        cout << format("FindAdvertisedName('%1%') failed.(%2%)\n")
                       % AlljoynUtil::NODE_PREFIX
                       % QCC_StatusText(status); // debug

    status = bus_->FindAdvertisedName(AlljoynUtil::CHANNEL_PREFIX.c_str());
    if (ER_OK != status)
        cout << format("FindAdvertisedName('%1%') failed.(%2%)\n")
                       % AlljoynUtil::CHANNEL_PREFIX
                       % QCC_StatusText(status); // debug

}

AlljoynSpace::~AlljoynSpace()
{
    BOOST_FOREACH(RemoteNodeMap::value_type &item, remoteNodes_)
    {
        AlljoynRemoteNode *node = item.second;
        bus_->LeaveJoinedSession(node->getAlljoynSessionId());
        delete node;
        node = NULL;
    }
    remoteNodes_.clear();

    if(node_ != NULL)
    {
        delete node_;
        node_ = NULL;
    }

    if(bus_)
    {
        if(bus_->IsConnected())
        {
            QStatus status = bus_->Disconnect();
            if (ER_OK != status)
            {
                cout << format("bus disconnect failed.(%1%)\n")
                               % QCC_StatusText(status); // debug
            }
        }

        if(bus_->IsStarted())
        {
            QStatus status = bus_->Stop();
            if (ER_OK != status)
            {
                cout << format("bus stop failed.(%1%)\n")
                               % QCC_StatusText(status); // debug
            }
        }

        delete bus_;
        bus_ = NULL;
    }

    cout << "AlljoynGlobalSpace stop.\n"; // debug
}

bool AlljoynSpace::hasRemoteNode(const std::string &nodeId)
{
    if(remoteNodes_.find(nodeId) == remoteNodes_.end())
        return false;
    else
        return true;
}

RemoteNode& AlljoynSpace::getRemoteNode(const string &nodeId)
{
    return *remoteNodes_.at(nodeId);
}

// BusListener ----------------------------------------------------
void AlljoynSpace::FoundAdvertisedName(const char *name,
                                       TransportMask transport,
                                       const char *namePrefix)
{
    cout << format("AlljoynSpace::FoundAdvertisedName(name='%1%', transport = 0x%2$x, prefix='%3%')\n")
                   % name
                   % transport
                   % namePrefix; // debug

    AlljoynLocalNode *node = dynamic_cast<AlljoynLocalNode*>(node_);
    string ajnServiceName(name);
    if(ajnServiceName != node->getAlljoynServiceName() &&
       starts_with(ajnServiceName, AlljoynUtil::NODE_PREFIX)) // Found RemoteNode
    {
        string nodeId = AlljoynUtil::NodeFromServiceName(ajnServiceName);
        bus_->EnableConcurrentCallbacks();
        SessionId sessionId;
        SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES,
                         true,
                         SessionOpts::PROXIMITY_ANY,
                         TRANSPORT_ANY);
        QStatus status = bus_->JoinSession(name,
                                           AlljoynUtil::NODE_SESSION_PORT,
                                           NULL,
                                           sessionId,
                                           opts);
        addRemoteNode(nodeId, transport, sessionId);
    }
    else if(starts_with(ajnServiceName, AlljoynUtil::CHANNEL_PREFIX)) // Found Channel
    {
        string nodeId;
        string channelId;
        string dataType;
        SessionPort sessionPort;
        AlljoynUtil::ChannelFromServiceName(ajnServiceName,
                                            nodeId,
                                            channelId,
                                            sessionPort,
                                            dataType);
        if(nodeId != node_->getId())
        {
            if(remoteNodes_.find(nodeId) == remoteNodes_.end())
                addRemoteNode(nodeId, transport, SESSION_ID_ALL_HOSTED);

            AlljoynRemoteNode *node = remoteNodes_.at(nodeId);
            node->registerChannel(dataType,
                                  channelId,
                                  std::numeric_limits<unsigned int>::max(),
                                  sessionPort,
                                  transport,
                                  SESSION_ID_ALL_HOSTED);
        }
    }
}

// SessionListener ----------------------------------------------------
void AlljoynSpace::SessionLost(SessionId sessionId,
                               SessionListener::SessionLostReason reason)
{
    cout << format("AlljoynGlobalSpace::SessionLost (id=%1%).\n")
                   % sessionId; // debug
    removeRemoteNode(sessionId);
}

void AlljoynSpace::SessionMemberAdded (SessionId sessionId,
                                       const char *uniqueName)
{
    cout << format("AlljoynGlobalSpace::SessionMemberAdded (id=%1%)(uniqueName=%2%).\n")
                   % sessionId
                   % uniqueName; // debug
}

void AlljoynSpace::SessionMemberRemoved(SessionId sessionId,
                                        const char *uniqueName)
{
    cout << format("AlljoynGlobalSpace::SessionMemberRemoved (id=%1%)(uniqueName=%2%).\n")
                   % sessionId
                   % uniqueName; // debug
}

// private ---------------------------------------------------------
void AlljoynSpace::addRemoteNode(const string &nodeId,
                                 TransportMask transportMask,
                                 SessionId sessionId)
{
    if(remoteNodes_.find(nodeId) == remoteNodes_.end())
    {
        AlljoynRemoteNode *node = new AlljoynRemoteNode(nodeId,
                                                        *this,
                                                        transportMask,
                                                        sessionId);
        remoteNodes_.insert(RemoteNodeMap::value_type(nodeId, node));
    }
    else
    {
        AlljoynRemoteNode *remoteNode = remoteNodes_.at(nodeId);
        remoteNode->setAlljoynSessionId(sessionId);
    }
}

void AlljoynSpace::removeRemoteNode(SessionId sessionId)
{
    string nodeId;
    BOOST_FOREACH(RemoteNodeMap::value_type &item, remoteNodes_)
    {
        AlljoynRemoteNode *node = item.second;
        if(node->getAlljoynSessionId() == sessionId)
        {
            nodeId = node->getId();
            break;
        }
    }

    if(nodeId.length() > 0)
        remoteNodes_.erase(nodeId);

}

}
