Overview
========

Netlify Traffic is a C++20 wrapper around the Apache TrafficServer C API. It's
goal is to replace the atscppapi, which allocates more than it needs to and is
unfriendly to modern C++ techniques. This also makes it harder to do cross
language support with other languages, such as Rust.

The top-level namespace is simply :expr:`traffic`, and all headers are
available via a :file:`<traffic/{filename}.hpp>` naming convention.

Netlify Traffic current depends on *both* `netlify::apex_
<https://github.com/netlify/apex>_` and `netlify::aegis
<https://github.com/netlify/aegis>`_. Both are automatically fetched during the
build process.

.. toctree::
   mutex
