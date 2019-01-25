#ifndef IMPRO_APPLICATION_HPP
#define IMPRO_APPLICATION_HPP

// std
#include <string>

// impro
#include <impro/defines.hpp>

namespace impro
{
    class ProcessCreator;
    class Process;
    class Space;

    /**
     * @brief The Impro Application class
     */
    class IMPRO_EXPORTS Application
    {
    public:
        static Application& Initialize();

        static void Finalize();

        static Application& getInstance();

        static void releaseInstance();

    public:
        /**
         * @brief Application is not copyable
         */
        Application( const Application & ) = delete;

        /**
         * @brief Application is not copyable
         */
        Application& operator=(const Application& other)  = delete;

        /**
         * @brief ~Application
         */
        virtual ~Application() {}

        // Process
        /**
         * @brief create process and store inside application
         * @param id process id
		 * @param creator Process Creator
         * @return process id
         */
        virtual Process&  createProcess(const std::string &id,
                                        const std::string &dir,
                                        ProcessCreator &creator) = 0;

        /**
         * @brief hasProcess
         * @param id process id
         * @return true if process exist, else return false
         */
        virtual bool hasProcess(const std::string &id) = 0;

        /**
         * @brief getProcess
         * @param id process id
         * @return process
         */
        virtual Process& getProcess(const std::string &id) = 0;

        /**
         * @brief create a thread to run specific process
         * @param id process id
         * @param block if true wait process complete
         */
        virtual void activate(const std::string &id,
                              bool block) = 0;

        /**
         * @brief run all process inside application in parallel
         * @param block if true wait process complete
         */
        virtual void activate(bool block) = 0;

        /**
         * @brief stop running specific process
         * @param id process id
         */
        virtual void deactivate(const std::string &id) = 0;

        /**
         * @brief stop all process inside application
         */
        virtual void deactivate() = 0;

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
                              const std::string &dir) = 0;

        /**
         * @brief getSpace
         * @param spaceId
         * @return
         */
        virtual Space& getSpace(const std::string &spaceId) = 0;

    protected:
        Application() {}




    };
}


#endif // IMPRO_APPLICATION_HPP
