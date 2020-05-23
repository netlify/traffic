#include <traffic/paths.hpp>
#include <ts/ts.h>

namespace traffic::path {

std::filesystem::path const& install () noexcept {
  static std::filesystem::path instance { TSInstallDirGet() };
  return instance;
}

std::filesystem::path const& runtime () noexcept {
  static std::filesystem::path instance { TSRuntimeDirGet() };
  return instance;
}

std::filesystem::path const& config () noexcept {
  static std::filesystem::path instance { TSConfigDirGet() };
  return instance;
}

std::filesystem::path const& plugin () noexcept {
  static std::filesystem::path instance { TSPluginDirGet() };
  return instance;
}

} /* namespace traffic::path */
