// impro
#include <impro/private/interface/alljoyncamera.hpp>
#include <impro/interface/alljoyncameracreator.hpp>

namespace impro { namespace iface
{

InterfaceCreator* AlljoynRemoteCameraCreator::newPtr()
{
    return new AlljoynRemoteCameraCreator();
}

Interface* AlljoynRemoteCameraCreator::create(Node &node)
{
    return new AlljoynRemoteCamera(IMPRO_INTERFACE_ALLJOYNREMOTECAMERA, node);
}

} }
