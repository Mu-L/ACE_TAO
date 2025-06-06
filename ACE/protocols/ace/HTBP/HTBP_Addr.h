// -*- C++ -*-

//=============================================================================
/**
 *  @file    HTBP_Addr.h
 *
 *  @author Phil Mesnier
 */
//=============================================================================

#ifndef ACE_HTBP_ADDR_H
#define ACE_HTBP_ADDR_H
#include /**/ "ace/pre.h"

#include "HTBP_Export.h"

#if !defined (ACE_LACKS_PRAGMA_ONCE)
# pragma once
#endif /* ACE_LACKS_PRAGMA_ONCE */

#include "ace/INET_Addr.h"
#include "ace/Synch.h"
#include "ace/SString.h"

ACE_BEGIN_VERSIONED_NAMESPACE_DECL

namespace ACE
{
  namespace HTBP
  {
    /**
     * @class Addr
     *
     * @brief Defines the member functions of the pure virtual class
     * Addr
     *
     * This class derives from ACE_INET_Addr. It is the base class for
     * the Inside, Proxy and Outside classes
     */
    class HTBP_Export Addr : public ACE_INET_Addr
    {
    public:
      /// Constructor
      Addr () = default;

      Addr (const Addr &) = default;
      Addr (Addr&&) = default;
      Addr& operator= (const Addr&) = default;
      Addr& operator= (Addr&&) = default;

      /// Create an Addr suitable for use on the inside of a firewall this
      /// take a string used to populate the htid_ member. With this address,
      /// the IP addr form is ignored.
      Addr (const char *htid);

      /// Initialize an Addr for the outside of a firewall. In this form,
      /// the htid_ is an empty string and the arguments are passed to the
      /// base address type.
      Addr (u_short port_number,
            const char host_name[],
            int address_family = AF_UNSPEC);

      /// Destructor
      ~Addr () override = default;

      int set (u_short port,
               const char host [],
               const char *htid);

      /// Methods to help convert the OutSide_Addr to a String
      /// and vice versa
      int addr_to_string (ACE_TCHAR buffer[],
                          size_t size,
                          int ipaddr_format = 1) const override;
      int string_to_addr (const char address[],
                          int address_family = AF_UNSPEC) override;

      int set_htid(const char *htid);
      const char *get_htid () const;

    private:
      /// HTID - web-obtained unique-identifier
      ACE_CString htid_;
    };
  }
}

ACE_END_VERSIONED_NAMESPACE_DECL

#include /**/ "ace/post.h"
#endif /* ACE_HTBP_ADDR_H */
