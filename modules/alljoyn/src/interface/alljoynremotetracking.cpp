// boost
#include <boost/format.hpp>
#include <boost/scoped_array.hpp>

// alljoyn
#include <alljoyn/BusAttachment.h>

// impro
#include <impro/private/interface/alljoyntracking.hpp>
#include <impro/private/alljoynspace.hpp>
#include <impro/private/alljoynremotenode.hpp>

using namespace std;
using namespace boost;
using namespace ajn;
using namespace cv;

namespace impro { namespace iface
{

const std::string TRACKING_INTERFACE = "impro.interface.tracking";

AlljoynRemoteTracking::AlljoynRemoteTracking(const std::string &type,
                                             Node &node)
    : Tracking(type, node)
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node.getSpace())).getBus();

    InterfaceDescription *iface = NULL;
    QStatus status = bus.CreateInterface(TRACKING_INTERFACE.c_str(), iface);
    if(status == ER_OK)
    {
        iface->AddMethod("SetTrackingMethod",          "ii",     NULL, "mode,method",                   0);
        iface->AddMethod("SetTemplateMatchParameters", "iadad", NULL, "mode,templateSiz,searchWindow", 0);
        iface->AddMethod("SetTrackingPoints",          "iad",    NULL, "mode,points",                   0);
        iface->AddMethod("SetTrackingOnOff",           "ib",     NULL, "mode,enabled",                  0);
        iface->Activate();
    }
    else if(status != ER_BUS_IFACE_ALREADY_EXISTS)
    {
        cout << boost::format("Failed to create interface '%1%'.(%2%)\n")
                              % TRACKING_INTERFACE
                              % QCC_StatusText(status);
    }
}

AlljoynRemoteTracking::~AlljoynRemoteTracking()
{

}


void AlljoynRemoteTracking::setTrackingMethod(CameraMode mode, TrackingMethod method)
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(TRACKING_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);
    MsgArg inputs[2];
    inputs[0].Set("i", mode);
    inputs[1].Set("i", method);
    Message reply(bus);
    QStatus status = remoteObj.MethodCall(TRACKING_INTERFACE.c_str(),
                                          "SetTrackingMethod",
                                          inputs,
                                          2,
                                          reply);
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'SetTrackingMethod' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
    }
}

void AlljoynRemoteTracking::setTemplateMatchParameters(CameraMode mode, double *templateSize, double *searchWindow)
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(TRACKING_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);
    MsgArg inputs[3];
    inputs[0].Set("i", mode);
    inputs[1].Set("ad", 4, templateSize);
    inputs[2].Set("ad", 4, searchWindow);
    Message reply(bus);
    QStatus status = remoteObj.MethodCall(TRACKING_INTERFACE.c_str(),
                                          "SetTemplateMatchParameters",
                                          inputs,
                                          3,
                                          reply);
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'SetTemplateMatchParameters' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
    }
}

void AlljoynRemoteTracking::setTrackingPoints(CameraMode mode, std::vector<Point2f> points)
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(TRACKING_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);
    size_t size = points.size() * 2;
    scoped_array<double> values(new double[size]);
//    double *values = new double[size];
    for(int i = 0; i < points.size(); ++i) {
        values[i * 2] = points.at(i).x;
        values[i * 2 + 1] = points.at(i).y;
    }
    MsgArg inputs[2];
    inputs[0].Set("i", mode);
    inputs[1].Set("ad", size, values.get());
    Message reply(bus);
    QStatus status = remoteObj.MethodCall(TRACKING_INTERFACE.c_str(),
                                          "SetTrackingPoints",
                                          inputs,
                                          2,
                                          reply);
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'setTrackingPoints' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
    }

//    delete values;
}

void AlljoynRemoteTracking::setTrackingOnOff(CameraMode mode, bool enabled)
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(TRACKING_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);
    MsgArg inputs[2];
    inputs[0].Set("i", mode);
    inputs[1].Set("b", enabled);
    Message reply(bus);
    QStatus status = remoteObj.MethodCall(TRACKING_INTERFACE.c_str(),
                                          "SetTrackingOnOff",
                                          inputs,
                                          2,
                                          reply);
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'SetTrackingOnOff ' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
    }

}


// deprecated ----------------------------------------------

//void AlljoynRemoteTracking::setSearchWindow(double x0, double x1, double y0, double y1)
//{
//    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
//    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
//    ProxyBusObject remoteObj(bus,
//                             node.getAlljoynServiceName().c_str(),
//                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
//                             node.getAlljoynSessionId());
//    const InterfaceDescription *iface = bus.GetInterface(TRACKING_INTERFACE.c_str());
//    remoteObj.AddInterface(*iface);
//    double *val = new double[4];
//    val[0] = x0; val[1] = x1; val[2] = y0; val[3] = y1;
//    MsgArg inputs[1];
//    inputs[0].Set("ad", 4, val);
//    Message reply(bus);
//    QStatus status = remoteObj.MethodCall(TRACKING_INTERFACE.c_str(),
//                                          "SetSearchWindow",
//                                          inputs,
//                                          1,
//                                          reply);
//    if (ER_OK != status)
//    {
//        cerr << boost::format("'%1%(%2%) 'SetSearchWindow' fail(%3%).\n")
//                       % node.getAlljoynServiceName()
//                       % node.getAlljoynServicePath()
//                       % QCC_StatusText(status);
//    }
//    delete val;
//}

//void AlljoynRemoteTracking::setTemplateSize(double x0, double x1, double y0, double y1)
//{
//    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
//    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
//    ProxyBusObject remoteObj(bus,
//                             node.getAlljoynServiceName().c_str(),
//                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
//                             node.getAlljoynSessionId());
//    const InterfaceDescription *iface = bus.GetInterface(TRACKING_INTERFACE.c_str());
//    remoteObj.AddInterface(*iface);
//    double *val = new double[4];
//    val[0] = x0; val[1] = x1; val[2] = y0; val[3] = y1;
//    MsgArg inputs[1];
//    inputs[0].Set("ad", 4, val);
//    Message reply(bus);
//    QStatus status = remoteObj.MethodCall(TRACKING_INTERFACE.c_str(),
//                                          "SetTemplateSize",
//                                          inputs,
//                                          1,
//                                          reply);
//    if (ER_OK != status)
//    {
//        cerr << boost::format("'%1%(%2%) 'SetTemplateSize' fail(%3%).\n")
//                       % node.getAlljoynServiceName()
//                       % node.getAlljoynServicePath()
//                       % QCC_StatusText(status);
//    }
//    delete val;
//}

//void AlljoynRemoteTracking::startTracking()
//{
//    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
//    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
//    ProxyBusObject remoteObj(bus,
//                             node.getAlljoynServiceName().c_str(),
//                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
//                             node.getAlljoynSessionId());
//    const InterfaceDescription *iface = bus.GetInterface(TRACKING_INTERFACE.c_str());
//    remoteObj.AddInterface(*iface);
//    Message reply(bus);
//    QStatus status = remoteObj.MethodCall(TRACKING_INTERFACE.c_str(),
//                                          "StartTracking",
//                                          NULL,
//                                          0,
//                                          reply);
//    if (ER_OK != status)
//    {
//        cerr << boost::format("'%1%(%2%) 'StartTracking' fail(%3%).\n")
//                       % node.getAlljoynServiceName()
//                       % node.getAlljoynServicePath()
//                       % QCC_StatusText(status);
//    }
//}

//void AlljoynRemoteTracking::stopTracking()
//{
//    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
//    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
//    ProxyBusObject remoteObj(bus,
//                             node.getAlljoynServiceName().c_str(),
//                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
//                             node.getAlljoynSessionId());
//    const InterfaceDescription *iface = bus.GetInterface(TRACKING_INTERFACE.c_str());
//    remoteObj.AddInterface(*iface);
//    Message reply(bus);
//    QStatus status = remoteObj.MethodCall(TRACKING_INTERFACE.c_str(),
//                                          "StopTracking",
//                                          NULL,
//                                          0,
//                                          reply);
//    if (ER_OK != status)
//    {
//        cerr << boost::format("'%1%(%2%) 'stopTracking' fail(%3%).\n")
//                       % node.getAlljoynServiceName()
//                       % node.getAlljoynServicePath()
//                       % QCC_StatusText(status);
//    }
//}


} }

