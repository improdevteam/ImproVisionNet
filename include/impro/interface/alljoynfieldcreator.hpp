#ifndef IMPRO_INTERFACE_ALLJOYNSTRAINFIELDCREATOR_HPP
#define IMPRO_INTERFACE_ALLJOYNSTRAINFIELDCREATOR_HPP

// std
#include <vector>

// impro
#include <impro/interfacecreator.hpp>

#define IMPRO_INTERFACE_ALLJOYNREMOTEFIELD "alljoynremotefield"

namespace impro
{
    namespace iface
    {
        class IMPRO_EXPORTS AlljoynRemoteFieldCreator : public InterfaceCreator
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

#endif // IMPRO_INTERFACE_ALLJOYNSTRAINFIELDCREATOR_HPP
