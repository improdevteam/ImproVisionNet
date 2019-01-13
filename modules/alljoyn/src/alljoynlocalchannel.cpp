// std
#include <iostream> // debug

// boost
#include <boost/format.hpp>

// ajn
#include <alljoyn/BusAttachment.h>

// impro
#include <impro/private/alljoynlocalchannel.hpp>
#include <impro/private/alljoynutil.hpp>
#include <impro/private/alljoynspace.hpp>
#include <impro/private/alljoynlocallistener.hpp>
#include <impro/data.hpp>
#include <impro/node.hpp>

using namespace std;
using namespace boost;
using namespace ajn;

namespace impro
{

AlljoynLocalChannel::AlljoynLocalChannel(const std::string &dataType,
                                         const std::string &id,
                                         unsigned int limit,
                                         Node &node)
    : LocalChannel(dataType, id, limit, node),
      AlljoynLocalObject(AlljoynUtil::ChannelServicePath(node.getId(), id).c_str(),
                        (dynamic_cast<AlljoynSpace&>(node.getSpace())).getBus() )
{
    const InterfaceDescription *iface = bus->GetInterface(AlljoynUtil::CHANNEL_INTERFACE.c_str());
    QStatus status = AddInterface(*iface);
    if (status == ER_OK)
    {
        TransferData = iface->GetMember("TransferData");
        assert(TransferData); // debug
        DataIsReady = iface->GetMember("DataIsReady");
        assert(DataIsReady); // debug
    }
    else
        cerr <<format("Failed to Add interface: %1%\n")
                      % AlljoynUtil::CHANNEL_INTERFACE; // debug


    ajnSessionPort_ = SESSION_PORT_ANY;
    SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES,
                     false,
                     SessionOpts::PROXIMITY_ANY,
                     TRANSPORT_TCP | TRANSPORT_LOCAL);

    status = bus->BindSessionPort(ajnSessionPort_, opts, *listener_);
    if (ER_OK != status)
        cerr << format("BindSessionPort failed.(%1%)\n")
                       % QCC_StatusText(status); // debug

    ajnServiceName_ = AlljoynUtil::ChannelServiceName(node_.getId(),
                                                      id,
                                                      ajnSessionPort_,
                                                      dataType);
}

AlljoynLocalChannel::~AlljoynLocalChannel()
{
}

void AlljoynLocalChannel::write(const std::string &dataId,
                                 Data &data)
{
    // 1st Step: write local
    Channel::save(dataId, data);

    // 2nd Step: check if there is any node need data
    if(subscribers_.size() == 0)
        return;

    // 3rd Step: send to remote.
    char* buf = new char[ALLJOYN_MAX_ARRAY_LEN];
    MsgArg args1[3];
    QStatus status;
    vector<uchar> vbuf;
    data_->serialize(vbuf);
    size_t length = vbuf.size();

    size_t offset = 0;
    int count = 0;
    while (length > 0)
    {
        size_t bufferLength = ALLJOYN_MAX_ARRAY_LEN;
        if (length > (size_t)ALLJOYN_MAX_ARRAY_LEN)
            length -= (size_t)ALLJOYN_MAX_ARRAY_LEN;
        else
        {
            bufferLength = length;
            length = 0;
        }

        for(size_t i = 0; i < bufferLength; ++i)
            buf[i] = vbuf[offset + i];

        offset += bufferLength;

        args1[0].Set("s", dataId.c_str());
        args1[1].Set("u", count);
        args1[2].Set("ay", bufferLength, buf);

        for(size_t i = 0; i < subscribers_.size(); ++i)
        {
            status = Signal(NULL, subscribers_.at(i), *TransferData, args1, 3);
            if (status != ER_OK)
                cerr << format("Error sending Signal to %1% (%2%).\n")
                               % subscribers_.at(i)
                               % QCC_StatusText(status); // debug
        }

//        status = Signal(NULL, SESSION_ID_ALL_HOSTED, *TransferData, args1, 3);
//        if (status != ER_OK)
//            cerr << format("Error sending Signal (%1%).\n")
//                           % QCC_StatusText(status); // debug

        count++;
    }
    delete [] buf;

    MsgArg args2[2];
    args2[0].Set("s", dataId.c_str());
    args2[1].Set("u", 0);
    for(size_t i = 0; i < subscribers_.size(); ++i)
    {
        status = Signal(NULL, subscribers_.at(i), *DataIsReady, args2, 2);
        if (status != ER_OK)
            cerr << format("Error sending Signal to %1% (%2%).\n")
                           % subscribers_.at(i)
                           % QCC_StatusText(status); // debug
    }

//    status = Signal(NULL, SESSION, *DataIsReady, args2, 2);
//    if (status != ER_OK)
//        cerr << format("Error sending Signal to (%1%).\n")
//                        % QCC_StatusText(status); // debug
}

void AlljoynLocalChannel::write(const string &dataId,
                                 vector<uchar> &raw)
{
    // 1st Step: write local
    Channel::save(dataId, raw);

    // 2nd Step: check if there is any node need data
    if(subscribers_.size() == 0)
        return;

    // 3rd Step: send to remote.
    char* buf = new char[ALLJOYN_MAX_ARRAY_LEN];
    MsgArg args1[3];
    QStatus status;
    size_t length = raw.size();

    size_t offset = 0;
    int count = 0;
    while (length > 0)
    {
        size_t bufferLength = ALLJOYN_MAX_ARRAY_LEN;
        if (length > (size_t)ALLJOYN_MAX_ARRAY_LEN)
            length -= (size_t)ALLJOYN_MAX_ARRAY_LEN;
        else
        {
            bufferLength = length;
            length = 0;
        }

        for(size_t i = 0; i < bufferLength; ++i)
            buf[i] = raw[offset + i];

        offset += bufferLength;

        args1[0].Set("s", dataId.c_str());
        args1[1].Set("u", count);
        args1[2].Set("ay", bufferLength, buf);

        for(size_t i = 0; i < subscribers_.size(); ++i)
        {
            status = Signal(NULL, subscribers_.at(i), *TransferData, args1, 3);
            if (status != ER_OK)
                cerr << format("Error sending Signal to %1% (%2%).\n")
                               % subscribers_.at(i)
                               % QCC_StatusText(status); // debug
        }
        count++;
    }
    delete [] buf;

    MsgArg args2[2];
    args2[0].Set("s", dataId.c_str());
    args2[1].Set("u", 0);
    for(size_t i = 0; i < subscribers_.size(); ++i)
    {
        status = Signal(NULL, subscribers_.at(i), *DataIsReady, args2, 2);
        if (status != ER_OK)
            cerr << format("Error sending Signal to %1% (%2%).\n")
                           % subscribers_.at(i)
                           % QCC_StatusText(status); // debug
    }
}

}
