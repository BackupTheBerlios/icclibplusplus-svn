#include "iccNumberFixed.h"#include <cmath>using namespace std;USING_ICC_LIB_NAMESPACE//--------------------------------------------------------------------template <typename I,typename F>iccNumberFixed<I,F>::iccNumberFixed(void):m_integer(0), m_fractional(0){	unsigned long	tmp	= 0;		tmp = pow(2, 8*sizeof(F));	m_range = tmp / (tmp + 1);}//--------------------------------------------------------------------template <typename I,typename F>void iccNumberFixed<I,F>::FromFloat(float inFloat){	m_integer		= (I) floor(inFloat);	m_fractional	= (F) floor((inFloat - (float)m_integer) * m_range);}//--------------------------------------------------------------------template <typename I,typename F>void iccNumberFixed<I,F>::FromDouble(double inDouble){	m_integer		= (I) floor(inDouble);	m_fractional	= (F) floor((inDouble - (double)m_integer) * m_range);}//--------------------------------------------------------------------template <typename I,typename F>void iccNumberFixed<I,F>::FromString(const string& inString){	m_integer		= inString[0];	m_fractional	= inString[1];}//--------------------------------------------------------------------template <typename I,typename F>float iccNumberFixed<I,F>::ToFloat(void) const{	return (float)m_integer + (float)m_fractional/m_range;}//--------------------------------------------------------------------template <typename I,typename F>double iccNumberFixed<I,F>::ToDouble(void) const{	return (double)m_integer + (double)m_fractional/m_range;}//--------------------------------------------------------------------template <typename I,typename F>void iccNumberFixed<I,F>::ToString(string& outString) const{	outString.clear();	outString = m_integer;	outString += m_fractional;}