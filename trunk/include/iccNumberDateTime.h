#ifndef _H_iccNumberDateTime_H_
#define _H_iccNumberDateTime_H_

#include "iccObject.h"
#include "iccBasicNumericTypes.h"
#include <istream>
#include <ostream>

ICC_LIB_NAMESPACE_START

// Date shall be in Coordinated Universal Time (UTC)
class iccNumberDateTime:	public iccObject
{
public:
    							iccNumberDateTime(void)
    							:	m_year(0),m_month(0),m_day(0),
    								m_hours(0),m_minutes(0),m_seconds(0)
    							{}

friend	void					operator>>(std::istream& inStream,iccNumberDateTime& outNumber);
friend	std::ostream&			operator<<(std::ostream& outStream,const iccNumberDateTime& inNumber);
   		iccNumberDateTime&		operator=(const iccNumberDateTime &inNumber)
                				{
									if(this != &inNumber)
	                				{
										m_year		= inNumber.m_year;
                            			m_month		= inNumber.m_month;
                            			m_day		= inNumber.m_day;
										m_hours		= inNumber.m_hours;
                            			m_minutes	= inNumber.m_minutes;
                            			m_seconds	= inNumber.m_seconds;
	                				}
                					return *this;
                				}

		unsigned long			GetSize(void) const
								{
									return	sizeof m_year
											+ sizeof m_month
											+ sizeof m_day
											+ sizeof m_hours
											+ sizeof m_minutes
											+ sizeof m_seconds;
								}

		bool					IsValid(void) const
								{
                        			if(m_month < 1 || 12 < m_month)
                        				return false;
                        			if(m_day < 1 || 31 < m_day)
                        				return false;
                        			else
                        			if(
                        				(m_month==4 || m_month==6 || m_month==9 || m_month==11)
                        				&& 30 < m_day
                        			)
                        				return false;
                        			else
                        			if(m_month == 2 && 28 < m_day)
                        				return false;
#pragma message("TO DO: leap years")
                        			if(23 < m_hours)
                        				return false;
                        			if(59 < m_minutes)
                        				return false;
                        			if(59 < m_seconds)
                        				return false;
                        			
                        			return true;
								}
		void					AutoCorrect(void)
								{
                        			if(m_month < 1 || 12 < m_month)
                        				m_month = 1;
                        			if(
                        				(m_month==4 || m_month==6 || m_month==9 || m_month==11)
                        				&& 30 < m_day
                        			)
                        				m_day = 1;
                        			else
                        			if(m_month == 2 && 28 < m_day)
                        				m_day = 1;
                        			else
                        			if(31 < m_day)
                        				m_day = 1;
#pragma message("TO DO: leap years")
                        			if(23 < m_hours)
                        				m_hours = 0;
                        			if(59 < m_minutes)
                        				m_minutes = 0;
                        			if(59 < m_seconds)
                        				m_seconds = 0;
								}
		
private:
        iccNumberUInt16			m_year;
        iccNumberUInt16			m_month;
        iccNumberUInt16			m_day;
        iccNumberUInt16			m_hours;
        iccNumberUInt16			m_minutes;
        iccNumberUInt16			m_seconds;
};

#pragma message("TO DO: write conversion methods to/from local time to UTC")

//--------------------------------------------------------------------
void operator>>(std::istream& inStream,iccNumberDateTime& outNumber)
{
	inStream >> outNumber.m_year;
	inStream >> outNumber.m_month;
	inStream >> outNumber.m_day;
	inStream >> outNumber.m_hours;
	inStream >> outNumber.m_minutes;
	inStream >> outNumber.m_seconds;
}

//--------------------------------------------------------------------
std::ostream& operator<<(std::ostream& outStream,const iccNumberDateTime& inNumber)
{
	outStream << inNumber.m_year;
	outStream << inNumber.m_month;
	outStream << inNumber.m_day;
	outStream << inNumber.m_hours;
	outStream << inNumber.m_minutes;
	outStream << inNumber.m_seconds;

	return outStream;
}

ICC_LIB_NAMESPACE_END

#endif//_H_iccNumberDateTime_H_


