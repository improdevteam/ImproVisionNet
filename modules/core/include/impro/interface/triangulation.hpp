#ifndef IMPRO_INTERFACE_TRIANGULATION_HPP
#define IMPRO_INTERFACE_TRIANGULATION_HPP

// opencv
#include <opencv2/core.hpp>

// impro
#include <impro/interface.hpp>

namespace impro
{
    namespace iface
    {
        /**
         * @brief The Triangulation class
         */
        class IMPRO_EXPORTS Triangulation : public Interface
        {
        public:
            /**
             * @brief ~Triangulation
             */
            virtual ~Triangulation() {}


            /**
             * @brief setParameters
             * @param camera1Matrix
             * @param camera1DistCoeffs
             * @param camera2Matrix
             * @param camera2DistCoeffs
             * @param R
             * @param T
             * @param R1
             * @param P1
             * @param R2
             * @param P2
             */
            virtual void setParameters(int type,
                                       std::string leftNode,
                                       std::string rightNode,
                                       cv::Mat camera1Matrix,
                                       cv::Mat camera1DistCoeffs,
                                       cv::Mat camera2Matrix,
                                       cv::Mat camera2DistCoeffs,
                                       cv::Mat R,  cv::Mat T,
                                       cv::Mat R1, cv::Mat P1,
                                       cv::Mat R2, cv::Mat P2,
                                       std::vector<cv::Point2f> coord1,
                                       std::vector<cv::Point2f> coord2) = 0;


            /**
             * @brief startTriangulation
             */
            virtual void startTriangulation() = 0;


            /**
             * @brief stopTriangulation
             */
            virtual void stopTriangulation() = 0;

        protected:
            /**
             * @brief Triangulation
             * @param type
             * @param node
             */
            Triangulation(const std::string &type,
                          Node &node)
                : Interface(type, node) {}

        };
    }
}

#endif // IMPRO_INTERFACE_TRIANGULATION_HPP
