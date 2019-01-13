// std
#include <iostream> // debug
#include <fstream>

// boost
#include <boost/format.hpp>
#include <boost/chrono.hpp>

// alljoyn
#include <alljoyn/BusAttachment.h>

// impro
#include <impro/private/alljoynutil.hpp>
#include <impro/private/alljoynspace.hpp>
#include <impro/private/alljoynremotechannel.hpp>
#include <impro/space.hpp>
#include <impro/node.hpp>

// impro legacy
#include <opencv2/highgui.hpp>
#include <impro/data/imageacc.hpp>
#include <impro/channelobserver.hpp>

using namespace std;
using namespace boost;
using namespace ajn;
using namespace cv;

/*
 * class AlljoynRemoteChannel
 */
namespace impro
{

AlljoynRemoteChannel::AlljoynRemoteChannel(const string &dataType,
                                           const string &id,
                                           unsigned int limit,
                                           Node &node,
                                           SessionPort sessionPort,
                                           TransportMask transport,
                                           SessionId sessionId)
    : RemoteChannel(dataType, id, limit, node),
      AlljoynRemoteObject(AlljoynUtil::ChannelServiceName(node.getId(), id, sessionPort, dataType),
                          AlljoynUtil::ChannelServicePath(node.getId(), id),
                          sessionPort,
                          transport,
                          sessionId,
                          (dynamic_cast<AlljoynSpace&>(node.getSpace())).getBus() )
{
    // stop transferTimer
    transferTimer.stop();

    const InterfaceDescription *iface = bus_.GetInterface(AlljoynUtil::CHANNEL_INTERFACE.c_str());

    std::cerr << "Register TransferFile\n" ;
    const InterfaceDescription::Member *member1 = iface->GetMember("TransferFile");
    QStatus status =  bus_.RegisterSignalHandler(this,
                                                static_cast<MessageReceiver::SignalHandler>(&AlljoynRemoteChannel::TransferFile),
                                                member1,
                                                ajnServicePath_.c_str());
    if(status != ER_OK)
        std::cout << "Register signal handler for TransferFile fail\n";

            std::cerr << "Register FileIsReady\n" ;
    const InterfaceDescription::Member *member2 = iface->GetMember("FileIsReady");
    status = bus_.RegisterSignalHandler(this,
                                       static_cast<MessageReceiver::SignalHandler>(&AlljoynRemoteChannel::FileIsReady),
                                       member2,
                                       ajnServicePath_.c_str());
    if(status != ER_OK)
        std::cout << "Register signal handler for FileIsReady fail\n";


    cerr << "Register TransferData\n" ;
    const InterfaceDescription::Member *member3 = iface->GetMember("TransferData");
    status =  bus_.RegisterSignalHandler(this,
                                                 static_cast<MessageReceiver::SignalHandler>(&AlljoynRemoteChannel::TransferData),
                                                 member3,
                                                 ajnServicePath_.c_str());
    if(status != ER_OK)
        cerr << "Register signal handler for TransferData fail\n";

    cerr << "Register DataIsReady\n" ;
    const InterfaceDescription::Member *member4 = iface->GetMember("DataIsReady");
    status = bus_.RegisterSignalHandler(this,
                                        static_cast<MessageReceiver::SignalHandler>(&AlljoynRemoteChannel::DataIsReady),
                                        member4,
                                        ajnServicePath_.c_str());
    if(status != ER_OK)
        cerr << "Register signal handler for DataIsReady fail\n";

}

AlljoynRemoteChannel::~AlljoynRemoteChannel()
{

}

void AlljoynRemoteChannel::subscribe(ChannelObserver *observer)
{
    if(observers_.size() == 0)
    {
//        bus_.EnableConcurrentCallbacks();
        SessionId sessionId;
        SessionOpts opts(SessionOpts::TRAFFIC_MESSAGES,
                         true,
                         SessionOpts::PROXIMITY_ANY,
                         TRANSPORT_ANY);
        cout << getAlljoynServiceName() << endl;
        cout << getAlljoynSessionPort() << endl;
        QStatus status = bus_.JoinSession(getAlljoynServiceName().c_str(),
                                           getAlljoynSessionPort(),
                                           NULL,
                                           sessionId,
                                           opts);
        if (ER_OK != status)
        {
            cerr << boost::format("JoinSession failed(Channel) try Legacy. (status=%1%)\n")
                                   %  QCC_StatusText(status); // debug

            // Legacy
            int lastidx = getAlljoynServiceName().find_last_of(".");
            string serviceName = getAlljoynServiceName().substr(0, lastidx);

            status = bus_.JoinSession(serviceName.c_str(),
                                               getAlljoynSessionPort(),
                                               NULL,
                                               sessionId,
                                               opts);
            if (ER_OK != status)
            {
                cerr << boost::format("JoinSession failed(Channel). (status=%1%)\n")
                                       %  QCC_StatusText(status); // debug
            }
            else
            {
                setAlljoynSessionId(sessionId);
            }
        }
        else
        {
            setAlljoynSessionId(sessionId);
        }
    }

    Channel::subscribe(observer);

}

void AlljoynRemoteChannel::unsubscribe(ChannelObserver *observer)
{
    Channel::unsubscribe(observer);
    if(observers_.size() == 0)
    {
        QStatus status = bus_.LeaveSession(getAlljoynSessionId());
        if (ER_OK != status)
        {
            cerr << boost::format("leaveSession failed(Channel). (status=%1%)\n")
                                   %  QCC_StatusText(status); // debug
        }
    }
}

// Handler --------------------------------------------------------
void AlljoynRemoteChannel::TransferData(const InterfaceDescription::Member *member,
                                        const char *sourcePath,
                                        Message &msg)
{
    if(transferTimer.is_stopped())
        transferTimer.start();

    uint32_t count;
    size_t size;
    uint8_t *data;
    msg->GetArg(1)->Get("u", &count);
    msg->GetArg(2)->Get("ay", &size, &data);
    if (size != 0)
        buffer.insert(buffer.end(), data, data + size);

}

void AlljoynRemoteChannel::DataIsReady(const InterfaceDescription::Member *member,
                                       const char *sourcePath,
                                       Message &msg)
{
    if (buffer.size() > 0)
    {
        // ToDo... need fix... important...
//        Data *data = dataFactory_->create();
//        data->deserialize(buffer);
//        string identifier(msg->GetArg(0)->v_string.str);
//        BasicOutputChannel::write(identifier, *data);
//        delete data;

        string dataId(msg->GetArg(0)->v_string.str);

        // peformance recording
        if(!transferTimer.is_stopped())
            transferTimer.stop();

        chrono::duration<double> wallSec = chrono::nanoseconds(transferTimer.elapsed().wall);
        chrono::duration<double> userSec = chrono::nanoseconds(transferTimer.elapsed().user);
        chrono::duration<double> systemSec = chrono::nanoseconds(transferTimer.elapsed().system);

        string fullPath(dir_);
        fullPath.append("/performance.log");
        ofstream outputFile(fullPath.c_str(), ofstream::app);
        outputFile << boost::format("%1%,%2%,%3%,%4%,%5%\n")
                      % dataId % buffer.size()
                      % wallSec.count()
                      % userSec.count()
                      % systemSec.count();
        outputFile.close();


        // SAve
        Channel::save(dataId, buffer);
        buffer.clear();
        std::cerr << boost::format("DataIsReady(%1%)(%2%)(%3%)\n")
                     % id_ % dataId % buffer.size();


    }
}


// Legacy ------------------------------------------------------------
void AlljoynRemoteChannel::TransferFile(const InterfaceDescription::Member *member,
                                       const char *sourcePath,
                                       Message &msg)
{
    if(transferTimer.is_stopped())
        transferTimer.start();

    uint32_t count;
    size_t size;
    uint8_t *data;
    msg->GetArg(1)->Get("u", &count);
    msg->GetArg(2)->Get("ay", &size, &data);
    if (size != 0)
        buffer.insert(buffer.end(), data, data + size);

}

void AlljoynRemoteChannel::FileIsReady(const InterfaceDescription::Member *member,
                                       const char *sourcePath,
                                       Message &msg)
{
    string dataId(msg->GetArg(0)->v_string.str);

    // peformance recording
    if(!transferTimer.is_stopped())
        transferTimer.stop();

    chrono::duration<double> wallSec = chrono::nanoseconds(transferTimer.elapsed().wall);
    chrono::duration<double> userSec = chrono::nanoseconds(transferTimer.elapsed().user);
    chrono::duration<double> systemSec = chrono::nanoseconds(transferTimer.elapsed().system);

    string fullPath(dir_);
    fullPath.append("/performance.log");
    ofstream outputFile(fullPath.c_str(), ofstream::app);
    outputFile << boost::format("%1%,%2%,%3%,%4%,%5%\n")
                  % dataId % buffer.size()
                  % wallSec.count()
                  % userSec.count()
                  % systemSec.count();
    outputFile.close();


    // save ....
    std::cerr << boost::format("FileIsReady(%1%)\n")
                 % id_;
    if (buffer.size() > 0)
    {
        Mat mat = imdecode(buffer, IMREAD_COLOR);
        buffer.clear();
        size_t bufAccSize;
        double *bufAcc;
        msg->GetArg(2)->Get("ad", &bufAccSize, &bufAcc);
        size_t size = bufAccSize / 3;
        std::vector<cv::Vec3f> vecAcc;
        for(size_t i = 0; i < size; ++i)
        {
            Vec3f acc(bufAcc[0 + i * 3], bufAcc[1 + i * 3], bufAcc[2 + i * 3]);
            vecAcc.push_back(acc);
        }

        data::ImageAcc* imgAcc = dynamic_cast<data::ImageAcc*>(data_);
        imgAcc->image_.mat_ = mat;
        imgAcc->acc_.vec_ = vecAcc;
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
}


}


