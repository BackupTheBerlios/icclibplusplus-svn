#ifndef _H_iccBasicNumericTypes_H_
#define _H_iccBasicNumericTypes_H_

#include "iccNumberFixed.h"

ICC_LIB_NAMESPACE_START

typedef unsigned char		iccNumberUInt8;
typedef	unsigned short		iccNumberUInt16;
typedef unsigned long		iccNumberUInt32;
typedef unsigned long long	iccNumberUInt64;

typedef char				iccNumberSInt8;
typedef short				iccNumberSInt16;
typedef long				iccNumberSInt32;
typedef long long			iccNumberSInt64;

typedef char				iccOneByteType;
typedef short				iccTwoByteType;
typedef long				iccFourByteType;
typedef long long			iccEightByteType;

enum
{
  iccNormalizedDeviceMin	= 0,
  iccNormalizedDeviceMax	= 0xFFFF
};

struct iccResponse16Number
{
  iccNumberUInt16		normalizedDevice;
  iccNumberUInt8		reserved[2];	// must be zero
  iccNumberS15Fixed16	measurementValue;
};

ICC_LIB_NAMESPACE_END

#endif//_H_iccBasicNumericTypes_H_

