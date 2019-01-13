#ifndef IMPRO_PRIVATE_INTERFACE_ALLJOYNTRACKING_HPP
#define IMPRO_PRIVATE_INTERFACE_ALLJOYNTRACKING_HPP

// alljoyn
#include <alljoyn/BusObject.h>

// impro
#include <impro/interface/tracking.hpp>

namespace impro
{
    namespace iface
    {
        class IMPRO_EXPORTS AlljoynRemoteTracking : public Tracking,
                                                    public ajn::MessageReceiver
        {
        public:
            /**
             * @brief AlljoynRemoteTracking
             * @param type
             * @param node
             */
            AlljoynRemoteTracking(const std::string &type,
                                  Node &node);

            /**
             * @brief ~AlljoynRemoteTracking
             */
            virtual ~AlljoynRemoteTracking();

            /**
             * @brief setTrackingMethod
             * @param method
             */
            virtual void setTrackingMethod(CameraMode mode, TrackingMethod method);

            /**
             * @brief setTemplateMatchParameters
             * @param templateSize (left, right, up, down)
             * @param searchWindow (left, right, up, down)
             */
            virtual void setTemplateMatchParameters(CameraMode mode, double *templateSize, double *searchWindow);

            /**
             * @brief setTrackingPoints
             * @param points
             */
            virtual void setTrackingPoints(CameraMode mode, std::vector<cv::Point2f> points);

            /**
             * @brief setTrackingOnOff
             * @param mode preview or picture
             * @param enabled true or false
             */
            virtual void setTrackingOnOff(CameraMode mode, bool enabled);
        };
    }
}

#endif // IMPRO_PRIVATE_INTERFACE_ALLJOYNTRACKING_HPP
