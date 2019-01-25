#ifndef IMPRO_SPACE_HPP
#define IMPRO_SPACE_HPP

// std
#include <string>
#include <vector>

// impro
#include <impro/defines.hpp>

namespace impro
{
    class LocalNode;
    class RemoteNode;

    /**
     * @brief The Space class
     */
    class IMPRO_EXPORTS Space
    {
    public:
        /**
         * @brief default move
         */
        Space(Space &&) = default;


        /**
         * @brief default move
         */
        Space& operator=(Space&& other) = default;

        /**
         * @brief Space is not copyable
         */
        Space( const Space & ) = delete;

        /**
         * @brief Space is not copyable
         */
        Space& operator=(const Space& other)  = delete;

        /**
         * @brief ~Space
         */
        virtual ~Space();

        /**
         * @brief hasRemoteNode
         * @param nodeId
         * @return
         */
        virtual bool hasRemoteNode(const std::string &nodeId) = 0;

        /**
         * @brief getRemoteNode
         * @param nodeId
         * @return
         */
        virtual RemoteNode& getRemoteNode(const std::string &nodeId) = 0;

        /**
         * @brief getLocalNode
         * @return
         */
        LocalNode& getLocalNode() { return *node_; }

        /**
         * @brief getId
         * @return
         */
        std::string getId() { return id_; }

        /**
         * @brief getDir
         * @return
         */
        std::string getDir() { return dir_; }

    protected:
        /**
         * @brief Space
         * @param spaceId
         * @param dir
         */
        Space(const std::string &spaceId,
              const std::string &dir);

    protected:
        std::string id_;
        std::string dir_;
        LocalNode *node_;
    };
}


#endif // IMPRO_SPACE_HPP
