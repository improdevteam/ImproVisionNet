// impro
#include <impro/datatype.hpp>
#include <impro/data.hpp>

namespace impro
{

DataTypeMap DataType::DataTypes_;

void DataType::Prepare(const std::string &type, Data &&data)
{
    if(DataTypes_.find(type) == DataTypes_.end())
    {
        std::shared_ptr<Data> dataPtr = data.newPtr();
        DataTypes_.insert(DataTypeMap::value_type(type, dataPtr));
    }
}

void DataType::Release()
{
    DataTypes_.clear();
}





}

