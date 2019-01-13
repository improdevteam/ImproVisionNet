#ifndef IMPRO_PRIVATE_ALLJOYNLOCALCHANNEL_HPP
#define IMPRO_PRIVATE_ALLJOYNLOCALCHANNEL_HPP

// std
#include <vector>

// impro
#include <impro/channel.hpp>
#include <impro/private/alljoynlocalobject.hpp>

namespace impro
{
    /**
     * @brief The AlljoynLocalChannel class
     */
    class IMPRO_EXPORTS AlljoynLocalChannel : public LocalChannel,
                                              public AlljoynLocalObject
    {
    public:
        /**
         * @brief AlljoynOutputChannel
         * @param dataType
         * @param id
         * @param limit
         * @param node
         */
        AlljoynLocalChannel(const std::string &dataType,
                             const std::string &id,
                             unsigned int limit,
                             Node &node);

        /**
         * @brief ~AlljoynLocalChannel
         */
        virtual ~AlljoynLocalChannel();


        /**
         * @brief write
         * @param dataId
         * @param data
         */
        virtual void write(const std::string &dataId,
                           Data &data);

        /**
         * @brief write
         * @param dataId
         * @param raw
         */
        virtual void write(const std::string &dataId,
                           std::vector<uchar> &raw);

    private:
        const ajn::InterfaceDescription::Member *TransferData;
        const ajn::InterfaceDescription::Member *DataIsReady;
    };
}

#endif // IMPRO_PRIVATE_ALLJOYNLOCALCHANNEL_HPP
