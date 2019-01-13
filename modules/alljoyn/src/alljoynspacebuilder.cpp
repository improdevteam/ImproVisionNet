// alljoyn
#include <alljoyn/AllJoynStd.h>
#include <alljoyn/Init.h>
#include <alljoyn/version.h>

// impro
#include <impro/private/alljoynspace.hpp>
#include <impro/alljoynspacebuilder.hpp>


namespace impro
{

bool AlljoynSpaceBuilder::_enableRouter_ = true;

AlljoynSpaceBuilder::AlljoynSpaceBuilder(bool enableRouter)
{
    _enableRouter_ = enableRouter;
}

SpaceBuilder* AlljoynSpaceBuilder::newPtr()
{
    return new AlljoynSpaceBuilder();
}

void AlljoynSpaceBuilder::prepare()
{
    AllJoynInit();
    if(_enableRouter_)
    {
        AllJoynRouterInit();
    }
}

void AlljoynSpaceBuilder::release()
{
    if(_enableRouter_)
    {
        AllJoynRouterShutdown();
    }
    AllJoynShutdown();
}

Space *AlljoynSpaceBuilder::build(const std::string &spaceId,
                                  const std::string &nodeId,
                                  const std::string &dir)
{
    AlljoynSpace *space = new AlljoynSpace(spaceId, nodeId, dir);
    return space;
}

}
