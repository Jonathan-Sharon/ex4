#include "MapCreator.h"

MapCreator::MapCreator::MapCreator()
    : m_readMapCreate{
          {std::string_view{"FIRST READ"}, std::make_shared<ThreadPool::FirstReadCreator>()},
          {std::string_view{"SECOND READ"}, std::make_shared<ThreadPool::SecondReadCreator>()}},
      m_writeMapCreate{
          {std::string_view{"FIRST WRITE"},std::make_shared<ThreadPool::FirstWriteCreator>()},
          {std::string_view{"SECOND WRITE"}, std::make_shared<ThreadPool::SecondWriteCreator>()},
          {std::string_view{"ERROR WRITE"}, std::make_shared<ThreadPool::ErrorWriteCreator>()}},

      m_operateMapCreate{
          {std::string_view{"FIND-GRAPH-PATH DFS"}, std::make_shared<ThreadPool::DFSCreator>()},
          {std::string_view{"FIND-GRAPH-PATH BFS"}, std::make_shared<ThreadPool::BFSCreator>()},
          {std::string_view{"FIND-GRAPH-PATH BESTFS"}, std::make_shared<ThreadPool::BestFSCreator>()},
          {std::string_view{"FIND-GRAPH-PATH ASTAR"}, std::make_shared<ThreadPool::AStarCreator>()}}

{
}

const std::shared_ptr<ThreadPool::ReadCreator>
MapCreator::MapCreator::atReadMap(const std::string_view &str) const
{
    return m_readMapCreate.at(str);
}

const std::shared_ptr<ThreadPool::WriteCreator>
MapCreator::MapCreator::atWriteMap(const std::string_view &str) const
{
    return m_writeMapCreate.at(str);
}

const std::shared_ptr<ThreadPool::OperateCreator>
MapCreator::MapCreator::atOperateMap(const std::string_view &str) const
{
    return m_operateMapCreate.at(str);
}
