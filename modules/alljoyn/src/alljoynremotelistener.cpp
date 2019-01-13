// boost
#include <boost/format.hpp>

// impro
#include <impro/private/alljoynremoteobject.hpp>
#include <impro/private/alljoynremotelistener.hpp>

using namespace std;
using namespace boost;
using namespace ajn;

/*
 * class AlljoynRemoteListener
 */
namespace impro
{

AlljoynRemoteListener::AlljoynRemoteListener(AlljoynRemoteObject &object)
    : object_(object)
{
}


// SessionListener --------------------------------------------------
void AlljoynRemoteListener::SessionLost(ajn::SessionId sessionId,
                                        SessionLostReason reason)
{
    cerr << format("SessionLost(%1%) (id=%2%).\n")
                   % object_.getAlljoynServiceName()
                   % sessionId; // debug

}

void AlljoynRemoteListener::SessionMemberAdded(SessionId sessionId,
                                               const char *uniqueName)
{
    cerr << format("SessionMemberAdded(%1%) (id=%2%, uniqueName=%3%).\n")
                   % object_.getAlljoynServiceName()
                   % sessionId
                   % uniqueName; // debug
}

void AlljoynRemoteListener::SessionMemberRemoved(ajn::SessionId sessionId,
                                                 const char *uniqueName)
{
    cerr << format("SessionMemberRemoved(%1%) (id=%2%, uniqueName=%3%).\n")
                   % object_.getAlljoynServiceName()
                   % sessionId
                   % uniqueName; // debug
}

}
