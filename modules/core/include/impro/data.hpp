#ifndef IMPRO_DATA_HPP
#define IMPRO_DATA_HPP

// std
#include <vector>
#include <memory>

// opencv
#include <opencv2/core.hpp>

// impro
#include <impro/defines.hpp>

namespace impro
{
    /**
     * @brief The Impro Abstract Data class
     */
    class IMPRO_EXPORTS Data
    {
    public:
        /**
         * @brief default move
         */
        Data(Data &&) = default;


        /**
         * @brief default move
         */
        Data& operator=(Data&& other) = default;

        /**
         * @brief default copy
         */
        Data( const Data & ) = default;

        /**
         * @brief default copy
         */
        Data& operator=(const Data& other)  = default;

        /**
         * @brief ~Data
         */
        virtual ~Data() {}


        /**
         * @brief newPtr
         * @return
         */
        virtual std::shared_ptr<Data> newPtr() = 0;

        /**
         * @brief Creates a full copy of the underlying data.
         * @return pointer of new data
         */
        virtual std::shared_ptr<Data> clone() = 0;

        /**
         * @brief full copy underlying data to user given input
         * @param data user given input for copying data
         */
        virtual void clone(Data &data) = 0;

        /**
         * @brief save data to disk
         * @param dir directory for saving data
         * @param id unique identifier
         */
        virtual void save(const std::string &dir,
                          const std::string &id) = 0;

        /**
         * @brief load data from disk
         * @param dir directory for loading data
         * @param id unique identifier
         */
        virtual void load(const std::string &dir,
                          const std::string &id) = 0;

        /**
         * @brief remove data from disk
         * @param dir directory for removing data
         * @param id unique identifier
         */
        virtual void remove(const std::string &dir,
                            const std::string &id) = 0;

        /**
         * @brief serialize
         * @param raw output serializing data
         * @param offset offset of serializing raw data
         * @return offset value
         */
        virtual uint serialize(std::vector<uchar> &raw,
                               uint offset = 0) = 0;

        /**
         * @brief deserialize
         * @param raw input data for deserializing
         * @param offset offset of data for deserializing
         * @return offset value
         */
        virtual uint deserialize(std::vector<uchar> &raw,
                                 uint offset = 0) = 0;

    protected:
        /**
         * @brief Data
         */
        Data() {}
    };
}


#endif // IMPRO_DATA_HPP
