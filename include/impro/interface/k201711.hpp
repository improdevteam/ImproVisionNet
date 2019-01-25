#ifndef IMPRO_INTERFACE_K201711_H
#define IMPRO_INTERFACE_K201711_H

// opencv
#include <opencv2/core.hpp>

// impro
#include <impro/interface.hpp>

namespace impro
{
    namespace iface
    {
        /**
         * @brief The K201711 class
         */
        class IMPRO_EXPORTS K201711 : public Interface
        {
        public:
            /**
             * @brief ~K201711
             */
            virtual ~K201711() {}


            /**
             * @brief setCameraParameters
             * @param cameraMatrix
             * @param cameraDistCoeffs
             */
            virtual void setCameraParameters(cv::Mat cameraMatrix,
                                             cv::Mat cameraDistCoeffs) = 0;


            /**
             * @brief setK201711Parameters
             * @param cameraMatrix
             * @param cameraDistCoeffs
             */
            virtual void setK201711Parameters(int interval,
                                              double threshold1,
                                              double threshold2,
                                              int duration) = 0;

            /**
             * @brief setReferencePoints
             * @param referencePoints
             */
            virtual void setReferencePoints(std::vector<cv::Point2f> referencePoints) = 0;

            /**
             * @brief setTrackingPoints
             * @param trackingPoints
             */
            virtual void setTrackingPoints(std::vector<cv::Point2f> trackingPoints) = 0;


            /**
             * @brief startK201711
             */
            virtual void startK201711() = 0;


            /**
             * @brief stopK201711
             */
            virtual void stopK201711() = 0;

        protected:
            /**
             * @brief K201711
             * @param type
             * @param node
             */
            K201711(const std::string &type,
                    Node &node)
                : Interface(type, node) {}

        };
    }
}

#endif // K201711_H
