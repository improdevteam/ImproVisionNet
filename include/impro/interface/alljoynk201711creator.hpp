#ifndef IMPRO_INTERFACE_ALLJOYNK201711_HPP
#define IMPRO_INTERFACE_ALLJOYNK201711_HPP

// std
#include <vector>

// impro
#include <impro/interfacecreator.hpp>

#define IMPRO_INTERFACE_ALLJOYNREMOTEK201711 "alljoynremotek201711"

namespace impro
{
    namespace iface
    {
        class IMPRO_EXPORTS AlljoynK201711Creator : public InterfaceCreator
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

#endif // IMPRO_INTERFACE_ALLJOYNK201711_HPP
