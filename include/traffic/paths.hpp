#ifndef TRAFFIC_PATHS_HPP
#define TRAFFIC_PATHS_HPP

#include <filesystem>

// These are like the various TS<Path>DirGet() functions, but returned
// as std::filesystem::path, and are cached on first call (thus, we do
// not allocate every time they are used, only the first time)

namespace traffic::path {

std::filesystem::path const& install () noexcept;
std::filesystem::path const& runtime () noexcept;
std::filesystem::path const& config () noexcept;
std::filesystem::path const& plugin () noexcept;

} /* namespace traffic::path */

#endif /* TRAFFIC_PATHS_HPP */
