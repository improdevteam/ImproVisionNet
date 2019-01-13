// impro
#include <impro/private/interface/alljoyntriangulation.hpp>
#include <impro/interface/alljoyntriangulationcreator.hpp>

namespace impro { namespace iface
{

InterfaceCreator* AlljoynRemoteTriangulationCreator::newPtr()
{
    return new AlljoynRemoteTriangulationCreator();
}

Interface* AlljoynRemoteTriangulationCreator::create(Node &node)
{
    return new AlljoynRemoteTriangulation(IMPRO_INTERFACE_ALLJOYNREMOTETRIANGULATION, node);
}

} }
