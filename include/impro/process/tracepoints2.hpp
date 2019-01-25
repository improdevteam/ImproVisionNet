#ifndef IMPRO_PROCESS_TRACEPOINTS2_HPP
#define IMPRO_PROCESS_TRACEPOINTS2_HPP

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
#include <impro/data/imageacc.hpp>
#include <impro/data/imageaccpts.hpp>

namespace impro
{
    namespace process
    {
        class IMPRO_EXPORTS TracePoints2 : public Process,
                                          public ChannelObserver
        {
        public:
            TracePoints2(const std::string &id,
                         const std::string &dir,
                         Application &app,
                         const std::string &spaceId,
                         const std::string &outputChannelId,
                         const std::string &inputNodeId,
                         const std::string &inputChannelId,
                         int searchSize);

            virtual void run();

            virtual void interrupt();

            virtual void dataReceived(Channel &channel);

            void setPoints(std::vector<cv::Point2f> points);

            void setSearchSize(int searchSize);

            void generateTemplates(cv::Mat origin, int x1, int x2, int y1, int y2);

            std::vector<cv::Mat> tmplts_;

        private:
            std::string spaceId_;
            std::string outputChannelId_;
            std::string inputNodeId_;
            std::string inputChannelId_;
            int searchSize_;

            std::string inputId_;
            Data *input_;
            Data *output_;

            boost::mutex inputMutex_;
            boost::mutex outputMutex_;
        };

        class IMPRO_EXPORTS TracePoints2Creator : public ProcessCreator
        {
        public:
            TracePoints2Creator(const std::string &spaceId,
                               const std::string &outputChannelId,
                               const std::string &inputNodeId,
                               const std::string &inputChannelId,
                               int searchSize)
                : ProcessCreator(),
                  spaceId_(spaceId),
                  outputChannelId_(outputChannelId),
                  inputNodeId_(inputNodeId),
                  inputChannelId_(inputChannelId),
                  searchSize_(searchSize) {}

            void setParameter(const std::string &spaceId,
                              const std::string &outputChannelId,
                              const std::string &inputNodeId,
                              const std::string &inputChannelId,
                              int searchSize)
            {
                spaceId_ = spaceId;
                outputChannelId_ = outputChannelId;
                inputNodeId_ = inputNodeId;
                inputChannelId_ = inputChannelId;
                searchSize_ = searchSize;
            }

            virtual Process *create(const std::string &id,
                                    const std::string &dir,
                                    Application &app)
            {
                return new TracePoints2(id,
                                        dir,
                                        app,
                                        spaceId_,
                                        outputChannelId_,
                                        inputNodeId_,
                                        inputChannelId_,
                                        searchSize_);
            }

        private:
            std::string spaceId_;
            std::string outputChannelId_;
            std::string inputNodeId_;
            std::string inputChannelId_;
            int searchSize_;
        };
    }
}

#endif // IMPRO_PROCESS_TRACEPOINTS2_HPP
