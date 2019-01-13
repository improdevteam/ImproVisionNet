#ifndef IMPRO_PRIVATE_INTERFACE_ALLJOYNCAMERA_HPP
#define IMPRO_PRIVATE_INTERFACE_ALLJOYNCAMERA_HPP

// alljoyn
#include <alljoyn/BusObject.h>

// impro
#include <impro/interface/camera.hpp>

namespace impro
{
    namespace iface
    {
        class IMPRO_EXPORTS AlljoynRemoteCamera : public Camera,
                                                  public ajn::MessageReceiver
        {
        public:
            /**
             * @brief AlljoynRemoteCamera
             * @param type
             * @param node
             */
            AlljoynRemoteCamera(const std::string &type,
                                Node &node);

            /**
             * @brief ~AlljoynRemoteCamera
             */
            virtual ~AlljoynRemoteCamera();

            /**
             * @brief takePicture
             */
            virtual void takePicture();

            /**
             * @brief setFocusMode
             */
            virtual void setFocusMode(FocusMode focusMode);

            /**
             * @brief zoomIn
             */
            virtual void zoomIn();

            /**
             * @brief zoomOut
             */
            virtual void zoomOut();

            /**
             * @brief setPreviewTransferInterval
             * @param interval : milliseconds
             */
            virtual void setPreviewTransferInterval(int interval);

            /**
             * @brief autoTakingPictures
             * @param enabled : ture of false
             * @param interval : milliseconds
             */
            virtual void autoTakingPictures(bool enabled, int interval);

            /**
             * @brief getInfo
             * @return info
             */
            virtual std::string getInfo();

            /**
             * @brief getPreviewSize
             * @return preview image size
             */
            virtual cv::Size getPreviewSize();

            /**
             * @brief getPictureSize
             * @return picture image size
             */
            virtual cv::Size getPictureSize();

            /**
             * @brief getLinearAcceleration
             * @return
             */
            virtual cv::Vec3d getLinearAcceleration();
        };
    }
}

#endif // IMPRO_PRIVATE_INTERFACE_ALLJOYNCAMERA_HPP
