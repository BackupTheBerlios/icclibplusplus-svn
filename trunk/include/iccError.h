#ifndef _H_iccError_H_
#define _H_iccError_H_

#include "iccSetup.h"

ICC_LIB_NAMESPACE_START

enum iccError{
	iccErrorNone				= 0,
	iccErrorRead,
	iccErrorWrite,
	iccErrorMemory,
	iccErrorNotEnoughMemory,
	iccErrorIOError,
	iccErrorBadFileFormat,
	iccErrorBadParameter,
	iccErrorNoData,		
	iccErrorTagNotFound,
	iccErrorBadTagType,
	iccErrorUnknown				= 0xFFFF	
};

ICC_LIB_NAMESPACE_END

#endif//_H_iccError_H_

