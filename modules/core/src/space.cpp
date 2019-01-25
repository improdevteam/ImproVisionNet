// std
#include <filesystem>

// impro
#include <impro/space.hpp>
#include <impro/node.hpp>

using namespace std;

namespace impro
{

Space::Space(const string &id,
             const string &dir)
    : id_(id), dir_(dir), node_(nullptr)
{
    filesystem::path d(dir_);
    if(!filesystem::exists(d))
        filesystem::create_directories(d);
}

Space::~Space()
{
    if(node_ != nullptr)
    {
        delete node_;
        node_ = nullptr;
    }
}

}
