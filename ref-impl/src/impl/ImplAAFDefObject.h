//@doc
//@class    AAFDefObject | Implementation class for AAFDefObject
#ifndef __ImplAAFDefObject_h__
#define __ImplAAFDefObject_h__

/******************************************\
*                                          *
* Advanced Authoring Format                *
*                                          *
* Copyright (c) 1998 Avid Technology, Inc. *
* Copyright (c) 1998 Microsoft Corporation *
*                                          *
\******************************************/

#ifndef __AAFTypes_h__
#include "AAFTypes.h"
#endif

#ifndef __ImplAAFObject_h__
#include "ImplAAFObject.h"
#endif

class ImplAAFDictionary;


class ImplAAFDefObject : public ImplAAFObject
{
public:
  //
  // Constructor/destructor
  //
  //********
  ImplAAFDefObject ();

protected:
  virtual ~ImplAAFDefObject ();

public:

  // SetAUID()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    Init
        // @parm [in] Pointer to an AUID reference
        (aafUID_t *  pAuid, wchar_t *name, wchar_t *description);
  //****************
  // GetAUID()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetAUID
        // @parm [retval,out] Pointer to an AUID reference
        (aafUID_t *  pAuid);

  //****************
  // SetAUID()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetAUID
        // @parm [in] Pointer to an AUID reference
        (aafUID_t *  pAuid);


  //****************
  // SetName()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetName
        (aafWChar *  name);  //@parm [in, ref] Definition Name


  //****************
  // GetName()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetName
        (// @parm [out, string, size_is(bufSize)] buffer into which Name is to be written
         wchar_t *  pName,

         // @parm [in] size of *pName buffer in bytes
         aafUInt32  bufSize);


  //****************
  // GetNameBufLen()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetNameBufLen
        (aafUInt32 *  nameLen);  //@parm [in,out] Definition Name length


  //****************
  // SetDescription()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    SetDescription
        (aafWChar *  description);  //@parm [in, ref] Definition description


  //****************
  // GetDescription()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetDescription
        (aafWChar *  description,  //@parm [in] Definition Description
		 aafUInt32 bufSize);	  //@parm [in] size of the buffer required to hold Definition Description + terminator


  //****************
  // GetDescriptionBufLen()
  //
  virtual AAFRESULT STDMETHODCALLTYPE
    GetDescriptionBufLen
        (aafUInt32 *  descriptionLen);  //@parm [in,out] Definition description length


public:
  // Declare this class to be storable.
  //
  OMDECLARE_STORABLE(ImplAAFDefObject)

  // Declare the module test method. The implementation of the will be be
  // in /test/ImplAAFDefObjectTest.cpp.
  static AAFRESULT test();

  // non-published method to set the containing dictionary for this
  // object.
  void SetDict (ImplAAFDictionary * pDict);

protected:
  // Returns a pointer to the dictionary containing this object.  Will
  // assert() if not yet set.
  ImplAAFDictionary * GetDict ();

private:
  // friendly name of this definition
  OMWideStringProperty          _name;

  // brief text description of this definition
  OMWideStringProperty          _description;

  // auid to be used to identify this definition
  OMFixedSizeProperty<aafUID_t> _identification;

  // pointer to dict containing this object
  ImplAAFDictionary *           _pDict;
};

#endif // ! __ImplAAFDefObject_h__
