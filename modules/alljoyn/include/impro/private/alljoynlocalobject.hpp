#ifndef IMPRO_PRIVATE_ALLJOYNOBJECT_HPP
#define IMPRO_PRIVATE_ALLJOYNOBJECT_HPP

// std
#include <vector>

// alljoyn
#include <alljoyn/AllJoynStd.h>
#include <alljoyn/BusObject.h>

// impro
#include <impro/defines.hpp>

namespace impro
{
    class AlljoynLocalListener;

    /**
     * @brief The AlljoynObject class
     */
    class IMPRO_EXPORTS AlljoynLocalObject : public ajn::BusObject
    {
    public:
        /**
         * @brief AlljoynObject
         * @param ajnServicePath
         * @param ajnBus
         */
        AlljoynLocalObject(std::string ajnServicePath,
                           ajn::BusAttachment &ajnBus);

        /**
         * @brief ~AlljoynObject
         */
        virtual ~AlljoynLocalObject();

        /**
         * @brief advertise
         */
        void advertise();

        /**
         * @brief addSubscriber
         * @param sessionId
         */
        void addSubscriber(ajn::SessionId sessionId);

        /**
         * @brief removeSubscriber
         * @param sessionId
         */
        void removeSubscriber(ajn::SessionId sessionId);

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
         * @brief getAlljoynSessionPort
         * @return
         */
        ajn::SessionPort getAlljoynSessionPort() { return ajnSessionPort_; }

        /**
         * @brief getAlljoynBusAttachment
         * @return
         */
        ajn::BusAttachment& getAlljoynBusAttachment() { return *bus; }

    protected:
        /**
         * @brief ObjectRegistered (BusObject)
         */
        void ObjectRegistered();

    protected:
        std::string ajnServiceName_;
        std::string ajnServicePath_;
        ajn::SessionPort ajnSessionPort_;
        AlljoynLocalListener *listener_;
        std::vector<ajn::SessionId> subscribers_;
    };
}

#endif // IMPRO_PRIVATE_ALLJOYNOBJECT_HPP
