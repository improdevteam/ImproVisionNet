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
        virtual void dataReceived(Channel &channel) = 0;
    };

}

#endif // IMPRO_CHANNELOBSERVER_HPP
