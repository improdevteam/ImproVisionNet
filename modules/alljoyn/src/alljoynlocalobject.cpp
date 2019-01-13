#include <iostream>

// boost
#include <boost/format.hpp>

// alljoyn
#include <impro/private/alljoynlocalobject.hpp>
#include <impro/private/alljoynlocallistener.hpp>

using namespace std;
using namespace boost;
using namespace ajn;

namespace impro
{

AlljoynLocalObject::AlljoynLocalObject(std::string ajnServicePath,
                             BusAttachment &ajnBus)
    : BusObject(ajnServicePath.c_str()),
      ajnServicePath_(ajnServicePath)
{
    listener_ = new AlljoynLocalListener(*this);

    // debug
    cout << "AlljoynLocalObject" << endl;

    QStatus status = ajnBus.RegisterBusObject(*this);
    if(ER_OK != status)
        cerr << format("RegisterBusObject('%1%') failed.(%2%)\n")
                       % ajnServicePath_
                       % QCC_StatusText(status); // debug
}

AlljoynLocalObject::~AlljoynLocalObject()
{
    // CancelAdvertiseName
//    QStatus status = bus->CancelAdvertiseName(ajnServiceName_.c_str(), TRANSPORT_ANY);
//    if(ER_OK != status) // debug
//       cerr << format("CancelAdvertiseName('%1%') failed.(%2%)\n")
//                      % ajnServiceName_
//                      % std::string(QCC_StatusText(status));

    // UnregisterBusObject
//    bus->UnregisterBusObject(*this);

    if(listener_)
    {
        delete listener_;
        listener_ = NULL;
    }
}

void AlljoynLocalObject::advertise()
{
    const uint32_t flags = DBUS_NAME_FLAG_REPLACE_EXISTING | DBUS_NAME_FLAG_DO_NOT_QUEUE;
    QStatus status = bus->RequestName(ajnServiceName_.c_str(), flags);
    if(ER_OK != status)
        cerr << format("RequestName('%1%') failed.(%2%)\n")
                       % ajnServiceName_
                       % QCC_StatusText(status); // debug

    status = bus->AdvertiseName(ajnServiceName_.c_str(),
                                TRANSPORT_TCP | TRANSPORT_LOCAL);
    if (ER_OK != status)
        cerr << format("AdvertiseName('%1%') failed.(%2%)\n")
                       % ajnServiceName_
                       % QCC_StatusText(status); // debug
}

void AlljoynLocalObject::addSubscriber(ajn::SessionId sessionId)
{
    subscribers_.push_back(sessionId);
}

void AlljoynLocalObject::removeSubscriber(ajn::SessionId sessionId)
{
    subscribers_.erase(std::remove(subscribers_.begin(),
                                   subscribers_.end(),
                                   sessionId), subscribers_.end());
}

void AlljoynLocalObject::ObjectRegistered()
{
    BusObject::ObjectRegistered();
    cout << format("ObjectRegistered has been called.(%1%)\n")
                   % ajnServicePath_; // debug
}

}
