#ifndef IMPRO_CHANNEL_HPP
#define IMPRO_CHANNEL_HPP

// std
#include <string>
#include <vector>

// opencv
#include <opencv2/core.hpp>

// impro
#include <impro/defines.hpp>

namespace impro
{
    class ChannelObserver;
    class Node;
    class Data;

    class IMPRO_EXPORTS Channel
    {
    public:
        /**
         * @brief current - important!! You must delete return pointer!!!
         * @return
         */
        virtual Data* current();

        /**
         * @brief prev - important!! You must delete return pointer!!!
         * @param n
         * @return
         */
        virtual Data* prev(unsigned int n = 1);

        /**
         * @brief at - important!! You must delete return pointer!!!
         * @param n
         * @return
         */
        virtual Data* at(unsigned int n);

        /**
         * @brief current
         * @param data
         */
        virtual void current(Data &data);

        /**
         * @brief prev
         * @param n
         * @param data
         * @return
         */
        virtual void prev(Data &data, unsigned int n = 1);

        /**
         * @brief at
         * @param n
         * @param data
         * @return
         */
        virtual void at(Data &data, unsigned int n);


        /**
         * @brief currentDataId
         * @return
         */
        virtual std::string currentDataId();

        /**
         * @brief prevDataId
         * @param n
         * @return
         */
        virtual std::string prevDataId(unsigned int n = 1);

        /**
         * @brief atDataId
         * @param n
         * @return
         */
        virtual std::string atDataId(unsigned int n);


        /**
         * @brief total
         * @return
         */
        virtual unsigned int total();

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

        /**
         * @brief getDataType
         * @return
         */
        std::string getDataType() { return dataType_; }

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
         * @brief getLimit
         * @return
         */
        unsigned int getLimit() { return limit_; }

        /**
         * @brief getNode
         * @return
         */
        Node& getNode() { return node_; }

        /**
         * @brief setLimit
         * @param limit
         */
        void setLimit(unsigned limit);

    protected:
        /**
         * @brief Channel
         * @param dataType
         * @param id
         * @param limit
         * @param node
         */
        Channel(const std::string &dataType,
                const std::string &id,
                unsigned int limit,
                Node &node);


        /**
         * @brief save
         * @param dataId
         * @param data
         */
        virtual void save(const std::string &dataId,
                          Data &data);

        /**
         * @brief save
         * @param dataId
         * @param raw
         */
        virtual void save(const std::string &dataId,
                          std::vector<uchar> &raw);

    protected:
        std::string dataType_;
        std::string id_;
        std::string dir_;
        unsigned int limit_;
        Node &node_;
        unsigned int idx_;
        Data *data_;
        std::vector<std::string> dataIds_;
        std::vector<ChannelObserver*> observers_;
    };


    /**
     * @brief The RemoteChannel class
     */
    class IMPRO_EXPORTS RemoteChannel : public Channel
    {
    public:
        /**
         * @brief ~InputChannel
         */
        virtual ~RemoteChannel();

    protected:
        /**
         * @brief RemoteChannel
         * @param node
         * @param id
         * @param dataType
         * @param limit
         */
        RemoteChannel(const std::string &dataType,
                     const std::string &id,
                     unsigned int limit,
                     Node &node);
    };

    /**
     * @brief The OutputChannel class
     */
    class IMPRO_EXPORTS LocalChannel : public Channel
    {
    public:
        /**
         * @brief ~OutputChannel
         */
        virtual ~LocalChannel();

        /**
         * @brief write
         * @param dataId
         * @param data
         */
        virtual void write(const std::string &dataId,
                           Data &data) = 0;

        /**
         * @brief write
         * @param dataId
         * @param raw
         */
        virtual void write(const std::string &dataId,
                           std::vector<uchar> &raw) = 0;

    protected:
        /**
         * @brief LocalChannel
         * @param node
         * @param id
         * @param dataType
         * @param limit
         */
        LocalChannel(const std::string &dataType,
                      const std::string &id,
                      unsigned int limit,
                      Node &node);
    };
}

#endif // IMPRO_CHANNEL_HPP
