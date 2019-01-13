#ifndef IMPRO_PRIVATE_ALLJOYNSPACE_HPP
#define IMPRO_PRIVATE_ALLJOYNSPACE_HPP

// std
#include <map>

// alljoyn
#include <alljoyn/AllJoynStd.h>
#include <alljoyn/BusAttachment.h>

// impro
#include <impro/space.hpp>

namespace impro
{
    class AlljoynRemoteNode;

    typedef std::map<std::string, AlljoynRemoteNode*> RemoteNodeMap;

    /**
     * @brief The AlljoynSpace class
     */
    class IMPRO_EXPORTS AlljoynSpace : public Space,
                                       public ajn::BusListener,
                                       public ajn::SessionListener
    {
    public:
        /**
         * @brief AlljoynSpace
         * @param spaceId
         * @param nodeId
         * @param config
         */
        AlljoynSpace(const std::string &spaceId,
                     const std::string &nodeId,
                     const std::string &dir);

        /**
         * @brief ~AlljoynSpace
         */
        virtual ~AlljoynSpace();

        /**
         * @brief hasRemoteNode
         * @param nodeId
         * @return
         */
        virtual bool hasRemoteNode(const std::string &nodeId);

        /**
         * @brief getRemoteNode
         * @param nodeId
         * @return
         */
        virtual RemoteNode& getRemoteNode(const std::string &nodeId);

        /**
         * @brief getBus
         * @return
         */
        ajn::BusAttachment& getBus() { return *bus_; }

    public:
        /**
         * @brief FoundAdvertisedName (BusListener)
         * @param name
         * @param transport
         * @param namePrefix
         */
        void FoundAdvertisedName(const char *name,
                                 ajn::TransportMask transport,
                                 const char *namePrefix);

        /**
         * @brief SessionLost (SessionListener)
         * @param sessionId
         * @param reason
         */
        void SessionLost(ajn::SessionId sessionId,
                         ajn::SessionListener::SessionLostReason reason);

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
        void addRemoteNode(const std::string &nodeId,
                           ajn::TransportMask transportMask,
                           ajn::SessionId sessionId);

        void removeRemoteNode(ajn::SessionId sessionId);

    private:
        ajn::BusAttachment *bus_;
        RemoteNodeMap remoteNodes_;
    };
}

#endif // IMPRO_PRIVATE_ALLJOYNSPACE_HPP
