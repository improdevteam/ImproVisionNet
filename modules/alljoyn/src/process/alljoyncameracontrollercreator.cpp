// std
#include <iostream> // debug

// impro
#include <impro/process/alljoyncameracontrollercreator.hpp>
#include <impro/private/process/alljoyncameracontroller.hpp>
#include <impro/application.hpp>
#include <impro/space.hpp>
#include <impro/private/alljoynspace.hpp>
#include <impro/private/alljoynlocalnode.hpp>

using namespace std;

namespace impro { namespace process
{

AlljoynCameraControllerCreator::AlljoynCameraControllerCreator(const string &spaceId)
    : spaceId_(spaceId)
{
}

Process* AlljoynCameraControllerCreator::create(const string &id,
                                                const string &dir,
                                                Application &app)
{
    Space &space = app.getSpace(spaceId_);
    AlljoynLocalNode &localNode = dynamic_cast<AlljoynLocalNode&>(space.getLocalNode());
    string ajnServicePath = localNode.getAlljoynServicePath() + "/controller";
    return new AlljoynCameraController(id, dir, app, space, ajnServicePath);
}


} }
