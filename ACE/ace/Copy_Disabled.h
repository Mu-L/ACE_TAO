// -*- C++ -*-

//===========================================================================
/**
 * @file Copy_Disabled.h
 *
 * @author Carlos O'Ryan <coryan@uci.edu>
 */
//===========================================================================

#ifndef ACE_COPY_DISABLED_H
#define ACE_COPY_DISABLED_H

#include /**/ "ace/pre.h"

#include /**/ "ace/config-lite.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

/**
 * @class ACE_Copy_Disabled
 *
 * @brief Helper class to disable copy construction and assignment
 *
 * Classes used to control OS and other resources are not "canonical",
 * i.e. they have their copy constructor and assignment operators
 * disabled.
 * This is often done by making the copy constructor and assignment
 * operators private, effectively disallowing copying by clients of
 * the class (including derived classes).  If the copy constructor and
 * assignment operators are left unimplemented then the class itself
 * cannot make any copies of its instances, because it would result in
 * link errors.
 *
 * To use this class simply use private inheritance:
 *
 * class Foo : private ACE_Copy_Disabled
 * {
 * // code here
 * };
 *
 * @deprecated This class is deprecated. Instead of using inheritance,
 * directly delete copy operations in your class:
 *
 * class Foo
 * {
 * public:
 *   Foo(const Foo&) = delete;
 *   Foo(Foo&&) = delete;
 *   Foo& operator=(const Foo&) = delete;
 *   Foo& operator=(Foo&&) = delete;
 * };
 */
class [[deprecated]] ACE_Copy_Disabled
{
public:
  /// Default constructor
  ACE_Copy_Disabled () = default;

private:
  ACE_Copy_Disabled (const ACE_Copy_Disabled &) = delete;
  ACE_Copy_Disabled (ACE_Copy_Disabled &&) = delete;
  ACE_Copy_Disabled &operator= (const ACE_Copy_Disabled &) = delete;
  ACE_Copy_Disabled &operator= (ACE_Copy_Disabled &&) = delete;
};

ACE_END_VERSIONED_NAMESPACE_DECL

#include /**/ "ace/post.h"

#endif /* ACE_COPY_DISABLED_H */
