// boost
#include <boost/foreach.hpp>

// impro
#include <impro/datatype.hpp>
#include <impro/data.hpp>

namespace impro
{

DataTypeMap DataType::DataTypes_;

void DataType::Prepare(const std::string &type, Data &data)
{
    if(DataTypes_.find(type) == DataTypes_.end())
    {
        Data *dataPtr = data.newPtr();
        DataTypes_.insert(DataTypeMap::value_type(type, dataPtr));
    }
}

void DataType::Release()
{
    BOOST_FOREACH(DataTypeMap::value_type &item, DataTypes_)
    {
        delete item.second;
    }
    DataTypes_.clear();
}





}

