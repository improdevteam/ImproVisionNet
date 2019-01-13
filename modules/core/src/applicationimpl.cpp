// std
#include <iostream> // debug

// boost
#include <boost/foreach.hpp>

// impro
#include <impro/private/applicationimpl.hpp>
#include <impro/processcreator.hpp>
#include <impro/process.hpp>
#include <impro/spacebuilder.hpp>
#include <impro/space.hpp>
#include <impro/interfacecreator.hpp>
#include <impro/datatype.hpp>
#include <impro/errors.hpp>

using namespace std;
using namespace boost;

namespace impro
{

Application *application_ = NULL;
Application& Application::Initialize()
{
    if(application_ == NULL)
        application_ = new ApplicationImpl();
    return *application_;
}

void Application::Finalize()
{
    if(application_ != NULL)
    {
        delete application_;
        application_ = NULL;
    }

    //
    DataType::Release();
    InterfaceCreator::Release();
    SpaceBuilder::Release();
}

Application& Application::getInstance()
{
    if(application_ == NULL)
        application_ = new ApplicationImpl();
    return *application_;
}

void Application::releaseInstance()
{
    if(application_ != NULL)
    {
        delete application_;
        application_ = NULL;
    }
}

//Application& Application::getInstance()
//{
//    static ApplicationImpl application_;
//    return application_;
//}

ApplicationImpl::~ApplicationImpl()
{
    // Clear Process
    BOOST_FOREACH(ProcessMap::value_type &item, processes_)
    {
        Process *process = item.second;
        if(process)
        {
            delete process;
            process = NULL;
        }
    }
    processes_.clear();

    // Clear Space
    BOOST_FOREACH(SpaceMap::value_type &item, spaces_)
    {
        Space *space = item.second;
        if(space)
        {
            delete space;
            space = NULL;
        }
    }
    spaces_.clear();
}

// Process ---------------------------------------------------------
Process& ApplicationImpl::createProcess(const string &id,
                                        const string &dir,
                                        ProcessCreator &creator)
{
    if(processes_.find(id) == processes_.end())
        processes_.insert(ProcessMap::value_type
                          (id, creator.create(id, dir, *this)));
    return *processes_.at(id);
}

bool ApplicationImpl::hasProcess(const string &id)
{
    if(processes_.find(id) != processes_.end())
        return true;
    else
        return false;
}

Process& ApplicationImpl::getProcess(const string &id)
{
    return *processes_.at(id);
}

void ApplicationImpl::activate(const string &id,
                               bool block)
{
    ProcessMap::iterator iter = processes_.find(id);
    if(iter != processes_.end() &&
       iter->second->getStatus() != Process::running)
    {
//        thread *t = threads_.create_thread(boost::bind(&Process::run,
//                                                       iter->second));
        threads_.create_thread(boost::bind(&Process::run, iter->second));
//        processThreads_.insert(ProcessThreadMap::value_type(id, t));
    }

    if(block)
        threads_.join_all();
}

void ApplicationImpl::activate(bool block)
{
    BOOST_FOREACH(ProcessMap::value_type &item, processes_)
    {
        string id = item.first;
        Process *process = item.second;
        if(process->getStatus() != Process::running)
        {
            thread *t = threads_.create_thread(boost::bind(&Process::run, process));
            processThreads_.insert(ProcessThreadMap::value_type(id, t));
        }
    }

    if(block)
        threads_.join_all();
}

void ApplicationImpl::deactivate(const string &id)
{
    ProcessMap::iterator iter = processes_.find(id);
    if(iter != processes_.end() &&
       iter->second->getStatus() == Process::running)
    {
        iter->second->interrupt();
        processThreads_.erase(iter->first);
    }
}

void ApplicationImpl::deactivate()
{
    BOOST_FOREACH(ProcessMap::value_type &item, processes_)
    {
        string id  = item.first;
        Process *process = item.second;
        if(process->getStatus() == Process::running)
        {
            process->interrupt();
            processThreads_.erase(id);
        }
    }
}

// Space ---------------------------------------------------------
int ApplicationImpl::joinSpace(const string &spaceType,
                               const string &spaceId,
                               const string &nodeId,
                               const string &dir)
{
    SpaceBuilderMap::iterator iter = SpaceBuilder::Builders_.find(spaceType);
    if(iter == SpaceBuilder::Builders_.end())
        return E_SPACEBUILDER_NOT_FOUND;

    SpaceBuilder *builder = iter->second;
    Space *space = builder->build(spaceId, nodeId, dir);
    spaces_.insert(SpaceMap::value_type(spaceId, space));
    return E_OK;
}

Space& ApplicationImpl::getSpace(const string &spaceId)
{
    return *spaces_.at(spaceId);
}

}
