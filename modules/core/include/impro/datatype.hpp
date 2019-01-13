#ifndef IMPRO_DATATYPE_HPP
#define IMPRO_DATATYPE_HPP

// std
#include <map>

// impro
#include <impro/defines.hpp>

namespace impro
{
    class Data;

    typedef std::map<std::string, Data*> DataTypeMap;

    class IMPRO_EXPORTS DataType
    {
        friend class Channel;
    public:
        /**
         * @brief Prepare
         * @param type
         * @param data
         */
        static void Prepare(const std::string &type,
                            Data &data);

        /**
         * @brief Release
         */
        static void Release();

    private:
        static DataTypeMap DataTypes_;
    };
}


#endif // IMPRO_DATATYPE_HPP
