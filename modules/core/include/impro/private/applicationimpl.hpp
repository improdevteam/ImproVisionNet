#ifndef IMPRO_PRIVATE_APPLICATIONIMPL_HPP
#define IMPRO_PRIVATE_APPLICATIONIMPL_HPP

// std
#include <map>

// boost
#include <boost/thread.hpp>

// impro
#include <impro/application.hpp>

namespace impro
{
    class Space;

    typedef std::map<std::string, Process*> ProcessMap;
    typedef std::map<std::string, boost::thread*> ProcessThreadMap;

    typedef std::map<std::string, Space*> SpaceMap;

    /**
     * @brief The Impro Application class
     */
    class IMPRO_EXPORTS ApplicationImpl : public Application
    {
    public:
        /**
         * @brief ~ApplicationImpl
         */
        virtual ~ApplicationImpl();

        // Process
        /**
         * @brief create process and store inside application
         * @param id process id
         * @param creator Process Creator
         * @return process
         */
        virtual Process& createProcess(const std::string &id,
                                       const std::string &dir,
                                       ProcessCreator &creator);

        /**
         * @brief hasProcess
         * @param id process id
         * @return true if process exist, else return false
         */
        virtual bool hasProcess(const std::string &id);

        /**
         * @brief getProcess
         * @param id process id
         * @return process
         */
        virtual Process& getProcess(const std::string &id);

        /**
         * @brief create a thread to run specific process
         * @param id process id
         * @param block if true wait process complete
         */
        virtual void activate(const std::string &id,
                              bool block);

        /**
         * @brief run all process inside application in parallel
         * @param block if true wait process complete
         */
        virtual void activate(bool block);

        /**
         * @brief stop running specific process
         * @param id process id
         */
        virtual void deactivate(const std::string &id);

        /**
         * @brief stop all process inside application
         */
        virtual void deactivate();

        // Space

        /**
         * @brief joinSpace
         * @param spaceType
         * @param id
         * @param config
         */
        virtual int joinSpace(const std::string &spaceType,
                              const std::string &spaceId,
                              const std::string &nodeId,
                              const std::string &dir);

        /**
         * @brief getSpace
         * @param spaceId
         * @return
         */
        virtual Space& getSpace(const std::string &spaceId);

    protected:
        boost::thread_group threads_;
        ProcessMap processes_;
        ProcessThreadMap processThreads_;
        SpaceMap spaces_;
    };
}

#endif // IMPRO_PRIVATE_APPLICATIONIMPL_HPP
