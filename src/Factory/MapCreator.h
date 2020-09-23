#pragma once

#include "ReadCreator.h"
#include "WriteCreator.h"
#include "OperateCreator.h"

#include <map>
#include <string_view>

namespace ThreadPool{
    class ReadCreator;
    class WriteCreator;
    class OperateCreator;
}


namespace MapCreator
{
    class MapCreator
    {
    public:
        explicit MapCreator();
        const std::shared_ptr<ThreadPool::ReadCreator> atReadMap(const std::string_view &str) const;
        const std::shared_ptr<ThreadPool::WriteCreator> atWriteMap(const std::string_view &str) const;
        const std::shared_ptr<ThreadPool::OperateCreator> atOperateMap(const std::string_view &str) const;

    private:
        const std::map<std::string_view, std::shared_ptr<ThreadPool::ReadCreator>> m_readMapCreate;
        const std::map<std::string_view, std::shared_ptr<ThreadPool::WriteCreator>> m_writeMapCreate;
        const std::map<std::string_view, std::shared_ptr<ThreadPool::OperateCreator>> m_operateMapCreate;
    };
} // namespace MapCreator