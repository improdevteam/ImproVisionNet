#ifndef IMPRO_ALLJOYNSPACEBUILDER_HPP
#define IMPRO_ALLJOYNSPACEBUILDER_HPP

// impro
#include <impro/spacebuilder.hpp>

#define IMPRO_SPACE_TYPE_ALLJOYN "alljoynspace"

namespace impro
{
    class AlljoynConfiguration;

    /**
     * @brief The AlljoynSpaceBuilder class
     */
    class IMPRO_EXPORTS AlljoynSpaceBuilder : public SpaceBuilder
    {
    public:
        /**
         * @brief AlljoynSpaceBuilder
         * @param enableRouter
         */
        AlljoynSpaceBuilder(bool enableRouter = true);

        /**
         * @brief clone
         * @return
         */
        virtual SpaceBuilder* newPtr();

        /**
         * @brief prepare
         * @param config
         */
        virtual void prepare();

        /**
         * @brief release
         */
        virtual void release();

        /**
         * @brief build
         * @param spaceId
         * @param nodeId
         * @param config
         * @return
         */
        virtual Space* build(const std::string &spaceId,
                             const std::string &nodeId,
                             const std::string &dir);

    private:
        static bool _enableRouter_;

    };
}


#endif // IMPRO_ALLJOYNSPACEBUILDER_HPP
