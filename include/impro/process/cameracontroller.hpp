#ifndef IMPRO_PROCESS_CAMERACONTROLLER_HPP
#define IMPRO_PROCESS_CAMERACONTROLLER_HPP

// std
#include <vector>

// impro
#include <impro/process.hpp>

namespace impro
{
    class Space;

    namespace process
    {
        /**
         * @brief The CameraController class
         */
        class IMPRO_EXPORTS CameraController : public Process
        {
        public:
            /**
             * @brief CameraController
             * @param id
             * @param app
             */
            CameraController(const std::string &id,
                             const std::string &dir,
                             Application &app,
                             Space &space)
                : Process(id, dir, app),
                  space_(space) {}

//            /**
//             * @brief addRemoteNodes
//             * @param remoteNodeId
//             */
//            virtual void addRemoteNode(std::string remoteNodeId) = 0;

//            /**
//             * @brief setRemoteNodes
//             * @param remoteNodeIds
//             */
//            virtual void setRemoteNodes() = 0;

            /**
             * @brief takePicture
             */
            virtual void takePicture(const std::vector<std::string> &remoteNodeIds,
                                     int postProcessing) = 0;

        protected:
            Space &space_;
        };
    }
}

#endif // IMPRO_PROCESS_CAMERACONTROLLER_HPP
