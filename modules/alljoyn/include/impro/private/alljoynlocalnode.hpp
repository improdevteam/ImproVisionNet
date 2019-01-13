#ifndef IMPRO_PRIVATE_ALLJOYNLOCALNODE_HPP
#define IMPRO_PRIVATE_ALLJOYNLOCALNODE_HPP

// std
#include <map>

// impro
#include <impro/private/alljoynlocalobject.hpp>
#include <impro/node.hpp>


namespace impro
{
    class AlljoynLocalChannel;

    typedef std::map<std::string, AlljoynLocalChannel*> LocalChannelMap;


    /**
     * @brief The AlljoynLocalNode class
     */
    class AlljoynLocalNode : public LocalNode,
                             public AlljoynLocalObject
    {
    public:
        /**
         * @brief AlljoynLocalNode
         * @param id
         * @param space
         */
        AlljoynLocalNode(const std::string &id,
                         Space &space);

        /**
         * @brief ~AlljoynLocalNode
         */
        virtual ~AlljoynLocalNode();

        /**
         * @brief registerChannel
         * @param dataType         *
         * @param channelId
         * @param limit
         * @return
         */
        virtual LocalChannel& registerChannel(const std::string &dataType,
                                               const std::string &channelId,
                                               unsigned int limit = std::numeric_limits<unsigned int>::max());

        /**
         * @brief getChannel
         * @param channelId
         * @return
         */
        virtual LocalChannel& getChannel(const std::string &channelId);


        /**
         * @brief hasChannel
         * @param channelId
         * @return
         */
        virtual bool hasChannel(const std::string &channelId);

    private:
        LocalChannelMap channels_;
    };
}

#endif // IMPRO_PRIVATE_ALLJOYNLOCALNODE_HPP
