//boost
#include <boost/foreach.hpp>

// impro
#include <impro/spacebuilder.hpp>

using namespace std;
using namespace boost;

namespace impro
{

SpaceBuilderMap SpaceBuilder::Builders_;

void SpaceBuilder::Prepare(const std::string &type,
                              SpaceBuilder &builder)
{
    if(Builders_.find(type) == Builders_.end())
    {
        SpaceBuilder *spaceBuilder = builder.newPtr();
        spaceBuilder->prepare();
        Builders_.insert(SpaceBuilderMap::value_type(type, spaceBuilder));
    }
}

void SpaceBuilder::Release()
{
    BOOST_FOREACH(SpaceBuilderMap::value_type &item, Builders_)
    {
        item.second->release();
        delete item.second;
    }
    Builders_.clear();
}


}
