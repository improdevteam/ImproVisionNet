#ifndef IMPRO_PRIVATE_ALLJOYNREMOTENODE_HPP
#define IMPRO_PRIVATE_ALLJOYNREMOTENODE_HPP

// impro
#include <impro/private/alljoynremoteobject.hpp>
#include <impro/node.hpp>

namespace impro
{
    class AlljoynRemoteChannel;

    typedef std::map<std::string, AlljoynRemoteChannel*> RemoteChannelMap;

    /**
     * @brief The AlljoynRemoteNode class
     */
    class IMPRO_EXPORTS AlljoynRemoteNode : public RemoteNode,
                                            public AlljoynRemoteObject
    {
    public:
        /**
         * @brief AlljoynRemoteNode
         * @param id
         * @param space
         * @param transportMask
         * @param sessionId
         */
        AlljoynRemoteNode(const std::string &id,
                          Space &space,
                          ajn::TransportMask transportMask,
                          ajn::SessionId sessionId);

        /**
         * @brief ~AlljoynRemoteNode
         */
        virtual ~AlljoynRemoteNode();

        /**
         * @brief getChannel
         * @param channelId
         * @return
         */
        virtual RemoteChannel& getChannel(const std::string &channelId);

        /**
         * @brief hasChannel
         * @param channelId
         * @return
         */
        virtual bool hasChannel(const std::string &channelId);

        /**
         * @brief registerChannel
         * @param dataType
         * @param channleId
         * @param limit
         * @param sessionPort
         * @param transport
         * @param sessionId
         * @return
         */
        RemoteChannel& registerChannel(const std::string &dataType,
                                       const std::string &channelId,
                                       unsigned int limit,
                                       ajn::SessionPort sessionPort,
                                       ajn::TransportMask transport,
                                       ajn::SessionId sessionId);
    private:
        RemoteChannelMap channels_;
    };
}

#endif // IMPRO_PRIVATE_ALLJOYNREMOTENODE_HPP
