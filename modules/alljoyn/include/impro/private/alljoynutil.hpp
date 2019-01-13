#ifndef IMPRO_PRIVATE_ALLJOYNUTIL_HPP
#define IMPRO_PRIVATE_ALLJOYNUTIL_HPP

// std
#include <string>

// alljoyn
#include <alljoyn/AllJoynStd.h>

// impro
#include <impro/defines.hpp>

namespace impro
{
    namespace AlljoynUtil
    {
        extern const ajn::SessionPort NODE_SESSION_PORT;

        extern const std::string NODE_INTERFACE;

        extern const std::string NODE_PREFIX;

        extern const std::string CHANNEL_INTERFACE;

        extern const std::string CHANNEL_PREFIX;

        extern const std::string SERVICE_INTERFACE;

        extern const std::string SERVICE_PREFIX;

        /**
         * @brief NodeServiceName
         * @param nodeId
         * @return
         */
        std::string NodeServiceName(const std::string &nodeId);

        /**
         * @brief NodeServicePath
         * @param nodeId
         * @return
         */
        std::string NodeServicePath(const std::string &nodeId);

        /**
         * @brief NodeFromServiceName
         * @param nodeServiceName
         * @return
         */
        std::string NodeFromServiceName(const std::string &nodeServiceName);

        /**
         * @brief NodeFromServicePath
         * @param nodeServicePath
         * @return
         */
        std::string NodeFromServicePath(const std::string &nodeServicePath);

        /**
         * @brief ChannelServicePrefix CHANNEL_PREFIX.channelId
         * @param channelId
         * @return
         */
        std::string ChannelServicePrefix(const std::string &channelId);

        /**
         * @brief ChannelServiceName CHANNEL_PREFIX.channelId.nodeId.pport.dataType
         * @param nodeId
         * @param channelId
         * @param port
         * @param dataType
         * @return
         */
        std::string ChannelServiceName(const std::string &nodeId,
                                       const std::string &channelId,
                                       ajn::SessionPort   port,
                                       const std::string &dataType);
        /**
         * @brief ChannelServicePath  /nodeId/channelId
         * @param nodeId
         * @param channelId
         * @return
         */
        std::string ChannelServicePath(const std::string &nodeId,
                                       const std::string &channelId);

        /**
         * @brief ChannelFromServiceName
         * @param channelServiceName
         * @param nodeId
         * @param channelId
         * @param port
         * @param dataType
         */
        void ChannelFromServiceName(const std::string &channelServiceName,
                                    std::string &nodeId,
                                    std::string &channelId,
                                    ajn::SessionPort &port,
                                    std::string &dataType);

        /**
         * @brief ChannelFromServicePath
         * @param channelServicePath
         * @param nodeId
         * @param channelId
         */
        void ChannelFromServicePath(const std::string &channelServicePath,
                                    std::string &nodeId,
                                    std::string &channelId);

        /**
         * @brief ServicePrefix  prefix.Id
         * @param prefix
         * @param Id
         * @return
         */
        std::string ServicePrefix(const std::string &prefix,
                                  const std::string &Id);

        /**
         * @brief ServiceName
         * @param prefix
         * @param nodeId
         * @param Id
         * @param port
         * @return
         */
        std::string ServiceName(const std::string &prefix,
                                const std::string &nodeId,
                                const std::string &Id,
                                ajn::SessionPort   port); // prefix.Id.nodeId.pport
        /**
         * @brief ServicePath
         * @param nodeId
         * @param Id
         * @return
         */
        std::string ServicePath(const std::string &nodeId,
                                const std::string &Id); // /nodeId/Id
        /**
         * @brief FromServiceName
         * @param prefix
         * @param serviceName
         * @param nodeId
         * @param Id
         * @param port
         */
        void FromServiceName(const std::string &prefix,
                             const std::string &serviceName,
                             std::string &nodeId,
                             std::string &Id,
                             ajn::SessionPort &port);
        /**
         * @brief FromServicePath
         * @param servicePath
         * @param nodeId
         * @param Id
         */
        void FromServicePath(const std::string &servicePath,
                             std::string &nodeId,
                             std::string &Id);
        /**
         * @brief CreateNodeInterface
         * @param bus
         */
        void CreateNodeInterface(ajn::BusAttachment &bus);

        /**
         * @brief CreateOutputChannelInterface
         * @param bus
         */
        void CreateOutputChannelInterface(ajn::BusAttachment &bus);

    }
}

#endif // IMPRO_PRIVATE_ALLJOYNUTIL_HPP
