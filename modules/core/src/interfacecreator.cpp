// impro
#include <impro/interfacecreator.hpp>

using namespace std;

namespace impro
{

InterfaceCreatorMap InterfaceCreator::Creators_;

void InterfaceCreator::Prepare(const std::string &type,
                               InterfaceCreator  &&creator)
{
    if(Creators_.find(type) == Creators_.end())
    {
        InterfaceCreator *interfaceCreator = creator.newPtr();
        Creators_.insert(InterfaceCreatorMap::value_type(type, interfaceCreator));
    }
}

void InterfaceCreator::Release()
{
    for(auto &item : Creators_)
    {
        delete item.second;
    }
    Creators_.clear();
}


}
