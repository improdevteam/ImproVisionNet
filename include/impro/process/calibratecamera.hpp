#ifndef IMPRO_PROCESS_CALIBRATECAMERA_HPP
#define IMPRO_PROCESS_CALIBRATECAMERA_HPP

// std
#include <queue>

// boost
#include <boost/thread.hpp>

// opencv
#include <opencv2/core.hpp>

// impro
#include <impro/channelobserver.hpp>
#include <impro/process.hpp>
#include <impro/processcreator.hpp>

namespace impro
{
    namespace process
    {
        class CalibrateCameraOutput
        {
        public:
            cv::Size imageSize_;

            double rms_;
            cv::Mat cameraMatrix_;
            cv::Mat distCoeffs_;
        };


        class IMPRO_EXPORTS CalibrateCamera : public Process,
                                              public ChannelObserver
        {
        public:
            CalibrateCamera(const std::string &id,
                            const std::string &dir,
                            Application &app,
                            const std::string &spaceId,
                            const std::string &inputNodeId,
                            const std::string &inputChannelId,
                            cv::Size patternSize,
                            cv::Size2f squareSize,
                            cv::Size imageSize);

            virtual void run();

            virtual void interrupt();

            virtual void dataReceived(Channel &channel);

            void clearCorners();

            double calibrate();

            void setOutput(CalibrateCameraOutput output) { output_ = output; }

            CalibrateCameraOutput getOutput() { return output_; }

        private:
            std::string spaceId_;
            std::string inputNodeId_;
            std::string inputChannelId_;
            cv::Size patternSize_;
            cv::Size2f squareSize_;

            std::vector<cv::Point3f> objectPoint_;
            cv::Size imageSize_;
            cv::Mat cameraMatrix_;
            cv::Mat cameraDistCoeffs_;

            boost::mutex mutex_;
            std::vector<std::vector<cv::Point2f> > cameraCorners_;

            CalibrateCameraOutput output_;
        };

        class IMPRO_EXPORTS CalibrateCameraCreator : public ProcessCreator
        {
        public:
            CalibrateCameraCreator(const std::string &spaceId,
                                   const std::string &inputNodeId,
                                   const std::string &inputChannelId,
                                   cv::Size patternSize,
                                   cv::Size2f squareSize,
                                   cv::Size imageSize)
                : ProcessCreator(),
                  spaceId_(spaceId),
                  inputNodeId_(inputNodeId),
                  inputChannelId_(inputChannelId),
                  patternSize_(patternSize),
                  squareSize_(squareSize),
                  imageSize_(imageSize) {}

            void setParameter(const std::string &spaceId,
                              const std::string &inputNodeId,
                              const std::string &inputChannelId,
                              cv::Size patternSize,
                              cv::Size2f squareSize,
                              cv::Size imageSize)
            {
                spaceId_ = spaceId;
                inputNodeId_ = inputNodeId;
                inputChannelId_ = inputChannelId;
                patternSize_ = patternSize;
                squareSize_ = squareSize;
                imageSize_ = imageSize;
            }

            virtual Process *create(const std::string &id,
                                    const std::string &dir,
                                    Application &app)
            {
                return new CalibrateCamera(id, dir, app,
                                           spaceId_,
                                           inputNodeId_,
                                           inputChannelId_,
                                           patternSize_,
                                           squareSize_,
                                           imageSize_);
            }

        private:
            std::string spaceId_;
            std::string inputNodeId_;
            std::string inputChannelId_;
            cv::Size patternSize_;
            cv::Size2f squareSize_;
            cv::Size imageSize_;
        };

    }
}


#endif // IMPRO_PROCESS_CALIBRATECAMERA_HPP
