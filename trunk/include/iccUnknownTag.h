//----------------------------------------------------------------------------------------
//	iccUnknownTag.h
//	ICCLib++
//
//	Creation: 20/11/2004
//	Author: Hugues Lemonnier
//----------------------------------------------------------------------------------------
// $HEADER$
//----------------------------------------------------------------------------------------
#ifndef _ICCUNKNOWNTAG_H
#define _ICCUNKNOWNTAG_H

class iccUnknownTag:	public iccTag
{
public:
							iccUnknownTag(void);
							iccUnknownTag(const iccUnknownTag& inTag)
							{
								*this = inTag;
							}
virtual						~iccUnknownTag();

virtual	iccError			Load(std::istream& inStream);
virtual	iccError			Save(std::ostream& outStream);

virtual	unsigned long		GetSize(void) const {return m_size;}
virtual	void				SetSize(unsigned long inSize);
		iccUnknownTag		&operator=(const iccUnknownTag& inTag);

private:
  		char				*m_data;
};

#endif	//_ICCUNKNOWNTAG_H

