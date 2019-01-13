// std
#include <iostream> // debug

// boost
#include <boost/format.hpp>

// impro
#include <impro/private/alljoynlocalobject.hpp>
#include <impro/private/alljoynlocallistener.hpp>

using namespace std;
using namespace boost;
using namespace ajn;

namespace impro
{

AlljoynLocalListener::AlljoynLocalListener(AlljoynLocalObject &object)
    : object_(object)
{
}

/*
 * Implement Alljoyn method -----------------------------------------------------------------------------
 */
bool AlljoynLocalListener::AcceptSessionJoiner(SessionPort sessionPort,
                                          const char *joiner,
                                          const SessionOpts &opts)
{
    if(sessionPort == object_.getAlljoynSessionPort())
    {
        cerr << format("AcceptSessionJoiner(%1%) (joiner=%2%, opts.proximity=0x%3$x, opts.traffic=0x%4$x, opts.transports=0x%5$x, sessionPort=%6%).\n")
                       % object_.getAlljoynServiceName()
                       % string(joiner)
                       % (unsigned int)opts.proximity
                       % opts.traffic % opts.transports
                       % sessionPort; // debug
        return true;
    }
    else
    {
        return false;
    }

}

void AlljoynLocalListener::SessionJoined(SessionPort sessionPort,
                                    SessionId sessionId,
                                    const char *joiner)
{
    cerr << format("SessionJoined(%1%) (id=%2%, joiner=%3%, sessionPort=%4%).\n")
                   % object_.getAlljoynServiceName()
                   % sessionId
                   % joiner
                   % sessionPort; // debug
    object_.addSubscriber(sessionId);
    BusAttachment &bus = object_.getAlljoynBusAttachment();
    bus.SetSessionListener(sessionId, this);
}

void AlljoynLocalListener::SessionLost(ajn::SessionId sessionId,
                                  SessionLostReason reason)
{
    cerr << format("SessionLost(%1%) (id=%2%).\n")
                   % object_.getAlljoynServiceName()
                   % sessionId; // debug
    object_.removeSubscriber(sessionId);
}

void AlljoynLocalListener::SessionMemberAdded (SessionId sessionId,
                                          const char *uniqueName)
{
    cerr << format("SessionMemberAdded(%1%) (id=%2%, uniqueName=%3%).\n")
                   % object_.getAlljoynServiceName()
                   % sessionId
                   % uniqueName; // debug
}

void AlljoynLocalListener::SessionMemberRemoved(ajn::SessionId sessionId,
                                           const char *uniqueName)
{
    cerr << format("SessionMemberRemoved(%1%) (id=%2%, uniqueName=%3%).\n")
                   % object_.getAlljoynServiceName()
                   % sessionId
                   % uniqueName; // debug
}

}
