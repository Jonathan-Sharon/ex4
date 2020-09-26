#pragma once

#include "OperateCreator.h"
#include "ReadCreator.h"
#include "WriteCreator.h"

#include <map>
#include <string_view>

namespace ThreadPool {
class ReadCreator;
class WriteCreator;
class OperateCreator;
} // namespace ThreadPool

namespace MapCreator {
class MapCreator {
public:
  /**
   * @brief Construct a new Map Creator object
   *
   */
  explicit MapCreator();

  /**
   * @brief get the creator object by giving a string key
   *
   * @param str the key string
   * @return const std::shared_ptr<ThreadPool::ReadCreator>
   */
  const std::shared_ptr<ThreadPool::ReadCreator>
  atReadMap(const std::string_view &str) const;

  /**
   * @brief get the creator object by giving a string key
   *
   * @param str the key string
   * @return const std::shared_ptr<ThreadPool::WriteCreator>
   */
  const std::shared_ptr<ThreadPool::WriteCreator>
  atWriteMap(const std::string_view &str) const;

  /**
   * @brief get the creator object by giving a string key
   *
   * @param str the key string
   * @return const std::shared_ptr<ThreadPool::OperateCreator>
   */
  const std::shared_ptr<ThreadPool::OperateCreator>
  atOperateMap(const std::string_view &str) const;

private:
  const std::map<std::string_view, std::shared_ptr<ThreadPool::ReadCreator>>
      m_readMapCreate;
  const std::map<std::string_view, std::shared_ptr<ThreadPool::WriteCreator>>
      m_writeMapCreate;
  const std::map<std::string_view, std::shared_ptr<ThreadPool::OperateCreator>>
      m_operateMapCreate;
};
} // namespace MapCreator