#include "MapCreator.h"

MapCreator::MapCreator::MapCreator()
    : m_readMapCreate{
          {std::string_view{"First Read"}, std::make_shared<ThreadPool::FirstReadCreator>()},
          {std::string_view{"Second Read"}, std::make_shared<ThreadPool::SecondReadCreator>()}},
      m_writeMapCreate{
          {std::string_view{"First Write"}, std::make_shared<ThreadPool::FirstWriteCreator>()},
          {std::string_view{"Second Write"}, std::make_shared<ThreadPool::SecondWriteCreator>()},
          {std::string_view{"Error Write"}, std::make_shared<ThreadPool::ErrorWriteCreator>()}},
          

      m_operateMapCreate{
          {std::string_view{"DFS"}, std::make_shared<ThreadPool::DFSCreator>()},
          {std::string_view{"BFS"}, std::make_shared<ThreadPool::BFSCreator>()},
          {std::string_view{"BestFS"}, std::make_shared<ThreadPool::BestFSCreator>()},
          {std::string_view{"AStar"}, std::make_shared<ThreadPool::AStarCreator>()}}
          
{
}

const std::shared_ptr<ThreadPool::ReadCreator>
                     MapCreator::MapCreator::atReadMap(const std::string_view &str) const{
    return m_readMapCreate.at(str);
}

const std::shared_ptr<ThreadPool::WriteCreator>
                     MapCreator::MapCreator::atWriteMap(const std::string_view &str) const{
    return m_writeMapCreate.at(str);
}

const std::shared_ptr<ThreadPool::OperateCreator>
                     MapCreator::MapCreator::atOperateMap(const std::string_view &str) const{
    return m_operateMapCreate.at(str);
}
