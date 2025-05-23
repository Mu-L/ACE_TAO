// -*- C++ -*-
#include "ace/OS_NS_stropts.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

ACE_INLINE
ACE_IPC_SAP::~ACE_IPC_SAP ()
{
  // ACE_TRACE ("ACE_IPC_SAP::~ACE_IPC_SAP");
}

ACE_INLINE ACE_HANDLE
ACE_IPC_SAP::get_handle () const
{
  ACE_TRACE ("ACE_IPC_SAP::get_handle");
  return this->handle_;
}

// Used to set the underlying handle_.

ACE_INLINE void
ACE_IPC_SAP::set_handle (ACE_HANDLE handle)
{
  ACE_TRACE ("ACE_IPC_SAP::set_handle");
  this->handle_ = handle;
}

// Provides access to the ACE_OS::ioctl system call.

ACE_INLINE int
ACE_IPC_SAP::control (int cmd, void *arg) const
{
  ACE_TRACE ("ACE_IPC_SAP::control");
  return ACE_OS::ioctl (this->handle_, static_cast<ACE_IOCTL_TYPE_ARG2> (cmd), arg);
}

ACE_END_VERSIONED_NAMESPACE_DECL
