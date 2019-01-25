// std
#include <iostream> // debug

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

namespace impro
{

static Application *application_ = nullptr;

Application& Application::Initialize()
{
    if(application_ == nullptr)
        application_ = new ApplicationImpl();
    return *application_;
}

void Application::Finalize()
{
    if(application_ != nullptr)
    {
        delete application_;
        application_ = nullptr;
    }

    //
    DataType::Release();
    InterfaceCreator::Release();
    SpaceBuilder::Release();
}

Application& Application::getInstance()
{
    if(application_ == nullptr)
        application_ = new ApplicationImpl();
    return *application_;
}

void Application::releaseInstance()
{
    if(application_ != nullptr)
    {
        delete application_;
        application_ = nullptr;
    }
}

//Application& Application::getInstance()
//{
//    static ApplicationImpl application_;
//    return application_;
//}

ApplicationImpl::ApplicationImpl()
{

}

ApplicationImpl::~ApplicationImpl()
{
    // Clear Process
    for(auto &item : processes_)
    {
        Process *process = item.second;
        if(process != nullptr)
        {
            delete process;
            process = nullptr;
        }
    }
    processes_.clear();

    // Clear Space
    for(auto &item : spaces_)
    {
        Space *space = item.second;
        if(space != nullptr)
        {
            delete space;
            space = nullptr;
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

    // ToDo: bug fix... for id only
    ProcessMap::iterator iter = processes_.find(id);
    if(iter != processes_.end() &&
       iter->second->getStatus() != Process::running)
    {
        thread *t = new thread(&Process::run, iter->second);
        threads_.push_back(t);
    }

    if(block)
    {
        for (auto &thread : threads_)
        {
            if (thread->joinable())
                thread->join();
        }
    }
}

void ApplicationImpl::activate(bool block)
{
     // ToDo: bug fix
    for(auto &item : processes_)
    {
        string id = item.first;
        Process *process = item.second;
        if(process->getStatus() != Process::running)
        {
            thread *t = new thread(&Process::run, process);
            threads_.push_back(t);
        }
    }

    if(block)
    {
        for (auto &thread : threads_)
        {
            if (thread->joinable())
                thread->join();
        }
    }
}

void ApplicationImpl::deactivate(const string &id)
{
    ProcessMap::iterator iter = processes_.find(id);
    if(iter != processes_.end() &&
       iter->second->getStatus() == Process::running)
    {
        iter->second->interrupt();
    }
}

void ApplicationImpl::deactivate()
{
    // ToDo: bug fix
    for(auto &item : processes_)
    {
        string id  = item.first;
        Process *process = item.second;
        if(process->getStatus() == Process::running)
        {
            process->interrupt();
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
