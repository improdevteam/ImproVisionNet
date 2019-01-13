#ifndef IMPRO_PRIVATE_ALLJOYNREMOTELISTENER_HPP
#define IMPRO_PRIVATE_ALLJOYNREMOTELISTENER_HPP

// alljoyn
#include <alljoyn/AllJoynStd.h>
#include <alljoyn/SessionListener.h>

// impro
#include <impro/defines.hpp>

namespace impro
{
    class AlljoynRemoteObject;

    /**
     * @brief The AlljoynRemoteListener class
     */
    class IMPRO_EXPORTS AlljoynRemoteListener : public ajn::SessionListener
    {
    public:
        /**
         * @brief AlljoynRemoteListener
         * @param object
         */
        AlljoynRemoteListener(AlljoynRemoteObject &object);

        /**
         * @brief SessionLost (SessionListener)
         * @param sessionId
         * @param reason
         */
        void SessionLost(ajn::SessionId sessionId,
                         SessionLostReason reason);

        /**
         * @brief SessionMemberAdded (SessionListener)
         * @param sessionId
         * @param uniqueName
         */
        void SessionMemberAdded (ajn::SessionId sessionId,
                                 const char *uniqueName);

        /**
         * @brief SessionMemberRemoved (SessionListener)
         * @param sessionId
         * @param uniqueName
         */
        void SessionMemberRemoved(ajn::SessionId sessionId,
                                  const char *uniqueName);

    private:
        AlljoynRemoteObject &object_;

    };
}

#endif // IMPRO_PRIVATE_ALLJOYNREMOTELISTENER_HPP
