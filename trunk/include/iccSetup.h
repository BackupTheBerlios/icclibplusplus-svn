#ifndef _H_iccSetup_H_
#define _H_iccSetup_H_

// Define as 1 to use namespace
#define USE_ICC_LIB_NAMESPACE	1

#if USE_ICC_LIB_NAMESPACE == 1
#	define ICC_LIB_NAMESPACE		icc
#	define USING_ICC_LIB_NAMESPACE	using namespace ICC_LIB_NAMESPACE;
#	define ICC_LIB_NAMESPACE_PREFIX	ICC_LIB_NAMESPACE::
#	define ICC_LIB_NAMESPACE_START	namespace ICC_LIB_NAMESPACE {
#	define ICC_LIB_NAMESPACE_END	}
#else
#	define ICC_LIB_NAMESPACE
#	define USING_ICC_LIB_NAMESPACE
#	define ICC_LIB_NAMESPACE_PREFIX
#	define ICC_LIB_NAMESPACE_START
#	define ICC_LIB_NAMESPACE_END
#endif

#endif//_H_iccSetup_H_


