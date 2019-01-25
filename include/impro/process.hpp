#ifndef IMPRO_PROCESS_HPP
#define IMPRO_PROCESS_HPP

// std
#include <string>

// impro
#include <impro/defines.hpp>

namespace impro
{
    class Application;

    /**
     * @brief The IMPRO Process class
     */
    class IMPRO_EXPORTS Process
    {
    public:
        enum Status
        {
            stopped = 0,
            running,
            stopping,
        };

    public:
        Process(const std::string &id,
                const std::string &dir,
                Application &app)
            : status_(stopped), id_(id), dir_(dir), app_(app) {}

        /**
         * @brief Process is not copyable
         */
        Process( const Process & ) = delete;

        /**
         * @brief Process is not copyable
         */
        Process& operator=(const Process& other)  = delete;

        /**
         * @brief ~Process
         */
        virtual ~Process() {}

        /**
         * @brief run process
         */
        virtual void run() = 0;

        /**
         * @brief interrupt process
         */
        virtual void interrupt() = 0;

        /**
         * @brief get process id
         * @return process id
         */
        std::string getId() { return id_; }

        /**
         * @brief get process status
         * @return status
         */
        Status getStatus() { return status_; }

    protected:
        Status       status_;
        std::string  id_;
        std::string  dir_;
        Application &app_;
    };
}

#endif // IMPRO_PROCESS_HPP
