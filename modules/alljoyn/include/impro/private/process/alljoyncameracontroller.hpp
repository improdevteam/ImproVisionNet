#ifndef IMPRO_PRIVATE_PROCESS_ALLJOYNCAMERACONTROLLER_HPP
#define IMPRO_PRIVATE_PROCESS_ALLJOYNCAMERACONTROLLER_HPP

// std
#include <vector>

// boost
#include <boost/thread.hpp>

// ajn
#include <alljoyn/BusObject.h>

// impro
#include <impro/process/cameracontroller.hpp>

namespace impro
{
    class Space;
    class AlljoynLocalNode;

    namespace process
    {
        /**
         * @brief The AlljoynCameraController class
         */
        class AlljoynCameraController : public CameraController,
                                        public ajn::BusObject
        {
        public:
            /**
             * @brief AlljoynCameraController
             * @param id
             * @param app
             * @param space
             */
            AlljoynCameraController(const std::string &id,
                                    const std::string &dir,
                                    Application &app,
                                    Space &space,
                                    const std::string &ajnServicePath);

            /**
             * @brief run
             */
            virtual void run();

            /**
             * @brief interrupt
             */
            virtual void interrupt();

//            /**
//             * @brief addRemoteNodes
//             * @param remoteNodeId
//             */
//            virtual void addRemoteNode(std::string remoteNodeId);

//            /**
//             * @brief setRemoteNodes
//             * @param remoteNodeIds
//             */
//            virtual void setRemoteNodes(const std::vector<std::string> &remoteNodeIds);

            /**
             * @brief takePicture
             */
            virtual void takePicture(const std::vector<std::string> &remoteNodeIds,
                                     int postProcessing);

        private:
//            AlljoynLocalNode &localNode_;
            std::vector<ajn::SessionId> remoteSessionIds_;
            const ajn::InterfaceDescription::Member *TakePicture;

//            boost::mutex mutex_;
        };
    }
}

#endif // IMPRO_PRIVATE_PROCESS_ALLJOYNCAMERACONTROLLER_HPP
