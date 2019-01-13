//boost
#include <boost/foreach.hpp>

// impro
#include <impro/interfacecreator.hpp>

using namespace std;
using namespace boost;

namespace impro
{

InterfaceCreatorMap InterfaceCreator::Creators_;

void InterfaceCreator::Prepare(const std::string &type,
                               InterfaceCreator  &creator)
{
    if(Creators_.find(type) == Creators_.end())
    {
        InterfaceCreator *interfaceCreator = creator.newPtr();
        Creators_.insert(InterfaceCreatorMap::value_type(type, interfaceCreator));
    }
}

void InterfaceCreator::Release()
{
    BOOST_FOREACH(InterfaceCreatorMap::value_type &item, Creators_)
    {
        delete item.second;
    }
    Creators_.clear();
}


}
