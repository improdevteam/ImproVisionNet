#ifndef IMPRO_PROCESS_TRIANGULATIONPROCESS_HPP
#define IMPRO_PROCESS_TRIANGULATIONPROCESS_HPP

// std
#include <string>
#include <queue>

// boost
#include <boost/thread.hpp>

// opencv
#include <opencv2/core.hpp>

// impro
#include <impro/channelobserver.hpp>
#include <impro/processcreator.hpp>
#include <impro/process.hpp>
#include <impro/data/imageaccpts.hpp>

namespace impro
{
    namespace process
    {
        class IMPRO_EXPORTS Triangulation : public Process,
                                            public ChannelObserver
        {
        public:
            Triangulation(const std::string &id,
                          const std::string &dir,
                          Application &app,
                          const std::string &spaceId,
                          const std::string &resultChannelId,
                          const std::string &input1NodeId,
                          const std::string &input1ChannelId,
                          const std::string &input2NodeId,
                          const std::string &input2ChannelId);

            virtual void run();

            virtual void interrupt();

            virtual void dataReceived(Channel &channel);

            void defineCoordinate(std::vector<cv::Point2f> leftPts,
                                  std::vector<cv::Point2f> rightPts);

            std::vector<cv::Point3d> getLeftCoordinate() { return leftCoord_; }
            std::vector<cv::Point3d> getRightCoordinate() { return rightCoord_; }

            void setLeftCoordinate(std::vector<cv::Point3d> leftCoord) { leftCoord_ = leftCoord; }
            void setRightCoordinate(std::vector<cv::Point3d> rightCoord) { rightCoord_ = rightCoord; }

            void setParameter(cv::Mat camera1Matrix,
                              cv::Mat camera1DistCoeffs,
                              cv::Mat camera2Matrix,
                              cv::Mat camera2DistCoeffs,
                              cv::Mat R,  cv::Mat T,
                              cv::Mat R1, cv::Mat P1,
                              cv::Mat R2, cv::Mat P2)
            {
                camera1Matrix_ = camera1Matrix;
                camera1DistCoeffs_ = camera1DistCoeffs;
                camera2Matrix_ = camera2Matrix;
                camera2DistCoeffs_ = camera2DistCoeffs;
                R_ = R; T_ = T; R1_ = R1; R2_ = R2; P1_ = P1; P2_ = P2;
            }

        private:
            std::string spaceId_;
            std::string resultChannelId_;
            std::string input1NodeId_;
            std::string input1ChannelId_;
            std::string input2NodeId_;
            std::string input2ChannelId_;

            cv::Mat camera1Matrix_;
            cv::Mat camera1DistCoeffs_;
            cv::Mat camera2Matrix_;
            cv::Mat camera2DistCoeffs_;
            cv::Mat R_, T_, R1_, P1_, R2_, P2_;

            boost::mutex mutex_;
//            std::queue<std::string> camera1_;
//            std::queue<std::string> camera2_;

            data::ImageAccPts *input1_;
            data::ImageAccPts *input2_;

            std::vector<cv::Point3d> leftCoord_;
            std::vector<cv::Point3d> rightCoord_;
        };

        class IMPRO_EXPORTS TriangulationCreator : public ProcessCreator
        {
        public:
            TriangulationCreator(const std::string &spaceId,
                                 const std::string &resultChannelId,
                                 const std::string &input1NodeId,
                                 const std::string &input1ChannelId,
                                 const std::string &input2NodeId,
                                 const std::string &input2ChannelId)
                : ProcessCreator(),
                  spaceId_(spaceId),
                  resultChannelId_(resultChannelId),
                  input1NodeId_(input1NodeId),
                  input1ChannelId_(input1ChannelId),
                  input2NodeId_(input2NodeId),
                  input2ChannelId_(input2ChannelId) {}

            void setParameter(const std::string &spaceId,
                              const std::string &resultChannelId,
                              const std::string &input1NodeId,
                              const std::string &input1ChannelId,
                              const std::string &input2NodeId,
                              const std::string &input2ChannelId)
            {
                spaceId_ = spaceId;
                resultChannelId_ = resultChannelId;
                input1NodeId_ = input1NodeId;
                input1ChannelId_ = input1ChannelId;
                input2NodeId_ = input2NodeId;
                input2ChannelId_ = input2ChannelId;
            }

            virtual Process *create(const std::string &id,
                                    const std::string &dir,
                                    Application &app)
            {
                return new Triangulation(id,
                                         dir,
                                         app,
                                         spaceId_,
                                         resultChannelId_,
                                         input1NodeId_,
                                         input1ChannelId_,
                                         input2NodeId_,
                                         input2ChannelId_);
            }

        private:
            std::string spaceId_;
            std::string resultChannelId_;
            std::string input1NodeId_;
            std::string input1ChannelId_;
            std::string input2NodeId_;
            std::string input2ChannelId_;
        };
    }
}

#endif // IMPRO_PROCESS_TRIANGULATIONPROCESS_HPP
