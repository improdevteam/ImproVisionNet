#ifndef IMPRO_PRIVATE_ALLJOYNREMOTEOBJECT_HPP
#define IMPRO_PRIVATE_ALLJOYNREMOTEOBJECT_HPP

// std
#include <string>
#include <map>

// alljoyn
#include <alljoyn/AllJoynStd.h>

// impro
#include <impro/defines.hpp>

namespace impro
{
    class Space;
    class AlljoynRemoteListener;

    /**
     * @brief The AlljoynRemoteObject class
     */
    class IMPRO_EXPORTS AlljoynRemoteObject
    {
    public:
        /**
         * @brief AlljoynRemoteObject
         * @param ajnServiceName
         * @param ajnServicePath
         * @param sessionPort
         * @param transportMask
         * @param sessionId
         * @param bus
         */
        AlljoynRemoteObject(const std::string &ajnServiceName,
                            const std::string &ajnServicePath,
                            ajn::SessionPort sessionPort,
                            ajn::TransportMask transportMask,
                            ajn::SessionId sessionId,
                            ajn::BusAttachment &bus);

        /**
         * @brief ~AlljoynRemoteObject
         */
        virtual ~AlljoynRemoteObject();

        /**
         * @brief getAlljoynBusAttachment
         * @return
         */
        virtual ajn::BusAttachment& getAlljoynBusAttachment() { return bus_; }

        /**
         * @brief getAlljoynServiceName
         * @return
         */
        std::string getAlljoynServiceName() { return ajnServiceName_; }

        /**
         * @brief getAlljoynServicePath
         * @return
         */
        std::string getAlljoynServicePath() { return ajnServicePath_; }

        /**
         * @brief getAlljoynTransportMask
         * @return
         */
        ajn::TransportMask getAlljoynTransportMask() { return ajnTransportMask_; }

        /**
         * @brief getAlljoynSessionPort
         * @return
         */
        ajn::SessionPort getAlljoynSessionPort() { return ajnSessionPort_; }

        /**
         * @brief setAlljoynSessionId
         * @param sessionId
         */
        void setAlljoynSessionId(ajn::SessionId sessionId) { ajnSessionId_ =  sessionId; }

        /**
         * @brief getAlljoynSessionId
         * @return
         */
        ajn::SessionId getAlljoynSessionId() { return ajnSessionId_; }

        /**
         * @brief getListener
         * @return
         */
        AlljoynRemoteListener& getListener() { return *listener_ ;}

    protected:
        std::string ajnServiceName_;
        std::string ajnServicePath_;
        ajn::SessionPort ajnSessionPort_;
        ajn::TransportMask ajnTransportMask_;
        ajn::SessionId ajnSessionId_;
        ajn::BusAttachment &bus_;
        AlljoynRemoteListener *listener_;
    };

    typedef std::map<std::string, AlljoynRemoteObject*> AlljoynRemoteObjectSet;

}

#endif // IMPRO_PRIVATE_ALLJOYNREMOTEOBJECT_HPP
