// boost
#include <boost/format.hpp>

// alljoyn
#include <alljoyn/BusAttachment.h>



// impro
#include <impro/private/interface/alljoyntriangulation.hpp>
#include <impro/private/alljoynspace.hpp>
#include <impro/private/alljoynremotenode.hpp>

using namespace std;
using namespace boost;
using namespace ajn;
using namespace cv;

namespace impro { namespace iface
{

const std::string TRIANGULATION_INTERFACE = "impro.interface.triangulation";

AlljoynRemoteTriangulation::AlljoynRemoteTriangulation(const std::string &type,
                                                       Node &node)
    : Triangulation(type, node)
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node.getSpace())).getBus();

    InterfaceDescription *iface = NULL;
    QStatus status = bus.CreateInterface(TRIANGULATION_INTERFACE.c_str(), iface);
    if(status == ER_OK)
    {
        iface->AddMethod("SetParameters", "issad",  NULL, "type,leftNode,rightNode,val", 0);
        iface->AddMethod("StartTriangulation", NULL,  NULL, "", 0);
        iface->AddMethod("StopTriangulation", NULL,  NULL, "", 0);
        iface->Activate();
    }
    else if(status != ER_BUS_IFACE_ALREADY_EXISTS)
    {
        cout << boost::format("Failed to create interface '%1%'.(%2%)\n")
                              % TRIANGULATION_INTERFACE
                              % QCC_StatusText(status);
    }
}

AlljoynRemoteTriangulation::~AlljoynRemoteTriangulation()
{

}

void AlljoynRemoteTriangulation::setParameters(int type,
                                               string leftNode,
                                               string rightNode,
                                               Mat camera1Matrix,
                                               Mat camera1DistCoeffs,
                                               Mat camera2Matrix,
                                               Mat camera2DistCoeffs,
                                               Mat R, Mat T,
                                               Mat R1, Mat P1,
                                               Mat R2, Mat P2,
                                               std::vector<Point2f> coord1,
                                               std::vector<Point2f> coord2)
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(TRIANGULATION_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);

    double *val = new double[116];

    // 0
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            val[i * 3 + j] = camera1Matrix.at<double>(i, j);
        }
    }

    // 0 + 9 = 9
    for(int i = 0; i < 14; ++i)
    {
        val[9 + i] = camera1DistCoeffs.at<double>(0, i);
    }

    // 0 + 9 + 14 = 23
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            val[23 + i * 3 + j] = camera2Matrix.at<double>(i, j);
        }
    }

    // 0 + 9 + 14 + 9 = 32
    for(int i = 0; i < 14; ++i)
    {
        val[32 + i] = camera2DistCoeffs.at<double>(0, i);
    }

    // 0 + 9 + 14 + 9 + 14 = 46
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            val[46 + i * 3 + j] = R.at<double>(i, j);
        }
    }

    // 0 + 9 + 14 + 9 + 14 + 9 = 55
    for(int i = 0; i < 3; ++i)
    {
        val[55 + i] = T.at<double>(i, 0);
    }

    // 0 + 9 + 14 + 9 + 14 + 9 + 3 = 58
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            val[58 + i * 3 + j] = R1.at<double>(i, j);
        }
    }

    // 0 + 9 + 14 + 9 + 14 + 9 + 3 + 9 = 67
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            val[67 + i * 4 + j] = P1.at<double>(i, j);
        }
    }

    // 0 + 9 + 14 + 9 + 14 + 9 + 3 + 9 + 12 = 79
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            val[79 + i * 3 + j] = R2.at<double>(i, j);
        }
    }

    // 0 + 9 + 14 + 9 + 14 + 9 + 3 + 9 + 12 + 9 = 88
    for(int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            val[88 + i * 4 + j] = P2.at<double>(i, j);
        }
    }

    // 0 + 9 + 14 + 9 + 14 + 9 + 3 + 9 + 12 + 9 + 12 = 100
    for(int i = 0; i < 4; ++i)
    {
        val[100 + i * 2] = coord1.at(i).x;
        val[100 + i * 2 + 1] = coord1.at(i).y;
    }

    // 0 + 9 + 14 + 9 + 14 + 9 + 3 + 9 + 12 + 9 + 12 + 8 = 108
    for(int i = 0; i < 4; ++i)
    {
        val[108 + i * 2] = coord2.at(i).x;
        val[108 + i * 2 + 1] = coord2.at(i).y;
    }

    MsgArg inputs[4];
    inputs[0].Set("i", type);
    inputs[1].Set("s", leftNode.c_str());
    inputs[2].Set("s", rightNode.c_str());
    inputs[3].Set("ad", 116, val);
    Message reply(bus);
    QStatus status = remoteObj.MethodCall(TRIANGULATION_INTERFACE.c_str(),
                                          "SetParameters",
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
    delete val;
}


void AlljoynRemoteTriangulation::startTriangulation()
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(TRIANGULATION_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);
    Message reply(bus);
    QStatus status = remoteObj.MethodCall(TRIANGULATION_INTERFACE.c_str(),
                                          "StartTriangulation",
                                          NULL,
                                          0,
                                          reply);
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'StartTriangulation' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
    }
}

void AlljoynRemoteTriangulation::stopTriangulation()
{
    BusAttachment &bus = (dynamic_cast<AlljoynSpace&>(node_.getSpace())).getBus();
    AlljoynRemoteNode &node = dynamic_cast<AlljoynRemoteNode&>(node_);
    ProxyBusObject remoteObj(bus,
                             node.getAlljoynServiceName().c_str(),
                             node.getAlljoynServicePath().append("/").append("CameraProcess").c_str(),
                             node.getAlljoynSessionId());
    const InterfaceDescription *iface = bus.GetInterface(TRIANGULATION_INTERFACE.c_str());
    remoteObj.AddInterface(*iface);
    Message reply(bus);
    QStatus status = remoteObj.MethodCall(TRIANGULATION_INTERFACE.c_str(),
                                          "StopTriangulation",
                                          NULL,
                                          0,
                                          reply);
    if (ER_OK != status)
    {
        cerr << boost::format("'%1%(%2%) 'StopTriangulation' fail(%3%).\n")
                       % node.getAlljoynServiceName()
                       % node.getAlljoynServicePath()
                       % QCC_StatusText(status);
    }
}


} }

