// $Id$

#ifndef TAO_POA_MACROS_H
#define TAO_POA_MACROS_H
#include "ace/pre.h"

#include "tao/try_macros.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

// Convenient macro for testing for deadlock, as well as for detecting
// when mutexes fail.
#define TAO_POA_GUARD(MUTEX,OBJ,LOCK) \
  ACE_GUARD_THROW_EX(MUTEX,OBJ,LOCK,CORBA::OBJ_ADAPTER ())

#define TAO_POA_GUARD_RETURN(MUTEX,OBJ,LOCK,RETURN) \
  ACE_GUARD_THROW_EX(MUTEX,OBJ,LOCK,CORBA::OBJ_ADAPTER ()); \
  ACE_CHECK_RETURN (RETURN)

#define TAO_POA_WRITE_GUARD(MUTEX,OBJ,LOCK) \
  ACE_WRITE_GUARD_THROW_EX(MUTEX,OBJ,LOCK,CORBA::OBJ_ADAPTER ())

#define TAO_POA_READ_GUARD(MUTEX,OBJ,LOCK) \
  ACE_READ_GUARD_THROW_EX(MUTEX,OBJ,LOCK,CORBA::OBJ_ADAPTER ())

#define TAO_POA_WRITE_GUARD_RETURN(MUTEX,OBJ,LOCK) \
  ACE_WRITE_GUARD_THROW_EX(MUTEX,OBJ,LOCK,CORBA::OBJ_ADAPTER ()); \
  ACE_CHECK_RETURN (RETURN)

#define TAO_POA_READ_GUARD_RETURN(MUTEX,OBJ,LOCK) \
  ACE_READ_GUARD_THROW_EX(MUTEX,OBJ,LOCK,CORBA::OBJ_ADAPTER ()); \
  ACE_CHECK_RETURN (RETURN)

#include "ace/post.h"
#endif /* TAO_POA_MACROS_H */
