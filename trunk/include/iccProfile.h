//----------------------------------------------------------------------------------------
//	iccProfile.h
//	ICCLib++
//	
//	Creation: 09/10/2004
//	Author: Hugues Lemonnier
//----------------------------------------------------------------------------------------
// $HEADER$
//----------------------------------------------------------------------------------------
#ifndef _ICCPROFILE_H
#define _ICCPROFILE_H

#include <istream>
#include <ostream>

#include "iccHeader.h"

class iccObject;
class iccTagTable;

/**
 *	The iccProfile class holds the data of an ICC profile and allows random
 *	access to any of its components.
 */
class iccProfile	:	public iccObject
{
public:
            			/**
            			 *	No-args constructor.
            			 */
        				iccProfile(void);
            			/**
            			 *	Destructor.
            			 */
virtual					~iccProfile(void);

        				/**
        				 *	Links the profile to an input stream.
        				 *	A profile object must be linked to an input stream in order to
        				 *	have read or write access to ICC profile data. When an input
        				 *	stream is linked, the profile header and the tag table are
        				 *	loaded and stored in the object. A tag is loaded only if 
        				 *	requested.
        				 *	@param inInputStream the stream to link the profile to.
        				 *	@return an error code
        				 */
virtual	int				Open(std::istream *inInputStream);

        				/**
        				 *	Links the profile to an output stream.
        				 *	A profile object must be linked to an output stream in order
        				 *	to write the ICC profile data.
        				 *	@param inOutputStream the output stream to link the profile to.
        				 *	@return an error code
        				 */
virtual	int				Open(std::ostream *inOutputStream);

        				/**
        				 *	Removes the link from a stream.
        				 *	@return an error code.
        				 */
virtual	int 			Close(void);

        				/**
        				 *	Loads all the tags of an ICC profile from the linkd stream.
        				 *	@return an error code
        				 */
virtual	int				Load(void);

        				/**
        				 *	Saves the profile to the linked stream.
        				 *	@return an error code
        				 */
virtual	int				Save(void);

		/**
		 *	@name	Getter/Setter
		 */
		//@{
virtual	const iccHeader	&GetHeader(void) {return m_header;}
   		//@}
protected:
            			/**
            			 *	Reads the profile header.
        				 *	@return an error code
            			 */
virtual	int				ReadHeader(void);

            			/**
            			 *	Writes the profile header.
        				 *	@return an error code
            			 */
virtual	int				WriteHeader(void);

            			/**
            			 *	Reads the tag table.
        				 *	@return an error code
            			 */
virtual	int				ReadTagTable(void);

            			/**
            			 *	Writes the tag table.
        				 *	@return an error code
            			 */
virtual	int   			WriteTagTable(void);

private:
    std::istream		*m_inputStream;		///< Linked input stream
    std::ostream		*m_outputStream;	///< Linked output stream
    iccHeader			m_header;			///< Profile header
    iccTagTable			m_tagTable;			///< Tag table
};

endif	// _ICCPROFILE_H
