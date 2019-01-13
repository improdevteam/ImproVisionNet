// std
#include <iostream> // debug

// boost
#include <boost/format.hpp>

// impro
#include <impro/private/process/alljoyncameracontroller.hpp>
#include <impro/private/alljoynlocalnode.hpp>
#include <impro/private/alljoynremotenode.hpp>
#include <impro/private/alljoynspace.hpp>
#include <impro/application.hpp>

using namespace std;
using namespace boost;
using namespace ajn;

namespace impro { namespace process
{

const std::string CAMERA_CONTROLLER_INTERFACE = "impro.interface.camera.controller";

AlljoynCameraController::AlljoynCameraController(const string &id,
                                                 const string &dir,
                                                 Application  &app,
                                                 Space &space,
                                                 const string &ajnServicePath)
    : CameraController(id, dir, app, space),
      BusObject(ajnServicePath.c_str())
{
    AlljoynSpace &alljoynSpace = dynamic_cast<AlljoynSpace&>(space_);
    BusAttachment &bus = alljoynSpace.getBus();

    InterfaceDescription *iface = NULL;
    QStatus status = bus.CreateInterface(CAMERA_CONTROLLER_INTERFACE.c_str(), iface);
    if(status == ER_OK)
    {
        iface->AddSignal("TakePicture", "i", "postProcessing", 0);
        iface->Activate();
    }
    else if(status != ER_BUS_IFACE_ALREADY_EXISTS)
    {
        cout << format("Failed to create interface '%1%'.(%2%)\n")
                       % CAMERA_CONTROLLER_INTERFACE
                       % QCC_StatusText(status);
    }

    const InterfaceDescription *iface1 = bus.GetInterface(CAMERA_CONTROLLER_INTERFACE.c_str());
    status = AddInterface(*iface1);
    if (status == ER_OK)
    {
        TakePicture = iface1->GetMember("TakePicture");
        assert(TakePicture); // debug
    }
    else
    {
        cout << format("Failed to get interface '%1%'.(%2%)\n")
                       % CAMERA_CONTROLLER_INTERFACE
                       % QCC_StatusText(status);
    }

    bus.RegisterBusObject(*this);
}

void AlljoynCameraController::run()
{
}

void AlljoynCameraController::interrupt()
{
}

//void AlljoynCameraController::addRemoteNode(std::string remoteNodeId)
//{
//    mutex_.lock();
//    AlljoynRemoteNode &remoteNode = dynamic_cast<AlljoynRemoteNode&>(space_.getRemoteNode(remoteNodeId));
//    remoteSessionIds_.push_back(remoteNode.getAlljoynSessionId());
//    mutex_.unlock();
//}

//void AlljoynCameraController::setRemoteNodes(const std::vector<std::string> &remoteNodeIds)
//{
//    mutex_.lock();
//    remoteSessionIds_.clear();
//    for(size_t i = 0; i < remoteNodeIds.size(); ++i)
//    {
//        AlljoynRemoteNode &remoteNode = dynamic_cast<AlljoynRemoteNode&>(space_.getRemoteNode(remoteNodeIds.at(i)));
//        remoteSessionIds_.push_back(remoteNode.getAlljoynSessionId());
//    }
//    mutex_.unlock();
//}

void AlljoynCameraController::takePicture(const std::vector<string> &remoteNodeIds,
                                          int postProcessing)
{
    for(size_t i = 0; i < remoteNodeIds.size(); ++i)
    {
        AlljoynRemoteNode &remoteNode = dynamic_cast<AlljoynRemoteNode&>(space_.getRemoteNode(remoteNodeIds.at(i)));
        cout << remoteNode.getAlljoynSessionId() << endl;
        MsgArg inputs[1];
        inputs[0].Set("i", postProcessing);
        QStatus status = Signal(NULL, remoteNode.getAlljoynSessionId(), *TakePicture, inputs, 1);
        if (status != ER_OK)
            cerr << format("Error sending Signal to %1% (%2%).\n")
                            % remoteNode.getAlljoynSessionId()
                            % QCC_StatusText(status); // debug
        else
            cout << format("sending Signal to %1% (%2%) success.\n")
                           % remoteNode.getAlljoynSessionId()
                           % QCC_StatusText(status); // debug
    }
}



} }
