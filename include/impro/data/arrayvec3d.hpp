#ifndef IMPRO_DATA_ARRAYVEC3D_HPP
#define IMPRO_DATA_ARRAYVEC3D_HPP

// opencv
#include <opencv2/core.hpp>

// impro
#include <impro/data.hpp>

// ??
#define IMPRO_DATA_ARRAYVEC3D "ArrayVec3d"

namespace impro
{
    namespace data
    {
        /**
         * @brief The ArrayVec3d class
         */
        class IMPRO_EXPORTS ArrayVec3d : public Data
        {
        public:
            /**
             * @brief newPtr
             * @return
             */
            virtual std::shared_ptr<Data> newPtr();

            /**
             * @brief Creates a full copy of the underlying data.
             * @return pointer of new data
             */
            virtual std::shared_ptr<Data> clone();

            /**
             * @brief full copy underlying data to user given input
             * @param data user given input for copying data
             */
            virtual void clone(Data &data);

            /**
             * @brief save data to disk
             * @param dir directory for saving data
             * @param id unique identifier
             */
            virtual void save(const std::string &dir,
                              const std::string &id);

            /**
             * @brief load data from disk
             * @param dir directory for loading data
             * @param id unique identifier
             */
            virtual void load(const std::string &dir,
                              const std::string &id);

            /**
             * @brief remove data from disk
             * @param dir directory for removing data
             * @param id unique identifier
             */
            virtual void remove(const std::string &dir,
                                const std::string &id);

            /**
             * @brief serialize
             * @param raw output serializing data
             * @param offset offset of serializing raw data
             * @return offset value
             */
            virtual uint serialize(std::vector<uchar> &raw,
                                   uint offset = 0);

            /**
             * @brief deserialize
             * @param raw input data for deserializing
             * @param offset offset of data for deserializing
             * @return offset value
             */
            virtual uint deserialize(std::vector<uchar> &raw,
                                     uint offset = 0);

        public:
            std::vector<cv::Vec3d> vec_;
        };
    }
}

#endif // IMPRO_DATA_ARRAYVEC3D_HPP
