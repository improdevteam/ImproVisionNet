#ifndef IMPRO_CHANNELOBSERVER_HPP
#define IMPRO_CHANNELOBSERVER_HPP

// impro
#include <impro/defines.hpp>

namespace impro
{
    class Channel;

    class IMPRO_EXPORTS ChannelObserver
    {
    public:
        /**
         * @brief ChannelObserver
         */
        ChannelObserver() {}

        /**
         * @brief Channel is not copyable
         */
        ChannelObserver( const ChannelObserver & ) = delete;

        /**
         * @brief Channel is not copyable
         */
        ChannelObserver& operator=(const ChannelObserver& other)  = delete;

        /**
         * @brief ~Channel
         */
        virtual ~ChannelObserver() {}

        /**
         * @brief dataReceived
         * @param channel
         */
        virtual void dataReceived(Channel &channel) = 0;
    };

}

#endif // IMPRO_CHANNELOBSERVER_HPP
