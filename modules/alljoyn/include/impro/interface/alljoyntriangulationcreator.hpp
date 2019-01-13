#ifndef IMPRO_INTERFACE_ALLJOYNTRIANGULATIONCREATOR_HPP
#define IMPRO_INTERFACE_ALLJOYNTRIANGULATIONCREATOR_HPP

// std
#include <vector>

// impro
#include <impro/interfacecreator.hpp>

#define IMPRO_INTERFACE_ALLJOYNREMOTETRIANGULATION "alljoynremotetriangulation"

namespace impro
{
    namespace iface
    {
        class IMPRO_EXPORTS AlljoynRemoteTriangulationCreator : public InterfaceCreator
        {
        public:
            /**
             * @brief newPtr
             * @return
             */
            virtual InterfaceCreator* newPtr();

            /**
             * @brief build
             * @param spaceId
             * @param nodeId
             * @param config
             * @return
             */
            virtual Interface* create(Node &node);
        };
    }
}

#endif // IMPRO_INTERFACE_ALLJOYNTRIANGULATIONCREATOR_HPP
