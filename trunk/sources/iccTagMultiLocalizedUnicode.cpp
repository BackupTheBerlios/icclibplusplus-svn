#include "iccTagMultiLocalizedUnicode.h"

using namespace std;
USING_ICC_LIB_NAMESPACE

//--------------------------------------------------------------------
iccTagMultiLocalizedUnicode& iccTagMultiLocalizedUnicode::operator=(const iccTagMultiLocalizedUnicode& inTag)
{
	if(this != &inTag)
	{
		*(iccTag*)this = *(iccTag*)&inTag;

		m_nbNames			= inTag.m_nbNames;
		m_nameRecordSize	= inTag.m_nameRecordSize;
		m_nameRecords		= inTag.m_nameRecords;
		m_names				= inTag.m_names;
	}
	return *this;
}

//--------------------------------------------------------------------
unsigned long iccTagMultiLocalizedUnicode::GetSizeSelf(void) const
{
	vector<nameRecord>::const_iterator	it,
										itEnd;
	unsigned long						tmp	= 0;
	
	for(it=m_nameRecords.begin(),itEnd=m_nameRecords.end(); it<itEnd; it++)
		tmp += it->m_nameLength;
	return	sizeof(iccNumberUInt32)
			+ sizeof(iccNumberUInt32)
			+ m_nbNames*nameRecord::Size()
			+ tmp;
}

//--------------------------------------------------------------------
iccError iccTagMultiLocalizedUnicode::LoadSelf(istream& inStream,unsigned long inSize)
{
	vector<nameRecord>::iterator	it;
	iccNumberUInt32					i	= 0;

	inStream >> m_nbNames;
	inSize -= sizeof(iccNumberUInt32);

	inStream >> m_nameRecordSize;
	inSize -= sizeof(iccNumberUInt32);

	for(i=0; i<m_nbNames; i++)
		inStream >> m_nameRecords[i];
	inSize -= m_nbNames*nameRecord::Size();

#pragma message("TO DO: read strings")

	return iccErrorNone;
}

//--------------------------------------------------------------------
iccError iccTagMultiLocalizedUnicode::SaveSelf(ostream& outStream,unsigned long& outSize) const
{
	vector<nameRecord>::iterator	it;
	iccNumberUInt32					i	= 0;

	outStream << m_nbNames;
	outSize += sizeof(iccNumberUInt32);

	outStream << m_nameRecordSize;
	outSize += sizeof(iccNumberUInt32);

	for(i=0; i<m_nbNames; i++)
		outStream << m_nameRecords[i];
	outSize += m_nbNames*nameRecord::Size();

#pragma message("TO DO: write strings")

	return iccErrorNone;
}

