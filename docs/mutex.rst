Mutex Objects
=============

There are two provided *mutex* types within Netlify Traffic. One is an owning
wrapper around :struct:`TSMutex`, while the other is a borrowed handle to a
:struct:`TSMutex`. Both follow the C++ standard's definition of the Lockable_
named requirement. This means that :struct:`traffic::mutex` and
:struct:`traffic::borrowed_mutex` are usable with :expr:`std::lock_guard` and
:expr:`std::scoped_lock`.

.. namespace:: traffic

.. struct:: mutex

   .. type:: using native_handle_type = TSMutex

   .. function:: mutex (native_handle_type) noexcept

   .. function:: mutex () noexcept

   .. function:: explicit operator bool () const noexcept

   .. function:: bool try_lock () noexcept

   .. function:: void unlock () noexcept

   .. function:: void lock () noexcept

   .. function:: native_handle_type native_handle () const noexcept

.. struct:: borrowed_mutex

   .. type:: using native_handle_type = TSMutex

   .. function:: borrowed_mutex (TSCont) noexcept

.. _Lockable: https://en.cppreference.com/w/cpp/named_req/Lockable
