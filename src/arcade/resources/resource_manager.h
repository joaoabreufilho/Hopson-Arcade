/*
 * Used for Documentation and Educational Purposes.
 * Public Description: This is a collection of small aracde-y games, created
 * using C++17 and SFML
 *
 * Hopson-Arcade {https://github.com/Hopson97}
 * GPL License
 */
/**
 * @file resource_manager.h
 * @brief Resource file handler.
 *
 * - \subpage Subsystem: Arcade Resources
 *
 * \date Jun 2021
 */
/** @addtogroup arcade_resources */
/** @{ */
#pragma once

#include <string>
#include <unordered_map>

/**
 * @class ResourceHolder
 * @brief Holds all the resources of the game
 */
template <typename Resource>
class ResourceManager {
 public:
  ResourceManager(const std::string& folder, const std::string& extention)
      : m_folder("res/" + folder + "/"), m_extention("." + extention) {}

  const Resource& get(const std::string& name) {
    if (!exists(name)) {
      add(name);
    }

    return m_resources.at(name);
  }

  bool exists(const std::string& name) const {
    return m_resources.find(name) != m_resources.end();
  }

  void add(const std::string& name) {
    Resource r;

    // if the resource fails to load, then it adds a default "fail"
    // resource
    if (!r.loadFromFile(getFullFilename(name))) {
      Resource fail;
      fail.loadFromFile(m_folder + "_fail_" + m_extention);
      m_resources.insert(std::make_pair(name, fail));
    } else {
      m_resources.insert(std::make_pair(name, r));
    }
  }

 private:
  std::string getFullFilename(const std::string& name) {
    return m_folder + name + m_extention;
  }

  const std::string m_folder;
  const std::string m_extention;

  std::unordered_map<std::string, Resource> m_resources;
};
/** @} */