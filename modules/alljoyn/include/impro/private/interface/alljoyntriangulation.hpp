#ifndef IMPRO_PRIVATE_INTERFACE_ALLJOYNTRIANGULATION_HPP
#define IMPRO_PRIVATE_INTERFACE_ALLJOYNTRIANGULATION_HPP

// alljoyn
#include <alljoyn/BusObject.h>

// impro
#include <impro/interface/triangulation.hpp>

namespace impro
{
    namespace iface
    {
        class IMPRO_EXPORTS AlljoynRemoteTriangulation : public Triangulation,
                                                         public ajn::MessageReceiver
        {
        public:
            /**
             * @brief AlljoynRemoteTriangulation
             * @param type
             * @param node
             */
            AlljoynRemoteTriangulation(const std::string &type,
                                       Node &node);

            /**
             * @brief ~AlljoynRemoteTriangulation
             */
            virtual ~AlljoynRemoteTriangulation();

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
                                       std::vector<cv::Point2f> coord2);


            /**
             * @brief startTriangulation
             */
            virtual void startTriangulation();


            /**
             * @brief stopTriangulation
             */
            virtual void stopTriangulation();
        };
    }
}

#endif // IMPRO_PRIVATE_INTERFACE_ALLJOYNTRIANGULATION_HPP
