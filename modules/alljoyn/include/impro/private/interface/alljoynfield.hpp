#ifndef IMPRO_PRIVATE_ALLJOYNFIELD_HPP
#define IMPRO_PRIVATE_ALLJOYNFIELD_HPP

// alljoyn
#include <alljoyn/BusObject.h>

// impro
#include <impro/interface/field.hpp>

namespace impro
{
    namespace iface
    {
        class IMPRO_EXPORTS AlljoynRemoteField : public Field,
                                                    public ajn::MessageReceiver
        {
        public:
            /**
             * @brief AlljoynRemoteField
             * @param type
             * @param node
             */
            AlljoynRemoteField(const std::string &type,
                                  Node &node);

            /**
             * @brief ~AlljoynRemoteField
             */
            virtual ~AlljoynRemoteField();

            /**
             * @brief setParameters
             */
            virtual void setParameters(CameraMode mode, std::vector<double> params);


            /**
             * @brief setPoints
             * @param points
             */
            virtual void setPoints(CameraMode mode, std::vector<cv::Point2f> points);

            /**
             * @brief setFieldOnOff
             * @param mode preview or picture
             * @param enabled true or false
             */
            virtual void setFieldOnOff(CameraMode mode, bool enabled);

        };
    }
}

#endif // IMPRO_PRIVATE_ALLJOYNFIELD_HPP
