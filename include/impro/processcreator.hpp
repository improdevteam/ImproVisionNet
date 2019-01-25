#ifndef IMPRO_PROCESSCREATOR_HPP
#define IMPRO_PROCESSCREATOR_HPP

// std
#include <string>

// impro
#include <impro/defines.hpp>

namespace impro
{
    class Application;
    class Process;

    /**
     * @brief The IMPRO ProcessCreator class
     */
    class IMPRO_EXPORTS ProcessCreator
    {
    public:
        /**
         * @brief Constructor
         */
        ProcessCreator() {}

        /**
         * @brief ProcessCreator is not copyable
         */
        ProcessCreator( const ProcessCreator & ) = delete;

        /**
         * @brief Process is not copyable
         */
        ProcessCreator& operator=(const ProcessCreator& other)  = delete;

        /**
         * @brief ~Process
         */
        virtual ~ProcessCreator() {}

        /**
         * @brief create process
         * @param id process id
         * @param node
         * @return
         */
        virtual Process* create(const std::string &id,
                                const std::string &dir,
                                Application &app) = 0;

    };
}


#endif // IMPRO_PROCESSCREATOR_HPP
