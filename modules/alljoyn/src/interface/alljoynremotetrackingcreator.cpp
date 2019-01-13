// impro
#include <impro/private/interface/alljoyntracking.hpp>
#include <impro/interface/alljoyntrackingcreator.hpp>

namespace impro { namespace iface
{

InterfaceCreator* AlljoynRemoteTrackingCreator::newPtr()
{
    return new AlljoynRemoteTrackingCreator();
}

Interface* AlljoynRemoteTrackingCreator::create(Node &node)
{
    return new AlljoynRemoteTracking(IMPRO_INTERFACE_ALLJOYNREMOTETRACKING, node);
}

} }
