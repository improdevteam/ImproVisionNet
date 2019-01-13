// boost
#include <boost/format.hpp>

// alljoyn
#include <alljoyn/BusAttachment.h>



// impro
#include <impro/private/interface/alljoynk201711.hpp>
#include <impro/private/alljoynspace.hpp>
#include <impro/private/alljoynremotenode.hpp>

using namespace std;
using namespace boost;
using namespace ajn;
using namespace cv;

namespace impro { namespace iface
{

const std::string K201711_INTERFACE = "impro.interface.k201711";

AlljoynRemoteK201711::AlljoynRemoteK201711(const std::string &type,
                                           Node &node)
    : K201711(type, node)
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node.getSpace())).getBus();

    InterfaceDescription *iface = NULL;
    QStatus status = bus.CreateInterface(K201711_INTERFACE.c_str(), iface);
    if(status == ER_OK)
    {
        iface->AddMethod("SetCameraParameters", "ad",  NULL, "val", 0);
        iface->AddMethod("SetK201711Parameters", "iddi",  NULL, "interval,threshold1,threshold2,duration", 0);
        iface->AddMethod("SetReferencePoints", "ad",  NULL, "val", 0);
        iface->AddMethod("SetTrackingPoints", "ad",  NULL, "val", 0);
        iface->AddMethod("StartK201711", NULL,  NULL, "", 0);
        iface->AddMethod("StopK201711", NULL,  NULL, "", 0);
        iface->Activate();
    }
    else if(status != ER_BUS_IFACE_ALREADY_EXISTS)
    {
        cout << boost::format("Failed to create interface '%1%'.(%2%)\n")
                              % K201711_INTERFACE
                              % QCC_StatusText(status);
    }
}

AlljoynRemoteK201711::~AlljoynRemoteK201711()
{

}

void AlljoynRemoteK201711::setCameraParameters(Mat cameraMatrix,
                                         Mat cameraDistCoeffs)
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(K201711_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);

    double *val = new double[23];

    // 0
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            val[i * 3 + j] = cameraMatrix.at<double>(i, j);
        }
    }

    // 0 + 9 = 9
    for(int i = 0; i < 14; ++i)
    {
        val[9 + i] = cameraDistCoeffs.at<double>(0, i);
    }

    MsgArg inputs[1];
    inputs[0].Set("ad", 23, val);
    Message reply(bus);
    QStatus status = remoteObj.MethodCall(K201711_INTERFACE.c_str(),
                                          "SetCameraParameters",
                                          inputs,
                                          1,
                                          reply);
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'SetParameters' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
    }
    delete val;
}

void AlljoynRemoteK201711::setK201711Parameters(int interval,
                                                double threshold1,
                                                double threshold2,
                                                int duration)
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(K201711_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);
    MsgArg inputs[4];
    inputs[0].Set("i", interval);
    inputs[1].Set("d", threshold1);
    inputs[2].Set("d", threshold2);
    inputs[3].Set("i", duration);
    Message reply(bus);
    QStatus status = remoteObj.MethodCall(K201711_INTERFACE.c_str(),
                                          "SetK201711Parameters",
                                          inputs,
                                          4,
                                          reply);
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'SetParameters' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
    }

}

void AlljoynRemoteK201711::setReferencePoints(std::vector<Point2f> referencePoints)
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(K201711_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);
    int size = referencePoints.size() * 2;
    double *val = new double[size];
    for(int i = 0; i < referencePoints.size(); ++i) {
        val[i * 2] = referencePoints.at(i).x;
        val[i * 2 + 1] = referencePoints.at(i).y;
    }
    MsgArg inputs[1];
    inputs[0].Set("ad", size, val);
    Message reply(bus);
    QStatus status = remoteObj.MethodCall(K201711_INTERFACE.c_str(),
                                          "SetReferencePoints",
                                          inputs,
                                          1,
                                          reply);
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'SetReferencePoints' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
    }
    delete val;
}

void AlljoynRemoteK201711::setTrackingPoints(std::vector<Point2f> trackingPoints)
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(K201711_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);
    int size = trackingPoints.size() * 2;
    double *val = new double[size];
    for(int i = 0; i < trackingPoints.size(); ++i) {
        val[i * 2] = trackingPoints.at(i).x;
        val[i * 2 + 1] = trackingPoints.at(i).y;
    }
    MsgArg inputs[1];
    inputs[0].Set("ad", size, val);
    Message reply(bus);
    QStatus status = remoteObj.MethodCall(K201711_INTERFACE.c_str(),
                                          "SetTrackingPoints",
                                          inputs,
                                          1,
                                          reply);
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'SetTrackingPoints' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
    }
    delete val;
}

void AlljoynRemoteK201711::startK201711()
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(K201711_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);
    Message reply(bus);
    QStatus status = remoteObj.MethodCall(K201711_INTERFACE.c_str(),
                                          "StartK201711",
                                          NULL,
                                          0,
                                          reply);
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'StartK201711' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
    }
}

void AlljoynRemoteK201711::stopK201711()
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(K201711_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);
    Message reply(bus);
    QStatus status = remoteObj.MethodCall(K201711_INTERFACE.c_str(),
                                          "StopK201711",
                                          NULL,
                                          0,
                                          reply);
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'StopK201711' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
    }
}


} }

