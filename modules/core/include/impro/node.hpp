#ifndef IMPRO_NODE_HPP
#define IMPRO_NODE_HPP

// std
#include <string>
#include <vector>
#include <map>

// impro
#include <impro/defines.hpp>

namespace impro
{
    class Space;
    class RemoteChannel;
    class LocalChannel;
    class Interface;

    typedef std::map<std::string, Interface*> InterfaceMap;


    class IMPRO_EXPORTS Node
    {
    public:
        /**
         * @brief Node is not copyable
         */
        Node( const Node & ) = delete;

        /**
         * @brief Node is not copyable
         */
        Node& operator=(const Node& other)  = delete;

        /**
         * @brief ~Node
         */
        virtual ~Node() {}

        /**
         * @brief getId
         * @return
         */
        std::string getId() { return id_; }

        /**
         * @brief getDir
         * @return
         */
        std::string getDir() { return dir_; }

        /**
         * @brief getSpace
         * @return
         */
        Space& getSpace() { return space_; }

    protected:
        /**
         * @brief Node
         * @param id
         * @param space
         */
        Node(const std::string &id,
             Space &space);

    protected:
        std::string id_;
        std::string dir_;
        Space &space_;
    };

    /**
     * @brief The LocalNode class
     */
    class IMPRO_EXPORTS LocalNode : public Node
    {
    public:
        /**
         * @brief LocalNode
         * @param id
         * @param space
         */
        LocalNode(const std::string &id,
                  Space &space);

        /**
         * @brief ~LocalNode
         */
        virtual ~LocalNode();

        /**
         * @brief registerChannel
         * @param id
         * @param dataType
         * @param limit
         * @return
         */
        virtual LocalChannel& registerChannel(const std::string &dataType,
                                              const std::string &channelId,
                                              unsigned int limit = std::numeric_limits<unsigned int>::max()) = 0;

        /**
         * @brief getChannel
         * @param channelId
         * @return
         */
        virtual LocalChannel& getChannel(const std::string &channelId) = 0;

        /**
         * @brief hasChannel
         * @param channelId
         * @return
         */
        virtual bool hasChannel(const std::string &channelId) = 0;
   };

    class IMPRO_EXPORTS RemoteNode : public Node
    {
    public:
        /**
         * @brief RemoteNode
         * @param id
         * @param space
         */
        RemoteNode(const std::string &id,
                   Space &space);

        /**
         * @brief ~RemoteNode
         */
        virtual ~RemoteNode();

        /**
         * @brief getChannel
         * @param channelId
         * @return
         */
        virtual RemoteChannel& getChannel(const std::string &channelId) = 0;

        /**
         * @brief hasChannel
         * @param channelId
         * @return
         */
        virtual bool hasChannel(const std::string &channelId) = 0;

        // ?? Temporary
        virtual Interface& getInterface(const std::string &type);

    protected:
        InterfaceMap ifaces_;
    };
}


#endif // IMPRO_NODE_HPP
