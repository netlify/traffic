#ifndef TRAFFIC_PLUGIN_HPP
#define TRAFFIC_PLUGIN_HPP

/* This is the public API that users must hook into */
/* Implementing these is *required* at a minimum */
// NOTE: Until initialize is implemented, TSPluginInit will be provided by
// plugins
namespace traffic::plugin {

extern char const* vendor () noexcept;
extern char const* email () noexcept;
extern char const* name () noexcept;

//extern void initialize (apex::arguments);

} /* namespace plugin */

#endif /* TRAFFIC_PLUGIN_HPP */
