// boost
#include <boost/format.hpp>

// alljoyn
#include <alljoyn/BusAttachment.h>



// impro
#include <impro/private/interface/alljoyncamera.hpp>
#include <impro/private/alljoynspace.hpp>
#include <impro/private/alljoynremotenode.hpp>

using namespace std;
using namespace boost;
using namespace ajn;
using namespace cv;

namespace impro { namespace iface
{

const std::string CAMERA_INTERFACE = "impro.interface.camera";

AlljoynRemoteCamera::AlljoynRemoteCamera(const std::string &type,
                                         Node &node)
    : Camera(type, node)
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node.getSpace())).getBus();

    InterfaceDescription *iface = NULL;
    QStatus status = bus.CreateInterface(CAMERA_INTERFACE.c_str(), iface);
    if(status == ER_OK)
    {
        iface->AddMethod("TakePicture", NULL,  NULL, "", 0);
        iface->AddMethod("SetFocusMode", "i",  NULL, "focusMode", 0);
        iface->AddMethod("ZoomIn", NULL,  NULL, "", 0);
        iface->AddMethod("ZoomOut", NULL,  NULL, "", 0);
        iface->AddMethod("SetPreviewTransferInterval", "i",  NULL, "interval", 0);
        iface->AddMethod("AutoTakingPictures", "bi",  NULL, "enabled,interval", 0);
        iface->AddMethod("GetInfo", NULL,  "s", "info", 0);
        iface->AddMethod("GetPreviewSize", NULL,  "ai", "size", 0);
        iface->AddMethod("GetPictureSize", NULL,  "ai", "size", 0);
        iface->AddMethod("GetLinearAcceleration", NULL,  "ad", "acc", 0);
        iface->Activate();
    }
    else if(status != ER_BUS_IFACE_ALREADY_EXISTS)
    {
        cout << boost::format("Failed to create interface '%1%'.(%2%)\n")
                              % CAMERA_INTERFACE
                              % QCC_StatusText(status);
    }
}

AlljoynRemoteCamera::~AlljoynRemoteCamera()
{

}

void AlljoynRemoteCamera::takePicture()
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(CAMERA_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);
    Message reply(bus);
    QStatus status = remoteObj.MethodCall(CAMERA_INTERFACE.c_str(),
                                          "TakePicture",
                                          NULL,
                                          0,
                                          reply);
        if (ER_OK != status)
        {
            cerr << boost::format("'%1%(%2%) 'TakePicture' fail(%3%).\n")
                           % node.getAlljoynServiceName()
                           % node.getAlljoynServicePath()
                           % QCC_StatusText(status);
        }
}



void AlljoynRemoteCamera::setFocusMode(FocusMode focusMode)
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(CAMERA_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);
    MsgArg inputs[1];
    inputs[0].Set("i", focusMode);
    Message reply(bus);
    QStatus status = remoteObj.MethodCall(CAMERA_INTERFACE.c_str(),
                                          "SetFocusMode",
                                          inputs,
                                          1,
                                          reply);
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'SetFocusMode ' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
    }
}



void AlljoynRemoteCamera::zoomIn()
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(CAMERA_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);
    Message reply(bus);
    QStatus status = remoteObj.MethodCall(CAMERA_INTERFACE.c_str(),
                                          "ZoomIn",
                                          NULL,
                                          0,
                                          reply);
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'ZoomIn' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
    }
}

void AlljoynRemoteCamera::zoomOut()
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(CAMERA_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);
    Message reply(bus);
    QStatus status = remoteObj.MethodCall(CAMERA_INTERFACE.c_str(),
                                          "ZoomOut",
                                          NULL,
                                          0,
                                          reply);
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'ZoomOut' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
    }
}

void AlljoynRemoteCamera::setPreviewTransferInterval(int interval)
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(CAMERA_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);
    MsgArg inputs[1];
    inputs[0].Set("i", interval);
    Message reply(bus);
    QStatus status = remoteObj.MethodCall(CAMERA_INTERFACE.c_str(),
                                          "SetPreviewTransferInterval",
                                          inputs,
                                          1,
                                          reply);
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'SetPreviewTransferInterval ' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
    }
}

void AlljoynRemoteCamera::autoTakingPictures(bool enabled, int interval)
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(CAMERA_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);
    MsgArg inputs[2];
    inputs[0].Set("b", enabled);
    inputs[1].Set("i", interval);
    Message reply(bus);
    QStatus status = remoteObj.MethodCall(CAMERA_INTERFACE.c_str(),
                                          "AutoTakingPictures",
                                          inputs,
                                          2,
                                          reply);
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'AutoTakingPictures ' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
    }
}

string AlljoynRemoteCamera::getInfo()
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(CAMERA_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);

    Message reply(bus);
    QStatus status = remoteObj.MethodCall(CAMERA_INTERFACE.c_str(),
                                          "GetInfo",
                                          NULL,
                                          0,
                                          reply);
    string retStr = "";
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'GetLinearAcceleration' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
    }
    else
    {
        retStr = reply->GetArg(0)->v_string.str;
    }
    return retStr;
}

Size AlljoynRemoteCamera::getPreviewSize()
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(CAMERA_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);

    Message reply(bus);
    QStatus status = remoteObj.MethodCall(CAMERA_INTERFACE.c_str(),
                                          "GetPreviewSize",
                                          NULL,
                                          0,
                                          reply);
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'GetPreviewSize' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
        return Size(0, 0);
    }
    else
    {
        size_t n;
        int *previewSize;
        reply->GetArg(0)->Get("ai", &n, &previewSize);
        if(n == 2)
            return Size(previewSize[0], previewSize[1]);
        else
            return Size(0, 0);
    }
}

Size AlljoynRemoteCamera::getPictureSize()
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(CAMERA_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);

    Message reply(bus);
    QStatus status = remoteObj.MethodCall(CAMERA_INTERFACE.c_str(),
                                          "GetPictureSize",
                                          NULL,
                                          0,
                                          reply);
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'GetPictureSize' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
        return Size(0, 0);
    }
    else
    {
        size_t n;
        int *pictureSize;
        reply->GetArg(0)->Get("ai", &n, &pictureSize);
        if(n == 2)
            return Size(pictureSize[0], pictureSize[1]);
        else
            return Size(0, 0);
    }
}

Vec3d AlljoynRemoteCamera::getLinearAcceleration()
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(CAMERA_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);

    Message reply(bus);
    QStatus status = remoteObj.MethodCall(CAMERA_INTERFACE.c_str(),
                                          "GetLinearAcceleration",
                                          NULL,
                                          0,
                                          reply);
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'GetLinearAcceleration' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
        Vec3d retVal(0.0f, 0.0f, 0.0f);
        return retVal;
    }
    else
    {
        size_t bufAccSize;
        double *bufAcc;
        reply->GetArg(0)->Get("ad", &bufAccSize, &bufAcc);
        if(bufAccSize == 3)
        {
            Vec3d retVal(bufAcc[0], bufAcc[1], bufAcc[2]);
            return retVal;
        }
        else
        {
            Vec3d retVal(0.0f, 0.0f, 0.0f);
            return retVal;
        }
    }
}

} }

// deprecated ----------------------------------------------

//void AlljoynRemoteCamera::takePicture(int postProcessing)
//{
//    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
//    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
//    ProxyBusObject remoteObj(bus,
//                             node.getAlljoynServiceName().c_str(),
//                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
//                             node.getAlljoynSessionId());
//    const InterfaceDescription *iface = bus.GetInterface(CAMERA_INTERFACE.c_str());
//    remoteObj.AddInterface(*iface);
//    MsgArg inputs[1];
//    inputs[0].Set("i", postProcessing);
//    Message reply(bus);
//    QStatus status = remoteObj.MethodCall(CAMERA_INTERFACE.c_str(),
//                                          "TakePicture",
//                                          inputs,
//                                          1,
//                                          reply);
//    if (ER_OK != status)
//    {
//        cerr << boost::format("'%1%(%2%) 'TakePicture' fail(%3%).\n")
//                       % node.getAlljoynServiceName()
//                       % node.getAlljoynServicePath()
//                       % QCC_StatusText(status);
//    }
//}

//void AlljoynRemoteCamera::autoFocus()
//{
//    cout << "autoFocus 1" << endl;
//    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
//    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
//    ProxyBusObject remoteObj(bus,
//                             node.getAlljoynServiceName().c_str(),
//                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
//                             node.getAlljoynSessionId());
//    cout << "autoFocus 2" << endl;
//    const InterfaceDescription *iface = bus.GetInterface(CAMERA_INTERFACE.c_str());
//    remoteObj.AddInterface(*iface);
//    Message reply(bus);
//    cout << "autoFocus 3" << endl;
//    QStatus status = remoteObj.MethodCall(CAMERA_INTERFACE.c_str(),
//                                          "AutoFocus",
//                                          NULL,
//                                          0,
//                                          reply);
//    cout << "autoFocus 4" << endl;
//    if (ER_OK != status)
//    {
//        cerr << boost::format("'%1%(%2%) 'AutoFocus' fail(%3%).\n")
//                       % node.getAlljoynServiceName()
//                       % node.getAlljoynServicePath()
//                       % QCC_StatusText(status);
//    }
//}


