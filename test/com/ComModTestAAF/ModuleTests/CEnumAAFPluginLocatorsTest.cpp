// @doc INTERNAL
// @com This file implements the module test for CAAFDefinitionObject
/******************************************\
*                                          *
* Advanced Authoring Format                *
*                                          *
* Copyright (c) 1998 Avid Technology, Inc. *
* Copyright (c) 1998 Microsoft Corporation *
*                                          *
\******************************************/


/***********************************************\
*	Stub only.   Implementation not yet added	*
\***********************************************/







#include "CEnumAAFPluginLocators.h"
#include "CEnumAAFPluginLocators.h"
#ifndef __CEnumAAFPluginLocators_h__
#error - improperly defined include guard
#endif


#include <iostream.h>

// Temporarily necessary global declarations.
extern "C" const CLSID CLSID_EnumAAFPluginLocators; // generated


HRESULT CEnumAAFPluginLocators::test()
{
  HRESULT hr = AAFRESULT_NOT_IMPLEMENTED;
  IEnumAAFPluginLocators *pObject = NULL;

  try
    {
      // Attempt to create an EnumAAFPluginLocators.
      hr =  CoCreateInstance(
                             CLSID_EnumAAFPluginLocators,
                             NULL, 
                             CLSCTX_INPROC_SERVER, 
                             IID_IEnumAAFPluginLocators, (void **)&pObject);
      if (FAILED(hr))
        {
          cerr << "CEnumAAFPluginLocators::test...FAILED!";
          cerr << hr;
          cerr << "\tCoCreateInstance(&CLSID_EnumAAFPluginLocators, NULL,"
            " CLSCTX_INPROC_SERVER, &IID_IEnumAAFPluginLocators, ...);" <<
              endl;
          return hr;
        }

      // module-specific tests go here

      if (pObject)
        pObject->Release();
      return AAFRESULT_NOT_IMPLEMENTED;

    }
  catch (...)
    {
      cerr << "CEnumAAFPluginLocators::test...Caught general C++"
        " exception!" << endl; 
    }

  // Cleanup our object if it exists.
  if (pObject)
    pObject->Release();

  return hr;
}















