#include <traffic/plugin.hpp>

#include <traffic/constants.hpp>
#include <ts/ts.h>


[[gnu::visibility("default")]] void TSPluginInit (int, char const**) {
  TSPluginRegistrationInfo info {
    traffic::plugin::name(),
    traffic::plugin::vendor(),
    traffic::plugin::email()
  };
  if (TSPluginRegister(&info) != traffic::success) {
    TSError("[%s] Plugin registration failed", traffic::plugin::name());
  }
  // traffic::plugin::initialize(apex::arguments(argc, argv));
}
