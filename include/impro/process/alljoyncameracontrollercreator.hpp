#ifndef IMPRO_PROCESS_ALLJOYNCAMERACONTROLLERCREATOR_HPP
#define IMPRO_PROCESS_ALLJOYNCAMERACONTROLLERCREATOR_HPP

// std
#include <vector>

// impro
#include <impro/processcreator.hpp>

namespace impro
{
    class LocalNode;
    class RemoteNode;

    namespace process
    {
        class IMPRO_EXPORTS AlljoynCameraControllerCreator : public ProcessCreator
        {
        public:
            /**
             * @brief AlljoynCameraControllerCreator
             */
            AlljoynCameraControllerCreator(const std::string &spaceId);

            /**
             * @brief create
             * @param id
             * @param app
             * @return
             */
            virtual Process* create(const std::string &id,
                                    const std::string &dir,
                                    Application &app);

        private:
            std::string spaceId_;
        };
    }
}

#endif // IMPRO_PROCESS_ALLJOYNCAMERACONTROLLERCREATOR_HPP
