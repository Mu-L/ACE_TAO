
//=============================================================================
/**
 *  @file    Time_Value_Test.cpp
 *
 *    This is a simple test of ACE_Time_Value.  No command line arguments
 *    are needed to run the test.
 *
 *  @author Prashant Jain <pjain@cs.wustl.edu> and David Levine <levine@cs.wustl.edu>
 */
//=============================================================================

// Note, for this test the config.h file *must* come first!
#include "ace/config-all.h"

#include "test_config.h"
#include "ace/ACE.h"
#include "ace/Time_Value.h"
#include "ace/Numeric_Limits.h"
#include <sstream>
#include <type_traits>

int
run_main (int, ACE_TCHAR *[])
{
  int ret = 0;

  ACE_START_TEST (ACE_TEXT ("Time_Value_Test"));

  ACE_Time_Value tv1;
  ACE_Time_Value tv2 (2);
  ACE_Time_Value tv3 (100U);
  ACE_Time_Value tv4 (1, 1000000);
  ACE_Time_Value tv5 (2UL);
  ACE_Time_Value tv6 (1, -1000000);
  ACE_Time_Value tv7 (static_cast<long> (2.0));

  // Beware!  2.5 gets truncated to 2!
  // NOTE:  this is intended to show what happens with
  // ACE_Time_Value (2.5).  Some compilers, such as g++ 2.7.2.3,
  // actually warn about it without the case.
  ACE_Time_Value tv8 (static_cast <long> (2.5));

  ACE_Time_Value first;
  ACE_Time_Value last(ACE_Time_Value::max_time);
  first = last;
  ACE_TEST_ASSERT (first == last);

  // Test assignment operator, tv9 and tv6 must be the same after this
  ACE_Time_Value tv9;
  tv9 = tv6;

  ACE_TEST_ASSERT (tv1 == ACE_Time_Value (0));
  ACE_TEST_ASSERT (tv2 < tv3);
  ACE_TEST_ASSERT (tv2 <= tv2);
  ACE_TEST_ASSERT (tv2 >= tv4);
  ACE_TEST_ASSERT (tv5 >= tv6);
  ACE_TEST_ASSERT (tv2 == ACE_Time_Value (1, 1000000));
  ACE_TEST_ASSERT (tv5 == tv4);
  ACE_TEST_ASSERT (tv2 == tv4);
  ACE_TEST_ASSERT (tv1 != tv2);
  ACE_TEST_ASSERT (tv6 == tv1);
  ACE_TEST_ASSERT (tv5 == tv7);
  ACE_TEST_ASSERT (tv7 == tv8); // That's right!  See above . . .
  ACE_TEST_ASSERT (tv9 == tv6);

  ACE_Time_Value tv10 (1);

  ACE_TEST_ASSERT (tv10.sec() == 1);

  // test multiplication by double
  // test simple multiplication
  tv1.set (1, 1);
  tv2.set (2, 2);
  tv1 *= 2.0;
  ACE_TEST_ASSERT (tv1 == tv2);
  tv1.set (1, 1);
  tv2.set (static_cast<time_t> (-2), static_cast<suseconds_t> (-2));
  tv1 *= -2.0;
  ACE_TEST_ASSERT (tv1 == tv2);

  // test usec shift
  tv1.set (1, 999999);
  tv2.set (19, 999990);
  tv1 *= 10.0;
  ACE_TEST_ASSERT ( tv1 == tv2);
  tv1.set (1, 999999);
  tv2.set (static_cast<time_t> (-19), -999990);
  tv1 *= -10.0;
  ACE_TEST_ASSERT (tv1 == tv2);

  // Test correct msec() convert; also checks for compile error reported in
  // Bugzilla 3336.
  ACE_Time_Value msec_test (42, 555000);
  ACE_UINT64 ms = 0;
  msec_test.msec (ms);
  if (ms != 42555)
    {
       ACE_ERROR ((LM_ERROR,
                     ACE_TEXT ("msec test failed: %Q should be 42555\n"),
                     ms));
       ++ret;
    }

  ms = 0;
  ms = msec_test.get_msec ();
  if (ms != 42555)
    {
       ACE_ERROR ((LM_ERROR,
                     ACE_TEXT ("get_msec test failed: %Q should be 42555\n"),
                     ms));
       ++ret;
    }
  ACE_Time_Value const msec_test2 (42, 555000);
  ms = 0;
  msec_test2.msec (ms);
  if (ms != 42555)
    {
       ACE_ERROR ((LM_ERROR,
                     ACE_TEXT ("msec const test failed: %Q should be 42555\n"),
                     ms));
       ++ret;
    }

  // Test setting double values
  ACE_Time_Value d1(10, 500000);
  ACE_Time_Value d2;
  d2.set(10.5);

  ACE_Time_Value d3(-10, -500000);
  ACE_Time_Value d4;
  d4.set(-10.5);

  ACE_TEST_ASSERT (d1 == d2);
  ACE_TEST_ASSERT (d3 == d4);
  ACE_TEST_ASSERT (d1 + d3 == ACE_Time_Value::zero);
  ACE_TEST_ASSERT (d3 + d1 == ACE_Time_Value::zero);
  ACE_TEST_ASSERT (d2 + d4 == ACE_Time_Value::zero);
  ACE_TEST_ASSERT (d4 + d2 == ACE_Time_Value::zero);
  ACE_TEST_ASSERT (ACE_Time_Value::zero - d1 = d3);
  ACE_TEST_ASSERT (ACE_Time_Value::zero - d3 = d1);
  ACE_TEST_ASSERT (ACE_Time_Value::zero - d2 = d4);
  ACE_TEST_ASSERT (ACE_Time_Value::zero - d4 = d2);

  ACE_Time_Value d5;
  d5.set(DBL_MAX);
  ACE_TEST_ASSERT (d5 == ACE_Time_Value::max_time);
  ACE_TEST_ASSERT (ACE_Time_Value::max_time.sec () != 0);
  ACE_TEST_ASSERT (ACE_Time_Value::max_time.usec () != -1);

  // Test performance of normalize()
  ACE_Time_Value v1(ACE_Numeric_Limits<time_t>::max(),
                    ACE_Numeric_Limits<suseconds_t>::max());
  ACE_Time_Value v2(ACE_Numeric_Limits<time_t>::min(),
                   ACE_Numeric_Limits<suseconds_t>::min());
  ACE_Time_Value v3(ACE_Numeric_Limits<time_t>::max(),
                    ACE_Numeric_Limits<suseconds_t>::min());
  ACE_Time_Value v4(ACE_Numeric_Limits<time_t>::min(),
                    ACE_Numeric_Limits<suseconds_t>::max());

  v1.set(ACE_Numeric_Limits<time_t>::max(),
         ACE_Numeric_Limits<suseconds_t>::max());
  v2.set(ACE_Numeric_Limits<time_t>::min(),
         ACE_Numeric_Limits<suseconds_t>::min());
  v3.set(ACE_Numeric_Limits<time_t>::max(),
         ACE_Numeric_Limits<suseconds_t>::min());
  v4.set(ACE_Numeric_Limits<time_t>::min(),
         ACE_Numeric_Limits<suseconds_t>::max());

  v1.set(DBL_MAX);

  // Test setting from ACE_UINT64
  ms = 42555;
  ACE_Time_Value msec_test3;
  msec_test3.set_msec (ms);
  if (msec_test3.sec () != 42)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("set_msec test failed: %d secs should be 42\n"),
                  msec_test3.sec ()));
      ++ret;
    }
  if (msec_test3.usec () != 555000)
    {
      ACE_ERROR ((LM_ERROR,
                  ACE_TEXT ("set_msec test failed: %d usecs should be 555000\n"),
                  msec_test3.usec ()));
      ++ret;
    }

  std::ostringstream ost;
  ost << ACE_Time_Value(1);
  ACE_TEST_ASSERT( ost.str() == "1" );
  ost.str("");
  ost << ACE_Time_Value(1,1);
  ACE_TEST_ASSERT( ost.str() == "1.000001" );
  ost.str("");
  ost << ACE_Time_Value(static_cast<time_t>(-1),-1);
  ACE_TEST_ASSERT( ost.str() == "-1.000001" );
  ost.str("");
  ost << ACE_Time_Value(0,1);
  ACE_TEST_ASSERT( ost.str() == "0.000001" );
  ost.str("");
  ost << ACE_Time_Value(0,-1);
  ACE_TEST_ASSERT( ost.str() == "-0.000001" );
  ost.str("");
  ost << ACE_Time_Value();
  ACE_TEST_ASSERT( ost.str() == "0" );

  if (sizeof(time_t) < 8)
    {
      if (std::is_signed<time_t>::value)
        {
          ACE_ERROR ((LM_ERROR,
                      ACE_TEXT ("time_t is 32bit signed, this platform will have problems after 2038\n")));
          ++ret;
        }
      else
        {
          ACE_DEBUG ((LM_DEBUG,
                      ACE_TEXT ("time_t is 32bit unsigned, this platform will have problems after 2106\n")));
        }
    }
  else
    {
      ACE_DEBUG ((LM_DEBUG,
                  ACE_TEXT ("time_t is at least 64bit, this platform will not have problems after 2038\n")));
    }

  ACE_END_TEST;

  return ret;
}
