#ifndef IMPRO_PRIVATE_ALLJOYNREMOTECHANNEL_HPP
#define IMPRO_PRIVATE_ALLJOYNREMOTECHANNEL_HPP

// std
#include <vector>

// boost
#include <boost/timer/timer.hpp>

// alljoyn
#include <alljoyn/BusObject.h>

// impro
#include <impro/channel.hpp>
#include <impro/private/alljoynremoteobject.hpp>


namespace impro
{
    /**
     * @brief The AlljoynRemoteChannel class
     */
    class IMPRO_EXPORTS AlljoynRemoteChannel : public RemoteChannel,
                                               public AlljoynRemoteObject,
                                               public ajn::MessageReceiver
    {
    public:
        /**
         * @brief AlljoynRemoteChannel
         * @param dataType
         * @param id
         * @param limit
         * @param node
         * @param sessionPort
         * @param transport
         * @param sessionId
         */
        AlljoynRemoteChannel(const std::string &dataType,
                             const std::string &id,
                             unsigned int limit,
                             Node &node,
                             ajn::SessionPort sessionPort,
                             ajn::TransportMask transport,
                             ajn::SessionId sessionId);

        /**
         * @brief ~AlljoynRemoteChannel
         */
        virtual ~AlljoynRemoteChannel();


        /**
         * @brief subscribe
         * @param observer
         */
        virtual void subscribe(ChannelObserver *observer);

        /**
         * @brief unsubscribe
         * @param observer
         */
        virtual void unsubscribe(ChannelObserver *observer);

    private: // Handler
        void TransferData(const ajn::InterfaceDescription::Member* member,
                          const char* sourcePath,
                          ajn::Message& msg);

        void DataIsReady(const ajn::InterfaceDescription::Member* member,
                         const char* sourcePath,
                         ajn::Message& msg);

        void TransferFile(const ajn::InterfaceDescription::Member* member,
                          const char* sourcePath,
                          ajn::Message& msg);

        void FileIsReady(const ajn::InterfaceDescription::Member* member,
                         const char* sourcePath,
                         ajn::Message& msg);


    private:
        std::vector<uchar> buffer;

        boost::timer::cpu_timer transferTimer;
    };
}


#endif // IMPRO_PRIVATE_ALLJOYNREMOTECHANNEL_HPP
