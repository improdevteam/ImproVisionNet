// impro
#include <impro/private/alljoynremoteobject.hpp>
#include <impro/private/alljoynremotelistener.hpp>

using namespace std;
using namespace ajn;

namespace impro
{

AlljoynRemoteObject::AlljoynRemoteObject(const string &ajnServiceName,
                                         const string &ajnServicePath,
                                         SessionPort sessionPort,
                                         TransportMask transportMask,
                                         SessionId sessionId,
                                         BusAttachment &bus)

    : ajnServiceName_(ajnServiceName),
      ajnServicePath_(ajnServicePath),
      ajnSessionPort_(sessionPort),
      ajnTransportMask_(transportMask),
      ajnSessionId_(sessionId),
      bus_(bus)
{
    listener_ = new AlljoynRemoteListener(*this);
}

AlljoynRemoteObject::~AlljoynRemoteObject()
{
    if(listener_)
    {
        delete listener_;
        listener_ = NULL;
    }
}

}
