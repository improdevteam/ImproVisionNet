#ifndef IMPRO_PROCESS_RELAY_HPP
#define IMPRO_PROCESS_RELAY_HPP

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
    class Data;

    namespace process
    {
        class IMPRO_EXPORTS Relay : public Process,
                                    public ChannelObserver
        {
        public:
            Relay(const std::string &id,
                  const std::string &dir,
                  Application &app,
                  const std::string &spaceId,
                  const std::string &outputChannelId,
                  const std::string &inputNodeId,
                  const std::string &inputChannelId);

            virtual void run();

            virtual void interrupt();

            virtual void dataReceived(Channel &channel);

        private:
            std::string spaceId_;
            std::string outputChannelId_;
            std::string inputNodeId_;
            std::string inputChannelId_;
        };

        class IMPRO_EXPORTS RelayCreator : public ProcessCreator
        {
        public:
            RelayCreator(const std::string &spaceId,
                         const std::string &outputChannelId,
                         const std::string &inputNodeId,
                         const std::string &inputChannelId)
                : ProcessCreator(),
                  spaceId_(spaceId),
                  outputChannelId_(outputChannelId),
                  inputNodeId_(inputNodeId),
                  inputChannelId_(inputChannelId) {}

            void setParameter(const std::string &spaceId,
                              const std::string &outputChannelId,
                              const std::string &inputNodeId,
                              const std::string &inputChannelId)
            {
                spaceId_ = spaceId;
                outputChannelId_ = outputChannelId;
                inputNodeId_ = inputNodeId;
                inputChannelId_ = inputChannelId;
            }

            virtual Process *create(const std::string &id,
                                    const std::string &dir,
                                    Application &app)
            {
                return new Relay(id,
                                 dir,
                                 app,
                                 spaceId_,
                                 outputChannelId_,
                                 inputNodeId_,
                                 inputChannelId_);
            }

        private:
            std::string spaceId_;
            std::string outputChannelId_;
            std::string inputNodeId_;
            std::string inputChannelId_;
        };
    }
}

#endif // IMPRO_PROCESS_RELAY_HPP
