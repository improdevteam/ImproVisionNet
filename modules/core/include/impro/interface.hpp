#ifndef IMPRO_INTERFACE_HPP
#define IMPRO_INTERFACE_HPP

// std
#include <string>

// impro
#include <impro/defines.hpp>

namespace impro
{
    class Node;

    class IMPRO_EXPORTS Interface
    {
    public:
        /**
         * @brief ~Interface
         */
        virtual ~Interface() {}

    protected:
        /**
         * @brief Interface
         * @param type
         * @param node
         */
        Interface(const std::string &type,
                  Node &node)
            : type_(type), node_(node) {}

    protected:
        std::string type_;
        Node &node_;
    };
}

#endif // IMPRO_INTERFACE_HPP
