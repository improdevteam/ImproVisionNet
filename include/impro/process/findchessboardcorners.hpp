#ifndef IMPRO_PROCESS_FINDCHESSBOARDCORNERS_HPP
#define IMPRO_PROCESS_FINDCHESSBOARDCORNERS_HPP

// std
#include <queue>

// boost
#include <boost/thread.hpp>

// opencv
#include <opencv2/core.hpp>

// impro
#include <impro/process.hpp>
#include <impro/processcreator.hpp>
#include <impro/channelobserver.hpp>

namespace impro
{
    class Data;

    namespace process
    {
        class IMPRO_EXPORTS FindChessboardCorners : public Process,
                                                    public ChannelObserver
        {
        public:
            FindChessboardCorners(const std::string &id,
                                  const std::string &dir,
                                  Application &app,
                                  const std::string &spaceId,
                                  const std::string &displayChannelId,
                                  const std::string &analysisChannelId,
                                  const std::string &inputNodeId,
                                  const std::string &inputChannelId,
                                  cv::Size patternSize);

            virtual ~FindChessboardCorners();

            virtual void run();

            virtual void interrupt();

            virtual void dataReceived(impro::Channel &channel);

            void keepCorners();

            void setReverseCorners(bool needReverse);

        private:
            std::string spaceId_;
            std::string displayChannelId_;
            std::string analysisChannelId_;
            std::string inputNodeId_;
            std::string inputChannelId_;
            cv::Size patternSize_;

            std::string inputId_;
            Data *input_;
            Data *output_;

            boost::mutex inputMutex_;
            boost::mutex outputMutex_;

            bool needReverse_;
        };

        class IMPRO_EXPORTS FindChessboardCornersCreator : public ProcessCreator
        {
        public:
            FindChessboardCornersCreator(const std::string &spaceId,
                                         const std::string &displayChannelId,
                                         const std::string &analysisChannelId,
                                         const std::string &remoteNodeId,
                                         const std::string &inputChannelId,
                                         cv::Size patternSize)
                : ProcessCreator(),
                  spaceId_(spaceId),
                  displayChannelId_(displayChannelId),
                  analysisChannelId_(analysisChannelId),
                  remoteNodeId_(remoteNodeId),
                  inputChannelId_(inputChannelId),
                  patternSize_(patternSize) {}

            void setParameter(const std::string &spaceId,
                              const std::string &displayChannelId,
                              const std::string &analysisChannelId,
                              const std::string &remoteNodeId,
                              const std::string &inputChannelId,
                              cv::Size patternSize)
            {
                spaceId_ = spaceId;
                displayChannelId_ = displayChannelId;
                analysisChannelId_ = analysisChannelId;
                remoteNodeId_ = remoteNodeId;
                inputChannelId_ = inputChannelId;
                patternSize_ = patternSize;
            }

            virtual Process *create(const std::string &id,
                                    const std::string &dir,
                                    Application &app)
            {
                return new FindChessboardCorners(id,
                                                 dir,
                                                 app,
                                                 spaceId_,
                                                 displayChannelId_,
                                                 analysisChannelId_,
                                                 remoteNodeId_,
                                                 inputChannelId_,
                                                 patternSize_);
            }

        private:
            std::string spaceId_;
            std::string displayChannelId_;
            std::string analysisChannelId_;
            std::string remoteNodeId_;
            std::string inputChannelId_;
            cv::Size patternSize_;
        };

    }
}

#endif // IMPRO_PROCESS_FINDCHESSBOARDCORNERS_HPP
