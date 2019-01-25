// impro
#include <impro/spacebuilder.hpp>

using namespace std;

namespace impro
{

SpaceBuilderMap SpaceBuilder::Builders_;

void SpaceBuilder::Prepare(const std::string &type,
                              SpaceBuilder &&builder)
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
    for(auto &item : Builders_)
    {
        item.second->release();
        delete item.second;
    }
    Builders_.clear();
}


}
