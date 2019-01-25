#ifndef IMPRO_DATA_K201711RESULT_HPP
#define IMPRO_DATA_K201711RESULT_HPP

// impro
#include <impro/data.hpp>
#include <impro/data/image.hpp>
#include <impro/data/arrayvec3f.hpp>
#include <impro/data/arraypoint2f.hpp>

#define IMPRO_DATA_K201711RESULT "k201711result"

namespace impro
{
    namespace data
    {
        class IMPRO_EXPORTS K201711Result : public Data
        {
        public:
            virtual Data* newPtr();

            virtual Data* clone();

            virtual void clone(Data &data);

            virtual void save(const std::string &directory,
                              const std::string &identifier);

            virtual void load(const std::string &directory,
                              const std::string &identifier);

            virtual void remove(const std::string &directory,
                                const std::string &identifier);

            virtual uint serialize(std::vector<uchar> &raw,
                                   uint offset = 0);

            virtual uint deserialize(std::vector<uchar> &raw,
                                     uint offset = 0);

        public:
            data::ArrayPoint2f initialReferencePoints_;
            data::ArrayPoint2f initialTrackingPoints_;
            data::ArrayPoint2f currentReferencePoints_;
            data::ArrayPoint2f currentTrackingPoints_;
            data::ArrayPoint2f correctedReferencePoints_;
            data::ArrayPoint2f correctedTrackingPoints_;
            cv::Mat cameraMovementTransformMatrix_;
        };
    }
}

#endif // IMPRO_DATA_K201711RESULT_HPP
