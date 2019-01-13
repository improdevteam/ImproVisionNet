#ifndef IMPRO_INTERFACE_CAMERA_HPP
#define IMPRO_INTERFACE_CAMERA_HPP

// std

// opencv
#include <opencv2/core.hpp>

// impro
#include <impro/interface.hpp>

namespace impro
{
    namespace iface
    {
        /**
         * @brief The Camera class
         */
        class IMPRO_EXPORTS Camera : public Interface
        {
        public: // enum
            enum FocusMode
            {
                Auto = 0,
                Infinity
            };

        public:
            /**
             * @brief ~Camera
             */
            virtual ~Camera() {}

            /**
             * @brief takePicture
             */
            virtual void takePicture() = 0;

            /**
             * @brief setFocusMode
             * @param focusMode
             */
            virtual void setFocusMode(FocusMode focusMode) = 0;

            /**
             * @brief zoomIn
             */
            virtual void zoomIn() = 0;

            /**
             * @brief zoomOut
             */
            virtual void zoomOut() = 0;

            /**
             * @brief setPreviewTransferInterval
             * @param interval : milliseconds
             */
            virtual void setPreviewTransferInterval(int interval) = 0;

            /**
             * @brief autoTakingPictures
             * @param enabled : ture of false
             * @param interval : milliseconds
             */
            virtual void autoTakingPictures(bool enabled, int interval) = 0;

            /**
             * @brief getInfo
             * @return info
             */
            virtual std::string getInfo() = 0;

            /**
             * @brief getPreviewSize
             * @return preview image size
             */
            virtual cv::Size getPreviewSize() = 0;

            /**
             * @brief getPictureSize
             * @return picture image size
             */
            virtual cv::Size getPictureSize() = 0;

            /**
             * @brief getLinearAcceleration
             * @return
             */
            virtual cv::Vec3d getLinearAcceleration() = 0;

        protected:
            /**
             * @brief Camera
             * @param type
             * @param node
             */
            Camera(const std::string &type,
                   Node &node)
                : Interface(type, node) {}

        };
    }
}

#endif // IMPRO_INTERFACE_CAMERA_HPP
