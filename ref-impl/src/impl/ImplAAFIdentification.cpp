
/***********************************************************************
 *
 *              Copyright (c) 1998-1999 Avid Technology, Inc.
 *
 * Permission to use, copy and modify this software and accompanying 
 * documentation, and to distribute and sublicense application software
 * incorporating this software for any purpose is hereby granted, 
 * provided that (i) the above copyright notice and this permission
 * notice appear in all copies of the software and related documentation,
 * and (ii) the name Avid Technology, Inc. may not be used in any
 * advertising or publicity relating to the software without the specific,
 * prior written permission of Avid Technology, Inc.
 *
 * THE SOFTWARE IS PROVIDED AS-IS AND WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS, IMPLIED OR OTHERWISE, INCLUDING WITHOUT LIMITATION, ANY
 * WARRANTY OF MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE.
 * IN NO EVENT SHALL AVID TECHNOLOGY, INC. BE LIABLE FOR ANY DIRECT,
 * SPECIAL, INCIDENTAL, PUNITIVE, INDIRECT, ECONOMIC, CONSEQUENTIAL OR
 * OTHER DAMAGES OF ANY KIND, OR ANY DAMAGES WHATSOEVER ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE AND
 * ACCOMPANYING DOCUMENTATION, INCLUDING, WITHOUT LIMITATION, DAMAGES
 * RESULTING FROM LOSS OF USE, DATA OR PROFITS, AND WHETHER OR NOT
 * ADVISED OF THE POSSIBILITY OF DAMAGE, REGARDLESS OF THE THEORY OF
 * LIABILITY.
 *
 ************************************************************************/


#ifndef __ImplAAFIdentification_h__
#include "ImplAAFIdentification.h"
#endif

#include "AAFTypes.h"
#include "AAFResult.h"
#include "AAFUtils.h"

#include "AAFStoredObjectIDs.h"
#include "AAFPropertyIDs.h"

#include <assert.h>


ImplAAFIdentification::~ImplAAFIdentification ()
{}

ImplAAFIdentification::ImplAAFIdentification():
  _companyName(         PID_Identification_CompanyName,          L"CompanyName"),
  _productName(         PID_Identification_ProductName,          L"ProductName"),
  _productVersion(      PID_Identification_ProductVersion,       L"ProductVersion"),
  _productVersionString(PID_Identification_ProductVersionString, L"ProductVersionString"),
  _productId(			  PID_Identification_ProductID,            L"ProductID"),
  _date(                PID_Identification_Date,                 L"Date"),
  _toolkitVersion(      PID_Identification_ToolkitVersion,       L"ToolkitVersion"),
  _platform(            PID_Identification_Platform,             L"Platform"),
  _generation(       PID_Identification_GenerationAUID,       L"GenerationAUID")
{
  // Insert the properties into the persistent property set.
  //
  _persistentProperties.put(   _companyName.address());
  _persistentProperties.put(   _productName.address());
  _persistentProperties.put(_productVersion.address());
  _persistentProperties.put(   _productVersionString.address());
  _persistentProperties.put(_productId.address());
  _persistentProperties.put(   _date.address());
  _persistentProperties.put(_toolkitVersion.address());
  _persistentProperties.put(   _platform.address());
  _persistentProperties.put(_generation.address());

  
#if defined( OS_WINDOWS )
  _platform = L"Win32";
#elif defined( OS_MACOS )
  _platform = L"MacOS";
#elif defined( OS_UNIX )
  _platform = L"Unix";
#else
  _platform = L"Unknown";
#endif

}


AAFRESULT STDMETHODCALLTYPE
ImplAAFIdentification::Initialize
 (aafCharacter_constptr companyName,
  aafCharacter_constptr productName,
  aafCharacter_constptr productVersionString,
  aafUID_constref productID)
{
  if (isInitialized ()) return AAFRESULT_ALREADY_INITIALIZED;

  if (! companyName)          return AAFRESULT_NULL_PARAM;
  if (! productName)          return AAFRESULT_NULL_PARAM;
  if (! productVersionString) return AAFRESULT_NULL_PARAM;

  AAFRESULT hr;

  hr = SetCompanyName (companyName);
  if (AAFRESULT_FAILED (hr)) return hr;
  hr = SetProductName (productName);
  if (AAFRESULT_FAILED (hr)) return hr;
  hr = SetProductVersionString (productVersionString);
  if (AAFRESULT_FAILED (hr)) return hr;
  hr = SetProductID (productID);
  if (AAFRESULT_FAILED (hr)) return hr;

  aafUID_t gen;
  hr = aafAUIDNew (&gen);
  if (AAFRESULT_FAILED (hr)) return hr;
  _generation = gen;

  aafTimeStamp_t timestamp;
  AAFGetDateTime (&timestamp);
  _date = timestamp;

  _toolkitVersion = AAFReferenceImplementationVersion;

  setInitialized ();

  return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFIdentification::GetCompanyName (aafWChar *  pName,
										   aafUInt32 bufSize)
{
  if (! isInitialized ()) return AAFRESULT_NOT_INITIALIZED;

  bool stat;
  if (! pName)
	{
	  return AAFRESULT_NULL_PARAM;
	}
  stat = _companyName.copyToBuffer(pName, bufSize);
  if (! stat)
	{
	  return AAFRESULT_SMALLBUF;
	}
  return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFIdentification::GetCompanyNameBufLen (aafUInt32 *  pLen)
{
  if (! isInitialized ()) return AAFRESULT_NOT_INITIALIZED;

  if (! pLen)
	{
	  return AAFRESULT_NULL_PARAM;
	}
  *pLen = _companyName.size();
  return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFIdentification::GetProductName (aafWChar *  pProductName,
										   aafUInt32 bufSize)
{
  if (! isInitialized ()) return AAFRESULT_NOT_INITIALIZED;

  bool stat;
  if (! pProductName)
	{
	  return AAFRESULT_NULL_PARAM;
	}
  stat = _productName.copyToBuffer(pProductName, bufSize);
  if (! stat)
	{
	  return AAFRESULT_SMALLBUF;
	}
  return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFIdentification::GetProductNameBufLen (aafUInt32 *  pLen)
{
  if (! isInitialized ()) return AAFRESULT_NOT_INITIALIZED;

  if (! pLen)
	{
	  return AAFRESULT_NULL_PARAM;
	}
  *pLen = _productName.size();
  return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFIdentification::GetProductVersion (aafProductVersion_t* productVersion)
{
  if (! isInitialized ()) return AAFRESULT_NOT_INITIALIZED;

	if (! productVersion)
	{
		return AAFRESULT_NULL_PARAM;
	}

	if(!_productVersion.isPresent())
	{
		return AAFRESULT_PROP_NOT_PRESENT;
	}	
	*productVersion = _productVersion;
	return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFIdentification::GetProductVersionString (aafWChar *  pVS,
													aafUInt32 bufSize)
{
  if (! isInitialized ()) return AAFRESULT_NOT_INITIALIZED;

  bool stat;
  if (! pVS)
	{
	  return AAFRESULT_NULL_PARAM;
	}
  stat = _productVersionString.copyToBuffer(pVS, bufSize);
  if (! stat)
	{
	  return AAFRESULT_SMALLBUF;
	}
  return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFIdentification::GetProductVersionStringBufLen (aafUInt32 *  pLen)
{
  if (! isInitialized ()) return AAFRESULT_NOT_INITIALIZED;

  if (! pLen)
	{
	  return AAFRESULT_NULL_PARAM;
	}
  *pLen = _productVersionString.size();
  return AAFRESULT_SUCCESS;
}



AAFRESULT STDMETHODCALLTYPE
    ImplAAFIdentification::GetProductID (aafUID_t * pPID)
{
  if (! isInitialized ()) return AAFRESULT_NOT_INITIALIZED;

  if (! pPID)
	{
	  return AAFRESULT_NULL_PARAM;
	}

  *pPID = _productId;

  return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFIdentification::GetDate (aafTimeStamp_t * pTS)
{
  if (! isInitialized ()) return AAFRESULT_NOT_INITIALIZED;

  if (! pTS)
	{
	  return AAFRESULT_NULL_PARAM;
	}
  *pTS = _date;
  return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFIdentification::GetRefImplVersion (aafProductVersion_t* productVersion)
{
  if (! isInitialized ()) return AAFRESULT_NOT_INITIALIZED;

	if (! productVersion)
	{
		return AAFRESULT_NULL_PARAM;
	}
	
	if(!_toolkitVersion.isPresent())
	{
		return AAFRESULT_PROP_NOT_PRESENT;
	}

	*productVersion = _toolkitVersion;

	return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFIdentification::GetPlatform (aafWChar *  pPlatform,
										aafUInt32 bufSize)
{
  if (! isInitialized ()) return AAFRESULT_NOT_INITIALIZED;

	if (! pPlatform)
	{
		return AAFRESULT_NULL_PARAM;
	}
	
	if(!_platform.isPresent())
	{
		return AAFRESULT_PROP_NOT_PRESENT;
	}

	bool stat;
	
	stat = _platform.copyToBuffer(pPlatform, bufSize);
	if (! stat)
	{
		return AAFRESULT_SMALLBUF;
	}
	return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFIdentification::GetPlatformBufLen (aafUInt32 *  pLen)
{
  if (! isInitialized ()) return AAFRESULT_NOT_INITIALIZED;

	if (! pLen)
	{
		return AAFRESULT_NULL_PARAM;
	}

	if(!_platform.isPresent())
	{
		return AAFRESULT_PROP_NOT_PRESENT;
	}
		
	*pLen = _platform.size();
	return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFIdentification::GetGenerationID (aafUID_t *  pGen)
{
  if (! isInitialized ()) return AAFRESULT_NOT_INITIALIZED;

  if (! pGen)
	{
	  return AAFRESULT_NULL_PARAM;
	}

  *pGen = _generation;
  return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFIdentification::SetCompanyName (const aafCharacter * pName)
{
  if (! pName)
	{
	  return AAFRESULT_NULL_PARAM;
	}

  _companyName = pName;

  return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFIdentification::SetProductName (const aafCharacter * pName)
{
  if (! pName)
	{
	  return AAFRESULT_NULL_PARAM;
	}

  _productName = pName;

  return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFIdentification::SetProductVersion (aafProductVersion_constref productVersion)
{
  if (! isInitialized ()) return AAFRESULT_NOT_INITIALIZED;

	_productVersion = productVersion;

	return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFIdentification::SetProductVersionString (const aafCharacter * pVS)
{
	if (! pVS)
	{
		return AAFRESULT_NULL_PARAM;
	}
	
	_productVersionString = pVS;
	
	return AAFRESULT_SUCCESS;
}


AAFRESULT STDMETHODCALLTYPE
    ImplAAFIdentification::SetProductID (const aafUID_t & PID)
{
  _productId = PID;
  return AAFRESULT_SUCCESS;
}
