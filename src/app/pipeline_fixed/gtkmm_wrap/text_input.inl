// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/proto.inl                                                                  */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_PROTO_INL)

#define HUGH_PROTO_INL

// includes, system

#include <>

// includes, project

#include <>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>
//#if defined(HUGH_USE_TRACE) || defined(HUGH_ALL_TRACE)
//#  include <typeinfo>
//#  include <hugh/support/type_info.hpp>
//#endif

namespace hugh {
  
  // functions, inlined (inline)
  
} // namespace hugh {

#if defined(HUGH_USE_TRACE)
#  undef HUGH_USE_TRACE
#endif

#endif // #if !defined(HUGH_PROTO_INL)
