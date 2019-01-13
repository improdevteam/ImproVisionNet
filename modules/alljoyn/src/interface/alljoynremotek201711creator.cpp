// impro
#include <impro/private/interface/alljoynk201711.hpp>
#include <impro/interface/alljoynk201711creator.hpp>

namespace impro { namespace iface
{

InterfaceCreator* AlljoynK201711Creator::newPtr()
{
    return new AlljoynK201711Creator();
}

Interface* AlljoynK201711Creator::create(Node &node)
{
    return new AlljoynRemoteK201711(IMPRO_INTERFACE_ALLJOYNREMOTEK201711, node);
}

} }
