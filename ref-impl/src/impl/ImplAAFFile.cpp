
/******************************************\
*                                          *
* Advanced Authoring Format                *
*                                          *
* Copyright (c) 1998 Avid Technology, Inc. *
* Copyright (c) 1998 Microsoft Corporation *
*                                          *
\******************************************/



#include "Container.h"


#ifndef __ImplAAFFile_h__
#include "ImplAAFFile.h"
#endif

#include "AAFTypes.h"
#include "ImplAAFSession.h"
#include "ImplAAFHeader.h"
#include "ImplAAFDataDef.h"
#include "AAFUtils.h"
#include "aafErr.h"
//#include "aafDefs.h"
#include "ImplAAFObjectCreation.h"

#include <assert.h>

extern "C" const aafClassID_t CLSID_AAFHeader;

ImplAAFFile::ImplAAFFile () :
  _cookie(0),
  _fmt(kAAFiMedia),
  _container(0),
  _byteOrder(0),
  _openType(kOmUndefined),
  _prevFile(0),
  _head(0),
  _semanticCheckEnable(AAFFalse),
  _session(0),
  _nilKind(0),
  _pictureKind(0),
  _soundKind(0)
{}


ImplAAFFile::~ImplAAFFile ()
{
  InternalReleaseObjects();

  // cleanup the container.
  delete _container;
  _container = 0;

#if MAYNEEDTHIS
  if (0 != _session)
  {
    _session->ReleaseRef();
    _session = 0;
  }
#endif //MAYNEEDTHIS
}

void ImplAAFFile::InternalReleaseObjects()
{
  if (0 != _soundKind)
  {
    _soundKind->ReleaseRef();
    _soundKind = 0;
  }

  if (0 != _pictureKind)
  {
    _pictureKind->ReleaseRef();
    _pictureKind = 0;
  }

  if (0 != _nilKind)
  {
    _nilKind->ReleaseRef();
    _nilKind = 0;
  }

  if (0 != _head)
  {
    _head->ReleaseRef();
    _head = 0;
  }
}
  //***********************************************************
  // METHOD NAME: Close()
  //
  // DESCRIPTION:
  // @mfunc AAFRESULT | AAFFile | Close |
  // Closes an AAF file, saving the result.
  // @end
  AAFRESULT STDMETHODCALLTYPE
	  ImplAAFFile::Close ()
  {
	
#if FULL_TOOLKIT
	AAFFile *tstFile;
  clearBentoErrors();
  aafAssert((_topMedia == NULL) || (_closeMediaProc != NULL), 
				  this, OM_ERR_MEDIA_CANNOT_CLOSE);
#endif
  
#if FULL_TOOLKIT
  XPROTECT()
	{
#endif
#if FULL_TOOLKIT
	  if (_closeMediaProc != NULL)
		{
		  while (_topMedia != NULL)
			CHECK((*_closeMediaProc) (_topMedia));
		}
		
	  if (this == _session->_topFile)
		_session->_topFile = _prevFile;
	  else
		{
		  tstFile = _session->_topFile;
		  while (tstFile && tstFile->_prevFile != NULL)
			{
			  if (tstFile->_prevFile == this)
				 {
					tstFile->_prevFile = _prevFile;
					break;
				 }
			  else
					tstFile = tstFile->_prevFile;
			}
		}
#endif

	  if (_fmt == kAAFiMedia)
		{
		  switch(_openType)
			{
			case kOmCreate:
			case kOmModify:
				break;
			
			default:
			  break;
			}
		
	  }
		else
		{
#if FULL_TOOLKIT
			if(_rawFileDesc != NULL)
				AAFFree(_rawFileDesc);
#endif
		}

#ifdef AAF_ERROR_TRACE
	  if(_stackTrace != NULL)
	  {
			AAFFree(_stackTrace);
		}
	  _stackTraceSize = 0;
	  _stackTrace = NULL;
#endif
	  if (_fmt == kAAFiMedia)
		{
#if FULL_TOOLKIT
		  if (_BentoErrorNumber)
        // Release all of the pointers that we created or copied during
        // the create or open methods.
        InternalReleaseObjects();

			_container->OMLAbortContainer();
        
        // Whenever a file is created or opened a new container is created.
        // If we don't want to leak the container object and any objects
        // in the associated OMFile object we had better delete the container
        // object here.
        delete _container;
        _container = 0;
		  else
      {
#endif
        // Release all of the pointers that we created or copied during
        // the create or open methods.
        InternalReleaseObjects();

			  _container->OMLCloseContainer();
        
        // Whenever a file is created or opened a new container is created.
        // If we don't want to leak the container object and any objects
        // in the associated OMFile object we had better delete the container
        // object here.
        delete _container;
        _container = 0;

#if FULL_TOOLKIT
      }
		  if (_BentoErrorRaised)
			{
				if(_BentoErrorNumber == CM_err_BadWrite)
				{
					RAISE(OM_ERR_CONTAINERWRITE);
				}
				else
				{
					RAISE(OM_ERR_BADCLOSE);
				}
			}
#endif
	  }
	  _cookie = 0;
#if FULL_TOOLKIT
  }
  XEXCEPT
  {
  }
	XEND
#endif

///	  omOptFree(NULL, file);

	return(AAFRESULT_SUCCESS);
  }

  //***********************************************************
  // METHOD NAME: GetRevision()
  //
  // DESCRIPTION:
  // @mfunc AAFRESULT | AAFFile | GetRevision |
  // Get the revision of the ciurrent AAF file.
  // @end
  // 
	AAFRESULT STDMETHODCALLTYPE
		ImplAAFFile::GetRevision (
    // @parm aafFileRev_t * | rev | [out] Revision of the current file
    aafFileRev_t *  rev
  )
  {
		*rev = kAAFRev1;
		return(AAFRESULT_SUCCESS);
  }

  AAFRESULT STDMETHODCALLTYPE
  ImplAAFFile::GetHeader (
    ImplAAFHeader ** header
  )
  {
    *header = _head;

    // We are returning a copy of the reference counted object.
    if (_head)
      _head->AcquireRef();

    return(AAFRESULT_SUCCESS);
  }

/************************
 * Function: InternOpenFile	(INTERNAL)
 *
 * 	Open a file, given a container use mode and type.   This
 *		is the function which takes care of most of the operations
 *		involved in opening the file.   The wrapper routines 
 *		omfsOpenFile() and omfsModifyFile() should be called instead
 *		by client applications.
 *
 * Argument Notes:
 *		<none>.
 *
 * ReturnValue:
 *		Error code (see below).
 *
 * Possible Errors:
 *		Standard errors (see top of file).
 *		OM_ERR_BAD_SESSION - Session handle is invalid.
 *		OM_ERR_BADHEAD - Head object is invalid or missing.
 *		OM_ERR_NOTAAFFILE - The file is not an AAF file.
 *		OM_ERR_BADOPEN - The file is an AAF file, but fails to open.
 */
AAFRESULT ImplAAFFile::InternOpenFile(aafWChar* stream, 
								   ImplAAFSession * session,
								   OMLContainerUseMode useMode, 
								   openType_t type)
{
	OMLRefCon        	myRefCon = NULL;
#if FULL_TOOLKIT
	aafErr_t      		status;
	aafInt32			errnum;
#endif
	aafErr_t                finalStatus = OM_ERR_NONE;

	if (session == NULL)
	  return(OM_ERR_BAD_SESSION);	

#if FULL_TOOLKIT
	if(!session->isValidSession())
		  return(OM_ERR_BAD_SESSION);	
#endif

#if FULL_TOOLKIT
	status = InitFileHandle(session, kAAFiMedia);
	if (status != OM_ERR_NONE)
		return (status);
#endif

	XPROTECT()
	{
#if FULL_TOOLKIT
		clearBentoErrors();
#endif
		_openType = type;

		if (stream == NULL) 
		  RAISE(OM_ERR_NULL_PARAM);

#if FULL_TOOLKIT		
		myRefCon = createRefConForMyHandlers(session->GetContainerSession(), 
											 (char *) stream, (GetUpdatingTargetType)NULL, this);

		aafCheckBentoRaiseError(this, OM_ERR_BADSESSIONMETA);
#endif
		
		/*
		 * Open the container
		 */
#if FULL_TOOLKIT
		_BentoErrorNumber = 0;
		session->ResetBentoError();
#endif
		assert(NULL == _container);
		_container = new OMContainer;
		_container->OMLOpenContainer(stream, session->GetContainerSession(), myRefCon, "AAF", 
									useMode, _head);
		if (_container == NULL)
		{
#if FULL_TOOLKIT
			if(_BentoErrorRaised)
				errnum = _BentoErrorNumber;
			else
				errnum = session->GetBentoError();
			if (errnum== CM_err_BadMagicBytes)
			{
				RAISE(OM_ERR_NOTAAFFILE);
			}
			else if(session->GetBentoError() == CM_err_GenericMessage)
			{
				RAISE(OM_ERR_FILE_NOT_FOUND);
			}
			else
			{
				RAISE(OM_ERR_BADOPEN);
			}
#endif
		}
		
		/* We now use datakinds in the whole API, not just 2.x
		 */
#if FULL_TOOLKIT
		_head->DatakindLookup(NODATAKIND, &_nilKind, &status);
		CHECK(status);
		_head->DatakindLookup(PICTUREKIND, &_pictureKind, &status);
		CHECK(status);
		_head->DatakindLookup(SOUNDKIND, &_soundKind, &status);
		CHECK(status);

		/* Register any other properties and types in the file in the cache */
		CHECK(_head->UpdateLocalTypesProps(_container));
		_session->HandleOpenCallback(this);
#endif
	}
	XEXCEPT
	{
	  finalStatus = XCODE();
	  NO_PROPAGATE(); /* Rely on finalStatus variable, as file will be NULL */

		/* Reset to previous state before returning with error */
		if (session && this)
		{

#ifdef AAF_ERROR_TRACE
		  if(_stackTrace != NULL)
			 {
				AAFFree(_stackTrace);
			 }
		  _stackTraceSize = 0;
		  _stackTrace = NULL;
#endif
		  if(_container != NULL)
			 {
				_container->OMLAbortContainer();
			 }
		  else if(myRefCon != NULL)
			 OMLFree((OMContainer *)NULL, myRefCon, session->GetContainerSession());

		  /* Set to previous file or NULL */
		  session->SetTopFile(_prevFile);
		  _cookie = 0;
//		  omOptFree(NULL, file);
		}
 // 		file = NULL;
	}
	XEND;

	return (finalStatus);
}

/************************
 * Function: Create
 *
 * 	Create an AAF file referencing the given session, of the
 *		given revision.
 *
 * Argument Notes:
 *		Stream -- Must be of a type which matches the Bento file handler.
 *		ie:	a SFReply record pointer for omfmacsf.c
 *				or a path string for aafansic.c
 *
 * ReturnValue:
 *		Error code (see below).
 *
 * Possible Errors:
 *		Standard errors (see top of file).
 */
AAFRESULT ImplAAFFile::Create(
			aafWChar*		stream, 
			ImplAAFSession		*session, 
			aafFileRev_t		rev)
{
	OMLRefCon        myRefCon;
#ifdef FULL_TOOLKIT
	aafErr_t		status;
#endif

	XPROTECT()
	{
		if (stream == NULL) 
		  RAISE(OM_ERR_NULL_PARAM);

		if (session == NULL)
		  RAISE(OM_ERR_BAD_SESSION);	

#if FULL_TOOLKIT
		if(!session->isValidSession())
		  RAISE(OM_ERR_BAD_SESSION);	

		CHECK(InitFileHandle(session, kAAFiMedia));	
		clearBentoErrors();
#endif
		_setrev = rev;
		_openType = kOmCreate;

#if FULL_TOOLKIT		
		myRefCon = createRefConForMyHandlers(session->GetContainerSession(), 
											 (char *) stream, (GetUpdatingTargetType)NULL, this);

		aafCheckBentoRaiseError(this, OM_ERR_BADSESSIONMETA);
#endif
		_head = dynamic_cast<ImplAAFHeader*>(CreateImpl(CLSID_AAFHeader));
		if (_head == NULL)
		  RAISE(OM_ERR_BADHEAD);

		_head->AddIdentificationObject(session->GetDefaultIdent());
#if FULL_TOOLKIT
		aafCheckBentoRaiseError(this, OM_ERR_BADHEAD);
	
		//_head = head; // already set above.
		/* We now use datakinds in the whole API, not just 2.x
		 */
		_head->DatakindLookup(NODATAKIND, &_nilKind, &status);
		CHECK(status);
		_head->DatakindLookup(PICTUREKIND, &_pictureKind, &status);
		CHECK(status);
		_head->DatakindLookup(SOUNDKIND, &_soundKind, &status);
		CHECK(status);
#endif
		assert(NULL == _container);
		_container = new OMContainer;
		_container->OMLOpenNewContainer(stream, _head, session->GetContainerSession(), myRefCon,
												"AAF",
												(OMLContainerUseMode) kOMLWriting,
												1, 0, 0);
#if FULL_TOOLKIT
		aafCheckBentoRaiseError(this, OM_ERR_BADOPEN);
#endif
		if(_container == NULL)
			RAISE(OM_ERR_BADOPEN);
	
	}
	XEXCEPT
	  {
		 /* Reset to previous state before returning with error */
		 if (session && this)
		{
			/* Added by MT: you need to save the pointer before deleting
			 * the  object
			 */
			ImplAAFFile *pSavedAddr = _prevFile;

//!!!			if (session->GetTopFile())
//				delete(session->GetTopFile());
			     
			/* Set to previous this or NULL */
			session->SetTopFile(pSavedAddr);
		}
	  }
	XEND;
	
	return (OM_ERR_NONE);
}

/************************
 * Function: OpenRead
 *
 * 	Opens an AAF file read-only.
 *
 * Argument Notes:
 *		Stream -- Must be of a type which matches the Bento file handler.
 *		ie:	a SFReply record pointer for omfmacsf.c
 *				or a path string for aafansic.c
 *
 * ReturnValue:
 *		Error code (see below).
 *
 * Possible Errors:
 *		Standard errors (see top of file).
 *		OM_ERR_BAD_SESSION - Session handle is invalid.
 *		OM_ERR_BADHEAD - Head object is invalid or missing.
 *		OM_ERR_NOTAAFFILE - The file is not an AAF file.
 *		OM_ERR_BADOPEN - The file is an AAF file, but fails to open.
 */
AAFRESULT ImplAAFFile::OpenRead(
			aafWChar*		stream, 
			ImplAAFSession *	session)
{
	return (InternOpenFile(stream, session, (OMLContainerUseMode) 0, 
							   kOmOpenRead));
}


/************************
 * Function: omfsModifyFile
 *
 * 	Opens an AAF file for update (read-write).
 *
 * Argument Notes:
 *		Stream -- Must be of a type which matches the Bento file handler.
 *		ie:	a SFReply record pointer for omfmacsf.c
 *				or a path string for aafansic.c
 *
 * ReturnValue:
 *		Error code (see below).
 *
 * Possible Errors:
 *		Standard errors (see top of file).
 *		OM_ERR_BAD_SESSION - Session handle is invalid.
 *		OM_ERR_BADHEAD - Head object is invalid or missing.
 *		OM_ERR_NOTAAFFILE - The file is not an AAF file.
 *		OM_ERR_BADOPEN - The file is an AAF file, but fails to open.
 */
AAFRESULT ImplAAFFile::OpenModify(
			aafWChar*		stream, 
			ImplAAFSession *	session)
{
	aafInt32	numIdent;
	
	XPROTECT()
	{
		CHECK(InternOpenFile(stream, session,
				 (OMLContainerUseMode) kOMLReuseFreeSpace, kOmModify));
		CHECK(_head->SetToolkitRevisionCurrent());
		
		/* NOTE: If modifying an existing file WITHOUT an IDNT object, add a
		 * dummy IDNT object to indicate that this program was not the creator.
		 */
		CHECK(_head->GetNumIdentifications(&numIdent));
		if(numIdent == 0)
		{
			_head->AddIdentificationObject((aafProductIdentification_t *)NULL);
		}
		/* Now, always add the information from THIS application */
		_head->AddIdentificationObject(session->GetDefaultIdent());
	}
	XEXCEPT
	  {
	  }
	XEND;
  
	return (OM_ERR_NONE);
}

#if 0
extern "C" const aafClassID_t CLSID_AAFFile;

OMDEFINE_STORABLE(ImplAAFFile, CLSID_AAFFile);
#endif
