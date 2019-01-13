// std
#include <iostream>

// boost
#include <boost/filesystem.hpp>

// impro
#include <impro/space.hpp>
#include <impro/node.hpp>

using namespace std;
using namespace boost;

namespace impro
{

Space::Space(const std::string &id,
             const std::string &dir)
    : id_(id), dir_(dir), node_(NULL)
{
    filesystem::path d(dir_);
    if(!filesystem::exists(d))
        filesystem::create_directories(d);
}

Space::~Space()
{
    if(node_ != NULL)
    {
        delete node_;
        node_ = NULL;
    }
}

}
