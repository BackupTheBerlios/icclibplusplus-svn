#ifndef _H_iccNumberXYZ_H_
#define _H_iccNumberXYZ_H_

#include "iccObject.h"
#include "iccNumberFixed.h"
#include <istream>
#include <ostream>

ICC_LIB_NAMESPACE_START

class iccNumberXYZ:	public iccObject
{
public:
    							iccNumberXYZ(void)
    							:m_CIE_X(),m_CIE_Y(),m_CIE_Z()
    							{}

friend	void					operator>>(std::istream& inStream,iccNumberXYZ& outNumber);
friend	std::ostream&			operator<<(std::ostream& outStream,const iccNumberXYZ& inNumber);
   		iccNumberXYZ&			operator=(const iccNumberXYZ &inNumber)
                				{
									if(this != &inNumber)
	                				{
										m_CIE_X = inNumber.m_CIE_X;
                            			m_CIE_Y = inNumber.m_CIE_Y;
                            			m_CIE_Z = inNumber.m_CIE_Z;
	                				}
                					return *this;
                				}

		unsigned long			GetSize(void) const
								{return m_CIE_X.GetSize() + m_CIE_Y.GetSize() + m_CIE_Z.GetSize();}

		bool					IsValid(void) const
								{
									if(
										m_CIE_X.GetInteger() < 0
										|| m_CIE_Y.GetInteger() < 0
										|| m_CIE_Z.GetInteger() < 0
									)
										return false;
									else
										return true;
								}
		void					AutoCorrect(void)
								{
									if(m_CIE_X.GetInteger() < 0)
										m_CIE_X.SetInteger(0);
									if(m_CIE_Y.GetInteger() < 0)
										m_CIE_Y.SetInteger(0);
									if(m_CIE_Z.GetInteger() < 0)
										m_CIE_Z.SetInteger(0);
								}
private:
		iccNumberS15Fixed16		m_CIE_X;
		iccNumberS15Fixed16		m_CIE_Y;
		iccNumberS15Fixed16		m_CIE_Z;
};

//--------------------------------------------------------------------
void operator>>(std::istream& inStream,iccNumberXYZ& outNumber)
{
	inStream >> outNumber.m_CIE_X;
	inStream >> outNumber.m_CIE_Y;
	inStream >> outNumber.m_CIE_Z;
}

//--------------------------------------------------------------------
std::ostream& operator<<(std::ostream& outStream,const iccNumberXYZ& inNumber)
{
	outStream << inNumber.m_CIE_X;
	outStream << inNumber.m_CIE_Y;
	outStream << inNumber.m_CIE_Z;

	return outStream;
}

ICC_LIB_NAMESPACE_END

#endif//_H_iccNumberXYZ_H_

