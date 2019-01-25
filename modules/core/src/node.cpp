// std
#include <filesystem>

// impro
#include <impro/space.hpp>
#include <impro/node.hpp>
#include <impro/interfacecreator.hpp>

using namespace std;

namespace impro
{

// Class Node ------------------------------------------------
Node::Node(const string &id,
           Space &space)
    : id_(id), space_(space)
{
    dir_ = space_.getDir();
    dir_.append("/").append(id);
    filesystem::path d(dir_);
    if(!filesystem::exists(d))
        filesystem::create_directories(d);
}

// Class LocalNode ------------------------------------------------
LocalNode::LocalNode(const std::string &id,
                     Space &space)
    : Node(id, space)
{
}

LocalNode::~LocalNode()
{
}

// Class RemoteNode ------------------------------------------------
RemoteNode::RemoteNode(const std::string &id,
                       Space &space)
    : Node(id, space)
{
}

RemoteNode::~RemoteNode()
{
}

Interface& RemoteNode::getInterface(const std::string &type)
{
    if(ifaces_.find(type) == ifaces_.end())
    {
        InterfaceCreatorMap::iterator iter = InterfaceCreator::Creators_.find(type);
        InterfaceCreator *creator = iter->second;
        Interface *interface = creator->create(*this);
        ifaces_.insert(InterfaceMap::value_type(type, interface));

    }
    return *ifaces_.at(type);
}


}
