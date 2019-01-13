// impro
#include <impro/private/interface/alljoynfield.hpp>
#include <impro/interface/alljoynfieldcreator.hpp>

namespace impro { namespace iface
{

InterfaceCreator* AlljoynRemoteFieldCreator::newPtr()
{
    return new AlljoynRemoteFieldCreator();
}

Interface* AlljoynRemoteFieldCreator::create(Node &node)
{
    return new AlljoynRemoteField(IMPRO_INTERFACE_ALLJOYNREMOTEFIELD, node);
}

} }
