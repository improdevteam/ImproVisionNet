#ifndef IMPRO_DATA_TRIANGULATIONRESULT_HPP
#define IMPRO_DATA_TRIANGULATIONRESULT_HPP

// impro
#include <impro/data.hpp>
#include <impro/data/image.hpp>
#include <impro/data/arrayvec3f.hpp>
#include <impro/data/arraypoint2f.hpp>
#include <impro/data/arraypoint3d.hpp>

#define IMPRO_DATA_TRIANGULATIONRESULT "triangulationresult"

namespace impro
{
    namespace data
    {
        class IMPRO_EXPORTS TriangulationResult : public Data
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
            data::Image left_;
            data::ArrayVec3f leftAcc_;
            data::ArrayPoint2f leftPts_;
            data::ArrayPoint3d leftXYZPts_;
            data::Image right_;
            data::ArrayVec3f rightAcc_;
            data::ArrayPoint2f rightPts_;
            data::ArrayPoint3d rightXYZPts_;

            data::ArrayPoint3d userXYZPts_;
        };
    }
}

#endif // IMPRO_DATA_TRIANGULATIONRESULT_HPP
