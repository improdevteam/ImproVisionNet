#ifndef IMPRO_INTERFACE_FIELD_HPP
#define IMPRO_INTERFACE_FIELD_HPP

// opencv
#include <opencv2/core.hpp>

// impro
#include <impro/interface.hpp>

namespace impro
{
    namespace iface
    {
        /**
         * @brief The Tracking class
         */
        class IMPRO_EXPORTS Field : public Interface
        {
        public: // enum
            enum CameraMode
            {
                Preview = 0,
                Picture
            };

        public:
            /**
             * @brief ~Tracking
             */
            virtual ~Field() {}


            /**
             * @brief setParameters
             */
            virtual void setParameters(CameraMode mode, std::vector<double> params) = 0;


            /**
             * @brief setPoints
             * @param points
             */
            virtual void setPoints(CameraMode mode, std::vector<cv::Point2f> points) = 0;

            /**
             * @brief setFieldOnOff
             * @param mode preview or picture
             * @param enabled true or false
             */
            virtual void setFieldOnOff(CameraMode mode, bool enabled) = 0;


        protected:
            /**
             * @brief Field
             * @param type
             * @param node
             */
            Field(const std::string &type,
                        Node &node)
                : Interface(type, node) {}

        };
    }
}

#endif // IMPRO_INTERFACE_STRAINFIELD_HPP
