#ifndef IMPRO_INTERFACE_TRACKING_HPP
#define IMPRO_INTERFACE_TRACKING_HPP

// opencv
#include <opencv2/core.hpp>

// impro
#include <impro/interface.hpp>

namespace impro
{
    namespace iface
    {
        /**
         * @brief The Tracking class
         */
        class IMPRO_EXPORTS Tracking : public Interface
        {
        public: // enum
            enum TrackingMethod
            {
                TemplateMatch = 0,
                FindTransformECC
            };

            enum CameraMode
            {
                Preview = 0,
                Picture
            };

        public:
            /**
             * @brief ~Tracking
             */
            virtual ~Tracking() {}


            /**
             * @brief setTrackingMethod
             * @param method
             */
            virtual void setTrackingMethod(CameraMode mode, TrackingMethod method) = 0;

            /**
             * @brief setTemplateMatchParameters
             * @param templateSize (left, right, up, down)
             * @param searchWindow (left, right, up, down)
             */
            virtual void setTemplateMatchParameters(CameraMode mode, double *templateSize, double *searchWindow) = 0;


            /**
             * @brief setTrackingPoints
             * @param points
             */
            virtual void setTrackingPoints(CameraMode mode, std::vector<cv::Point2f> points) = 0;

            /**
             * @brief setTrackingOnOff
             * @param mode preview or picture
             * @param enabled true or false
             */
            virtual void setTrackingOnOff(CameraMode mode, bool enabled) = 0;


        protected:
            /**
             * @brief Tracking
             * @param type
             * @param node
             */
            Tracking(const std::string &type,
                     Node &node)
                : Interface(type, node) {}

        };
    }
}

#endif // IMPRO_INTERFACE_TRACKING_HPP
