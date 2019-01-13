#ifndef IMPRO_PRIVATE_INTERFACE_ALLJOYNK201711_HPP
#define IMPRO_PRIVATE_INTERFACE_ALLJOYNK201711_HPP

// alljoyn
#include <alljoyn/BusObject.h>

// impro
#include <impro/interface/k201711.hpp>

namespace impro
{
    namespace iface
    {
        /**
         * @brief The K201711 class
         */
        class IMPRO_EXPORTS AlljoynRemoteK201711 : public K201711,
                                                   public ajn::MessageReceiver

        {
        public:
            /**
             * @brief AlljoynK201711
             * @param type
             * @param node
             */
            AlljoynRemoteK201711(const std::string &type,
                           Node &node);

            /**
             * @brief ~AlljoynK201711
             */
            virtual ~AlljoynRemoteK201711();


            /**
             * @brief setCameraParameters
             * @param cameraMatrix
             * @param cameraDistCoeffs
             */
            virtual void setCameraParameters(cv::Mat cameraMatrix,
                                             cv::Mat cameraDistCoeffs);


            /**
             * @brief setK201711Parameters
             * @param cameraMatrix
             * @param cameraDistCoeffs
             */
            virtual void setK201711Parameters(int interval,
                                              double threshold1,
                                              double threshold2,
                                              int duration);


            /**
             * @brief setReferencePoints
             * @param referencePoints
             */
            virtual void setReferencePoints(std::vector<cv::Point2f> referencePoints);

            /**
             * @brief setTrackingPoints
             * @param trackingPoints
             */
            virtual void setTrackingPoints(std::vector<cv::Point2f> trackingPoints);


            /**
             * @brief startK201711
             */
            virtual void startK201711();


            /**
             * @brief stopK201711
             */
            virtual void stopK201711();

        };
    }
}

#endif // IMPRO_PRIVATE_INTERFACE_ALLJOYNK201711_HPP
