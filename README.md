# Overview

This is a more lifetime/scoped focused approach to wrapping the Apache
TrafficServer API. If anything, it's intended to replace the atscppapi, which
allocates more than it needs to, and is unfriendly to modern C++ techniques.
This makes it harder to integrate other languages like Rust. By using this
approach, we can more 'safely' move between C++ and Rust code in the same
plugin.

Please note, this library has not yet been tested in every aspect of its
development. Expect high churn/API changes.
