#ifndef IMPRO_SPACEBUILDER_HPP
#define IMPRO_SPACEBUILDER_HPP

// std
#include <string>
#include <map>

// imrpo
#include <impro/defines.hpp>


namespace impro
{
    class SpaceBuilder;
    class Space;

    typedef std::map<std::string, SpaceBuilder*> SpaceBuilderMap;

    /**
     * @brief The SpaceBuilder class
     */
    class IMPRO_EXPORTS SpaceBuilder
    {
        friend class ApplicationImpl;
    public:
        /**
         * @brief Prepare
         * @param type
         * @param builder
         */
        static void Prepare(const std::string &type,
                            SpaceBuilder &&builder);

        /**
         * @brief Release
         */
        static void Release();

    private:
        static SpaceBuilderMap Builders_;

    public:
        /**
         * @brief SpaceBuilder is not copyable
         */
        SpaceBuilder( const SpaceBuilder & ) = delete;

        /**
         * @brief SpaceBuilder is not copyable
         */
        SpaceBuilder& operator=(const SpaceBuilder& other)  = delete;

        /**
         * @brief ~SpaceBuilder
         */
        virtual ~SpaceBuilder() {}

        /**
         * @brief clone
         * @return
         */
        virtual SpaceBuilder* newPtr() = 0;

        /**
         * @brief prepare
         */
        virtual void prepare() = 0;

        /**
         * @brief release
         */
        virtual void release() = 0;

        /**
         * @brief build
         * @param spaceId
         * @param nodeId
         * @param config
         * @return
         */
        virtual Space* build(const std::string &spaceId,
                             const std::string &nodeId,
                             const std::string &dir) = 0;
    protected:
        SpaceBuilder() {}
    };
}


#endif // IMPRO_SPACEBUILDER_HPP
