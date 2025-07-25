/**
 * This program checks if the compiler / platform supports strongly
 * typed enums
 */

#include "test_config.h"

#include <limits>
#include <stdint.h>
#include <ostream>

namespace CORBA {
  // First forward declare TCKind, this is legal with C++11
  enum class TCKind : uint32_t;

  enum class TCKind : uint32_t
  {
    tk_null,
    tk_void,
    tk_event
  };// TCKind

  // And another forward declared TCKind, after it has been
  // declared
  enum class TCKind : uint32_t;
}

std::ostream& operator<< (std::ostream& strm, CORBA::TCKind _enumerator)
{
  switch (_enumerator) {
    case CORBA::TCKind::tk_null: return strm << "CORBA::TCKind::tk_null"; break;
    case CORBA::TCKind::tk_void: return strm << "CORBA::TCKind::tk_void"; break;
    default: return strm;
  }
}

int
run_main (int, ACE_TCHAR *[])
{
  ACE_START_TEST (ACE_TEXT("Compiler_Features_16_Test"));

  ACE_DEBUG ((LM_INFO,
              ACE_TEXT ("Strongly typed enums work.\n")));

  ACE_END_TEST;

  return 0;
}
