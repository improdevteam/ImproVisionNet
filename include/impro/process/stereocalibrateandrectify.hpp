#ifndef IMPRO_PROCESS_STEREOCALIBRATE_HPP
#define IMPRO_PROCESS_STEREOCALIBRATE_HPP

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
        class StereoCalibrateAndRectifyOutput
        {
        public:
            cv::Size imageSize_;

            double rms_;
            cv::Mat cameraMatrix_[2];
            cv::Mat distCoeffs_[2];
            cv::Mat R_, T_, E_, F_;

            cv::Mat R1_;
            cv::Mat P1_;
            cv::Mat R2_;
            cv::Mat P2_;
            cv::Mat Q_;

            cv::Mat rmap_[2][2];
            cv::Rect validROI_[2];
        };


        class IMPRO_EXPORTS StereoCalibrateAndRectify : public Process,
                                                        public ChannelObserver
        {
        public:
            StereoCalibrateAndRectify(const std::string &id,
                                      const std::string &dir,
                                      Application &app,
                                      const std::string &spaceId,
                                      const std::string &input1NodeId,
                                      const std::string &input1ChannelId,
                                      const std::string &input2NodeId,
                                      const std::string &input2ChannelId,
                                      cv::Size patternSize,
                                      cv::Size2f squareSize,
                                      cv::Size imageSize);

            virtual void run();

            virtual void interrupt();

            virtual void dataReceived(Channel &channel);

            void clearCorners();

            double calibrate();

            void setOutput(StereoCalibrateAndRectifyOutput output) { output_ = output; }

            StereoCalibrateAndRectifyOutput getOutput() { return output_; }

        private:
            std::string spaceId_;
            std::string input1NodeId_;
            std::string input1ChannelId_;
            std::string input2NodeId_;
            std::string input2ChannelId_;
            cv::Size patternSize_;
            cv::Size2f squareSize_;

            std::vector<cv::Point3f> objectPoint_;
            cv::Size imageSize_;
            cv::Mat camera1Matrix_;
            cv::Mat camera1DistCoeffs_;
            cv::Mat camera2Matrix_;
            cv::Mat camera2DistCoeffs_;

            boost::mutex mutex_;
            std::vector<std::vector<cv::Point2f> > camera1Corners_;
            std::vector<std::vector<cv::Point2f> > camera2Corners_;

            StereoCalibrateAndRectifyOutput output_;
        };

        class IMPRO_EXPORTS StereoCalibrateAndRectifyCreator : public ProcessCreator
        {
        public:
            StereoCalibrateAndRectifyCreator(const std::string &spaceId,
                                             const std::string &input1NodeId,
                                             const std::string &input1ChannelId,
                                             const std::string &input2NodeId,
                                             const std::string &input2ChannelId,
                                             cv::Size patternSize,
                                             cv::Size2f squareSize,
                                             cv::Size imageSize)
                : ProcessCreator(),
                  spaceId_(spaceId),
                  input1NodeId_(input1NodeId),
                  input1ChannelId_(input1ChannelId),
                  input2NodeId_(input2NodeId),
                  input2ChannelId_(input2ChannelId),
                  patternSize_(patternSize),
                  squareSize_(squareSize),
                  imageSize_(imageSize) {}

            void setParameter(const std::string &spaceId,
                              const std::string &input1NodeId,
                              const std::string &input1ChannelId,
                              const std::string &input2NodeId,
                              const std::string &input2ChannelId,
                              cv::Size patternSize,
                              cv::Size2f squareSize,
                              cv::Size imageSize)
            {
                spaceId_ = spaceId;
                input1NodeId_ = input1NodeId;
                input1ChannelId_ = input1ChannelId;
                input2NodeId_ = input2NodeId;
                input2ChannelId_ = input2ChannelId;
                patternSize_ = patternSize;
                squareSize_ = squareSize;
                imageSize_ = imageSize;
            }

            virtual Process *create(const std::string &id,
                                    const std::string &dir,
                                    Application &app)
            {
                return new StereoCalibrateAndRectify(id,
                                                     dir,
                                                     app,
                                                     spaceId_,
                                                     input1NodeId_,
                                                     input1ChannelId_,
                                                     input2NodeId_,
                                                     input2ChannelId_,
                                                     patternSize_,
                                                     squareSize_,
                                                     imageSize_);
            }

        private:
            std::string spaceId_;
            std::string input1NodeId_;
            std::string input1ChannelId_;
            std::string input2NodeId_;
            std::string input2ChannelId_;
            cv::Size patternSize_;
            cv::Size2f squareSize_;
            cv::Size imageSize_;
        };

    }
}


#endif // IMPRO_PROCESS_STEREOCALIBRATE_HPP
