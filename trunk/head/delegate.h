//-------------------------------------------------------------------------
//
// Copyright (C) 2004-2005 Yingle Jia
//
// Permission to copy, use, modify, sell and distribute this software is 
// granted provided this copyright notice appears in all copies. 
// This software is provided "as is" without express or implied warranty, 
// and with no claim as to its suitability for any purpose.
//
// ns_delegateDelegate.h
//

#ifndef __ns_delegate_Delegate__
#define __ns_delegate_Delegate__

#include <stdexcept> // for std::logic_error
#include <utility> // for std::pair

// Macros for template metaprogramming

#define ns_delegate_JOIN(a, b)        ns_delegate_DO_JOIN(a, b)
#define ns_delegate_DO_JOIN(a, b)     ns_delegate_DO_JOIN2(a, b)
#define ns_delegate_DO_JOIN2(a, b)    a##b

#define ns_delegate_MAKE_PARAMS1_0(t)
#define ns_delegate_MAKE_PARAMS1_1(t)    t##1
#define ns_delegate_MAKE_PARAMS1_2(t)    t##1, ##t##2
#define ns_delegate_MAKE_PARAMS1_3(t)    t##1, ##t##2, ##t##3
#define ns_delegate_MAKE_PARAMS1_4(t)    t##1, ##t##2, ##t##3, ##t##4
#define ns_delegate_MAKE_PARAMS1_5(t)    t##1, ##t##2, ##t##3, ##t##4, ##t##5
#define ns_delegate_MAKE_PARAMS1_6(t)    t##1, ##t##2, ##t##3, ##t##4, ##t##5, ##t##6

#define ns_delegate_MAKE_PARAMS2_0(t1, t2)
#define ns_delegate_MAKE_PARAMS2_1(t1, t2)   t1##1 t2##1
#define ns_delegate_MAKE_PARAMS2_2(t1, t2)   t1##1 t2##1, t1##2 t2##2
#define ns_delegate_MAKE_PARAMS2_3(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3
#define ns_delegate_MAKE_PARAMS2_4(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3, t1##4 t2##4
#define ns_delegate_MAKE_PARAMS2_5(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3, t1##4 t2##4, t1##5 t2##5
#define ns_delegate_MAKE_PARAMS2_6(t1, t2)   t1##1 t2##1, t1##2 t2##2, t1##3 t2##3, t1##4 t2##4, t1##5 t2##5, t1##6 t2##6

#define ns_delegate_MAKE_PARAMS1(n, t)         ns_delegate_JOIN(ns_delegate_MAKE_PARAMS1_, n) (t)
#define ns_delegate_MAKE_PARAMS2(n, t1, t2)    ns_delegate_JOIN(ns_delegate_MAKE_PARAMS2_, n) (t1, t2)

namespace ns_delegate {

class InvalidCallException : public std::logic_error
{
public:
    InvalidCallException() : std::logic_error("An empty delegate is called")
    {
    }
};

template <class T>
inline static T _HandleInvalidCall()
{
    throw InvalidCallException();
}

template <>
inline static void _HandleInvalidCall<void>()
{
}

template <class TSignature>
class Delegate; // no body

} // namespace ns_delegate

// Specializations

#define ns_delegate_DELEGATE_NUM_ARGS	0 // Delegate<R ()>
#include "DelegateTemplate.h"
#undef ns_delegate_DELEGATE_NUM_ARGS

#define ns_delegate_DELEGATE_NUM_ARGS	1 // Delegate<R (T1)>
#include "DelegateTemplate.h"
#undef ns_delegate_DELEGATE_NUM_ARGS

#define ns_delegate_DELEGATE_NUM_ARGS	2 // Delegate<R (T1, T2)>
#include "DelegateTemplate.h"
#undef ns_delegate_DELEGATE_NUM_ARGS

#define ns_delegate_DELEGATE_NUM_ARGS	3 // Delegate<R (T1, T2, T3)>
#include "DelegateTemplate.h"
#undef ns_delegate_DELEGATE_NUM_ARGS

#define ns_delegate_DELEGATE_NUM_ARGS	4 // Delegate<R (T1, T2, T3, T4)>
#include "DelegateTemplate.h"
#undef ns_delegate_DELEGATE_NUM_ARGS

#define ns_delegate_DELEGATE_NUM_ARGS	5 // Delegate<R (T1, T2, T3, T4, T5)>
#include "DelegateTemplate.h"
#undef ns_delegate_DELEGATE_NUM_ARGS

#define ns_delegate_DELEGATE_NUM_ARGS	6 // Delegate<R (T1, T2, T3, T4, T5, T6)>
#include "DelegateTemplate.h"
#undef ns_delegate_DELEGATE_NUM_ARGS

#endif // #ifndef __ns_delegate_Delegate__
