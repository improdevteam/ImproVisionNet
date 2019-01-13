#ifndef IMPRO_INTERFACECREATOR_HPP
#define IMPRO_INTERFACECREATOR_HPP

// std
#include <string>
#include <map>

// imrpo
#include <impro/defines.hpp>

namespace impro
{
    class InterfaceCreator;
    class Interface;
    class Node;

    typedef std::map<std::string, InterfaceCreator*> InterfaceCreatorMap;

    /**
     * @brief The InterfaceCreator class
     */
    class IMPRO_EXPORTS InterfaceCreator
    {
        friend class RemoteNode;
    public:
        /**
         * @brief Prepare
         * @param type
         * @param builder
         */
        static void Prepare(const std::string &type,
                            InterfaceCreator &creator);

        /**
         * @brief Release
         */
        static void Release();

    private:
        static InterfaceCreatorMap Creators_;

    public:
        /**
         * @brief newPtr
         * @return
         */
        virtual InterfaceCreator* newPtr() = 0;

        /**
         * @brief build
         * @param spaceId
         * @param nodeId
         * @param config
         * @return
         */
        virtual Interface* create(Node &node) = 0;
    };
}

#endif // IMPRO_INTERFACECREATOR_HPP
