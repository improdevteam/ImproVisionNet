#ifndef IMPRO_PRIVATE_ALLJOYNLOCALLISTENER_HPP
#define IMPRO_PRIVATE_ALLJOYNLOCALLISTENER_HPP

// alljoyn
#include <alljoyn/AllJoynStd.h>
#include <alljoyn/BusAttachment.h>

// impro
#include <impro/defines.hpp>

namespace impro
{
    class AlljoynLocalObject;

    /**
     * @brief The AlljoynListener class
     */
    class IMPRO_EXPORTS AlljoynLocalListener : public ajn::SessionPortListener,
                                          public ajn::SessionListener
    {
    public:
        /**
         * @brief AlljoynListener
         * @param object
         */
        AlljoynLocalListener(AlljoynLocalObject &object);

        /**
         * @brief AcceptSessionJoiner (SessionPortListener)
         * @param sessionPort
         * @param joiner
         * @param opts
         * @return
         */
        bool AcceptSessionJoiner(ajn::SessionPort sessionPort,
                                 const char *joiner,
                                 const ajn::SessionOpts &opts);

        /**
         * @brief SessionJoined (SessionPortListener)
         * @param sessionPort
         * @param sessionId
         * @param joiner
         */
        void SessionJoined(ajn::SessionPort sessionPort,
                           ajn::SessionId sessionId,
                           const char *joiner);

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
        AlljoynLocalObject &object_;
    };
}

#endif // IMPRO_PRIVATE_ALLJOYNLOCALLISTENER_HPP
