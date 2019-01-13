// std
#include <vector>
#include <iostream> // debug

// boost
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/format.hpp>

// alljoyn
#include <alljoyn/BusAttachment.h>

// impro
#include <impro/private/alljoynutil.hpp>

// Legacy...
#include <impro/data/imageacc.hpp>

using namespace std;
using namespace boost;
using namespace ajn;

namespace impro { namespace AlljoynUtil
{

const SessionPort NODE_SESSION_PORT = 1020;

const string NODE_INTERFACE = "impro.interface.node";

const string NODE_PREFIX = "impro.node";

const string CHANNEL_INTERFACE = "impro.interface.channel";

const string CHANNEL_PREFIX = "impro.channel";

const string SERVICE_PREFIX = "impro.service";

string NodeServiceName(const string &nodeId)
{
    return string(NODE_PREFIX).append(".").append(nodeId);
}

string NodeServicePath(const string &nodeId)
{
    return string("/").append(nodeId);
}

string NodeFromServiceName(const string &nodeServiceName)
{
    string prefix(NODE_PREFIX);
    return nodeServiceName.substr(prefix.length() + 1);
}

string NodeFromServicePath(const string &nodeServicePath)
{
    return nodeServicePath.substr(1);
}

string ChannelServicePrefix(const string &channelId)
{
    return string(CHANNEL_PREFIX).append(".").append(channelId);
}

string ChannelServiceName(const string &nodeId,
                          const string &channelId,
                          SessionPort   port,
                          const string &dataType)
{
    // CHANNEL_PREFIX.channelId.nodeId.port
    string portStr = lexical_cast<string>(port);
    return string(CHANNEL_PREFIX).append(".").append(channelId)
                                      .append(".").append(nodeId)
                                      .append(".p").append(portStr)
                                      .append(".").append(dataType);
}

string ChannelServicePath(const string &nodeId,
                          const string &channelId)
{
    // /nodeId/channelId
    return string("/").append(nodeId)
                           .append("/").append(channelId);
}

void ChannelFromServiceName(const string &channelServiceName,
                            string &nodeId,
                            string &channelId,
                            SessionPort &port,
                            string &dataType)
{
    string prefix(CHANNEL_PREFIX);
    string channelNodeStr = channelServiceName.substr(prefix.length() + 1);
    vector<string> result;
    split(result, channelNodeStr, is_any_of( "." ));
    channelId = result.at(0);
    nodeId = result.at(1);
    string portStr = result.at(2);
    portStr = portStr.substr(1);
    port = lexical_cast<SessionPort>(portStr);
    if(result.size() == 4)
        dataType = result.at(3);
    else
        dataType = IMPRO_DATA_IMAGEACC;
}

void ChannelFromServicePath(const string &channelServicePath,
                            string &nodeId,
                            string &channelId)
{
    string nodeChannelStr = channelServicePath.substr(1);
    vector<string> result;
    split(result, nodeChannelStr, is_any_of( "/" ));
    nodeId = result.at(0);
    channelId = result.at(1);
}

string ServicePrefix(const string &prefix,
                                   const string &Id) // prefix.Id
{
    return string(prefix).append(".").append(Id);
}

string ServiceName(const string &prefix,
                                 const string &nodeId,
                                 const string &Id,
                                 ajn::SessionPort   port) // prefix.Id.nodeId.pport
{
    // CHANNEL_PREFIX.channelId.nodeId.port
    string portStr = lexical_cast<string>(port);
    return string(prefix).append(".").append(Id)
                              .append(".").append(nodeId)
                              .append(".p").append(portStr);

}

string ServicePath(const string &nodeId,
                                 const string &Id) // /nodeId/Id
{
    // /nodeId/Id
    return string("/").append(nodeId)
                           .append("/").append(Id);
}

void FromServiceName(const string &prefix,
                              const string &serviceName,
                              string &nodeId,
                              string &Id,
                              ajn::SessionPort &port)
{
    string str = serviceName.substr(prefix.length() + 1);
    vector<string> result;
    split(result, str, is_any_of( "." ));
    Id = result.at(0);
    nodeId = result.at(1);
    string portStr = result.at(2);
    portStr = portStr.substr(1);
    port = lexical_cast<SessionPort>(portStr);
}

void FromServicePath(const string &servicePath,
                              string &nodeId,
                              string &Id)
{
    string str = servicePath.substr(1);
    vector<string> result;
    split(result, str, is_any_of( "/" ));
    nodeId = result.at(0);
    Id = result.at(1);
}

void CreateNodeInterface(BusAttachment &bus)
{
    InterfaceDescription *iface = NULL;
    QStatus status = bus.CreateInterface(NODE_INTERFACE.c_str(),
                                         iface);
    if(status == ER_BUS_IFACE_ALREADY_EXISTS)
        return;
    else if(status == ER_OK)
    {
        iface->AddMethod("FindChannelSessionPort",
                         "s", "u", "channelIdentifier, sessionPort", 0);
        iface->Activate();
    }
    else
    {
        cout << format("Failed to create interface '%1%'.(%2%)\n")
                       % NODE_INTERFACE
                       % QCC_StatusText(status);
    }
}

void CreateOutputChannelInterface(BusAttachment &bus)
{
    InterfaceDescription *iface = NULL;
    QStatus status = bus.CreateInterface(CHANNEL_INTERFACE.c_str(),
                                         iface);
    if(status == ER_BUS_IFACE_ALREADY_EXISTS)
        return;
    else if(status == ER_OK)
    {
        iface->AddSignal("TransferFile", "suay", "filename,count,data", 0);
        iface->AddSignal("FileIsReady", "suad", "filename,count,acc", 0);
        iface->AddSignal("TransferData", "suay", "identifier,count,data", 0);
        iface->AddSignal("DataIsReady", "su", "identifier,count", 0);
        iface->Activate();
    }
    else
    {
        cout <<format("Failed to create interface '%1%'.(%2%)\n")
                      % CHANNEL_INTERFACE
                      % QCC_StatusText(status);
    }
}


} }
