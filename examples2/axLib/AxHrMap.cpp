//=---------------------------------------------------------------------=
//
// The contents of this file are subject to the AAF SDK Public
// Source License Agreement (the "License"); You may not use this file
// except in compliance with the License.  The License is available in
// AAFSDKPSL.TXT, or you may obtain a copy of the License from the AAF
// Association or its successor.
// 
// Software distributed under the License is distributed on an "AS IS"
// basis, WITHOUT WARRANTY OF ANY KIND, either express or implied.  See
// the License for the specific language governing rights and limitations
// under the License.
// 
// The Original Code of this file is Copyright 1998-2001, Licensor of the
// AAF Association.
// 
//=---------------------------------------------------------------------=

#if defined(OS_WINDOWS)
#pragma warning(disable:4786)
// The prama is busted. It must be above std lib header includes, even then
// it doesn't work. See:
// http://support.microsoft.com/support/kb/articles/Q167/3/55.ASP
// http://support.microsoft.com/support/kb/articles/Q195/3/86.ASP
// http://support.microsoft.com/support/kb/articles/Q122/5/39.ASP
#endif

#include "AxHrMap.h"

#include <AAFResult.h>

namespace {

AxString hrUnkownStr( L"unkown" );

};

AxHrMap::AxHrMap()
{

#define HRSTRING( PREFIX, STRING ) PREFIX##STRING
#define MAP_ADD( HR ) _map[ HR ] = HRSTRING( L, #HR ) ;

	
	// Error code list generated automatically using the command:
	// grep AAFRESULT ref-impl/include/AAFResult.h | cut -d\  -f2 | sort | uniq

	MAP_ADD( AAFRESULT_24BITVIDEO );
	MAP_ADD( AAFRESULT_3COMPONENT );
	MAP_ADD( AAFRESULT_ABSTRACT_CLASS );
	MAP_ADD( AAFRESULT_ADJACENT_TRAN );
	MAP_ADD( AAFRESULT_ALREADY_INITIALIZED );
	MAP_ADD( AAFRESULT_ALREADY_OPEN );
	MAP_ADD( AAFRESULT_ALREADY_UNIQUELY_IDENTIFIED );
	MAP_ADD( AAFRESULT_ASSERTION_VIOLATION );
	MAP_ADD( AAFRESULT_BADACTABLE );
	MAP_ADD( AAFRESULT_BADAIFCDATA );
	MAP_ADD( AAFRESULT_BADCLOSE );
	MAP_ADD( AAFRESULT_BADCOMPR );
	MAP_ADD( AAFRESULT_BADCONTAINER );
	MAP_ADD( AAFRESULT_BADDATAADDRESS );
	MAP_ADD( AAFRESULT_BADDCTABLE );
	MAP_ADD( AAFRESULT_BADEXPORTLAYOUT );
	MAP_ADD( AAFRESULT_BADEXPORTPIXFORM );
	MAP_ADD( AAFRESULT_BADFRAMEOFFSET );
	MAP_ADD( AAFRESULT_BADHEAD );
	MAP_ADD( AAFRESULT_BADINDEX );
	MAP_ADD( AAFRESULT_BADJPEGINFO );
	MAP_ADD( AAFRESULT_BADLAYOUT );
	MAP_ADD( AAFRESULT_BADMEDIATYPE );
	MAP_ADD( AAFRESULT_BADOPEN );
	MAP_ADD( AAFRESULT_BADPIXFORM );
	MAP_ADD( AAFRESULT_BADQTABLE );
	MAP_ADD( AAFRESULT_BADRATE );
	MAP_ADD( AAFRESULT_BADRWLINES );
	MAP_ADD( AAFRESULT_BADSAMPLEOFFSET );
	MAP_ADD( AAFRESULT_BADSESSIONCLOSE );
	MAP_ADD( AAFRESULT_BADSESSIONMETA );
	MAP_ADD( AAFRESULT_BADSESSIONOPEN );
	MAP_ADD( AAFRESULT_BADTIFFCOUNT );
	MAP_ADD( AAFRESULT_BADWAVEDATA );
	MAP_ADD( AAFRESULT_BAD_CODEC_REV );
	MAP_ADD( AAFRESULT_BAD_FHDL );
	MAP_ADD( AAFRESULT_BAD_FLAGS );
	MAP_ADD( AAFRESULT_BAD_FLAG_COMBINATION );
	MAP_ADD( AAFRESULT_BAD_ITHDL );
	MAP_ADD( AAFRESULT_BAD_LENGTH );
	MAP_ADD( AAFRESULT_BAD_MDHDL );
	MAP_ADD( AAFRESULT_BAD_PROP );
	MAP_ADD( AAFRESULT_BAD_SESSION );
	MAP_ADD( AAFRESULT_BAD_SIZE );
	MAP_ADD( AAFRESULT_BAD_SLOTLENGTH );
	MAP_ADD( AAFRESULT_BAD_SRCH_ITER );
	MAP_ADD( AAFRESULT_BAD_STRACKHDL );
	MAP_ADD( AAFRESULT_BAD_TYPE );
	MAP_ADD( AAFRESULT_BAD_TYPE_CATEGORY );
	MAP_ADD( AAFRESULT_BAD_VARIETY );
	MAP_ADD( AAFRESULT_BAD_VIRTUAL_CREATE );
	MAP_ADD( AAFRESULT_BLOCKING_SIZE );
	MAP_ADD( AAFRESULT_CANNOT_LOAD_CLSD );
	MAP_ADD( AAFRESULT_CANNOT_SAVE_CLSD );
	MAP_ADD( AAFRESULT_CLASS_NOT_FOUND );
	MAP_ADD( AAFRESULT_CODEC_CHANNELS );
	MAP_ADD( AAFRESULT_CODEC_INVALID );
	MAP_ADD( AAFRESULT_CODEC_NAME_SIZE );
	MAP_ADD( AAFRESULT_CODEC_SEMANTIC_WARN );
	MAP_ADD( AAFRESULT_COMPRLINESRD );
	MAP_ADD( AAFRESULT_COMPRLINESWR );
	MAP_ADD( AAFRESULT_CONTAINERWRITE );
	MAP_ADD( AAFRESULT_DATADEF_EXIST );
	MAP_ADD( AAFRESULT_DATA_IN_SEMANTIC );
	MAP_ADD( AAFRESULT_DATA_MDES_DISAGREE );
	MAP_ADD( AAFRESULT_DATA_NONCONTIG );
	MAP_ADD( AAFRESULT_DATA_OUT_SEMANTIC );
	MAP_ADD( AAFRESULT_DATA_SIZE );
	MAP_ADD( AAFRESULT_DECOMPRESS );
	MAP_ADD( AAFRESULT_DEFAULT_ALREADY_USED );
	MAP_ADD( AAFRESULT_DESCLENGTH );
	MAP_ADD( AAFRESULT_DESCSAMPRATE );
	MAP_ADD( AAFRESULT_DLL_LOAD_FAILED );
	MAP_ADD( AAFRESULT_DLL_SYMBOL_NOT_FOUND );
	MAP_ADD( AAFRESULT_DUPLICATE_MOBID );
	MAP_ADD( AAFRESULT_EFFECTDEF_EXIST );
	MAP_ADD( AAFRESULT_ELEMENT_NOT_OBJECT );
	MAP_ADD( AAFRESULT_ELEMENT_NOT_PRESENT );
	MAP_ADD( AAFRESULT_END_OF_DATA );
	MAP_ADD( AAFRESULT_EOF );
	MAP_ADD( AAFRESULT_ESSENCE_NOT_FOUND );
	MAP_ADD( AAFRESULT_EXTENSION_ALREADY_INITIALIZED );
	MAP_ADD( AAFRESULT_EXTENSION_NOT_FOUND );
//	MAP_ADD( AAFRESULT_FAILED(Status) );
	MAP_ADD( AAFRESULT_FILEREV_DIFF );
	MAP_ADD( AAFRESULT_FILEREV_NOT_SUPP );
	MAP_ADD( AAFRESULT_FILE_EXISTS );
	MAP_ADD( AAFRESULT_FILE_NOT_FOUND );
	MAP_ADD( AAFRESULT_FILE_REV_200 );
	MAP_ADD( AAFRESULT_FILL_FOUND );
	MAP_ADD( AAFRESULT_FILM_DESC_ONLY );
	MAP_ADD( AAFRESULT_FORMAT_BOUNDS );
	MAP_ADD( AAFRESULT_FORMAT_NOT_FOUND );
	MAP_ADD( AAFRESULT_ILLEGAL_FILEFMT );
	MAP_ADD( AAFRESULT_ILLEGAL_MEMFMT );
	MAP_ADD( AAFRESULT_ILLEGAL_VALUE );
	MAP_ADD( AAFRESULT_INCONSISTANCY );
	MAP_ADD( AAFRESULT_INSUFF_TRAN_MATERIAL );
	MAP_ADD( AAFRESULT_INTERNAL_DIVIDE );
	MAP_ADD( AAFRESULT_INTERNAL_ERROR );
	MAP_ADD( AAFRESULT_INTERNAL_ITERATOR );
	MAP_ADD( AAFRESULT_INTERNAL_MDO );
	MAP_ADD( AAFRESULT_INTERNAL_NEG64 );
	MAP_ADD( AAFRESULT_INTERNAL_UNKNOWN_LOC );
	MAP_ADD( AAFRESULT_INTERN_TOO_SMALL );
	MAP_ADD( AAFRESULT_INVALID_ATTRIBUTEKIND );
	MAP_ADD( AAFRESULT_INVALID_BOOLTYPE );
	MAP_ADD( AAFRESULT_INVALID_BYTEORDER );
	MAP_ADD( AAFRESULT_INVALID_CACHE_SIZE );
	MAP_ADD( AAFRESULT_INVALID_CLASS_ID );
	MAP_ADD( AAFRESULT_INVALID_CVAL );
	MAP_ADD( AAFRESULT_INVALID_DATADEF );
	MAP_ADD( AAFRESULT_INVALID_EDGETYPE );
	MAP_ADD( AAFRESULT_INVALID_EDITHINT );
	MAP_ADD( AAFRESULT_INVALID_EFFECT );
	MAP_ADD( AAFRESULT_INVALID_EFFECTARG );
	MAP_ADD( AAFRESULT_INVALID_EFFECTDEF );
	MAP_ADD( AAFRESULT_INVALID_ENUM_VALUE );
	MAP_ADD( AAFRESULT_INVALID_FILE_MOB );
	MAP_ADD( AAFRESULT_INVALID_FILMTYPE );
	MAP_ADD( AAFRESULT_INVALID_INTERPKIND );
	MAP_ADD( AAFRESULT_INVALID_LINKAGE );
	MAP_ADD( AAFRESULT_INVALID_MOBTYPE );
	MAP_ADD( AAFRESULT_INVALID_OBJ );
	MAP_ADD( AAFRESULT_INVALID_OP_CODEC );
	MAP_ADD( AAFRESULT_INVALID_PARAM );
	MAP_ADD( AAFRESULT_INVALID_PARM_SIZE );
	MAP_ADD( AAFRESULT_INVALID_ROUNDING );
	MAP_ADD( AAFRESULT_INVALID_SEARCH_CRIT );
	MAP_ADD( AAFRESULT_INVALID_TAPECASETYPE );
	MAP_ADD( AAFRESULT_INVALID_TAPEFORMATTYPE );
	MAP_ADD( AAFRESULT_INVALID_TIMECODE );
	MAP_ADD( AAFRESULT_INVALID_TRACKKIND );
	MAP_ADD( AAFRESULT_INVALID_TRACK_REF );
	MAP_ADD( AAFRESULT_INVALID_TRANSPARENCY );
	MAP_ADD( AAFRESULT_INVALID_TRAN_EFFECT );
	MAP_ADD( AAFRESULT_INVALID_VIDEOSIGNALTYPE );
	MAP_ADD( AAFRESULT_IS_ROOT_CLASS );
	MAP_ADD( AAFRESULT_ITER_WRONG_TYPE );
	MAP_ADD( AAFRESULT_JPEGBASELINE );
	MAP_ADD( AAFRESULT_JPEGDISABLED );
	MAP_ADD( AAFRESULT_JPEGPCM );
	MAP_ADD( AAFRESULT_JPEGPROBLEM );
	MAP_ADD( AAFRESULT_LEADING_TRAN );
	MAP_ADD( AAFRESULT_MAXCODE );
	MAP_ADD( AAFRESULT_MEDIASTREAM_NOTALLOWED );
	MAP_ADD( AAFRESULT_MEDIA_CANNOT_CLOSE );
	MAP_ADD( AAFRESULT_MEDIA_NOT_FOUND );
	MAP_ADD( AAFRESULT_MEDIA_NOT_INIT );
	MAP_ADD( AAFRESULT_MEDIA_NOT_REVERTABLE );
	MAP_ADD( AAFRESULT_MEDIA_OPENMODE );
	MAP_ADD( AAFRESULT_MISSING_MEDIA_REP );
	MAP_ADD( AAFRESULT_MISSING_MOBID );
	MAP_ADD( AAFRESULT_MISSING_SWAP_PROC );
	MAP_ADD( AAFRESULT_MISSING_TRACKID );
	MAP_ADD( AAFRESULT_MOB_NOT_FOUND );
	MAP_ADD( AAFRESULT_MULTI_WRITELEN );
	MAP_ADD( AAFRESULT_NEED_PRODUCT_IDENT );
	MAP_ADD( AAFRESULT_NOAUDIOCONV );
	MAP_ADD( AAFRESULT_NOBYTEORDER );
	MAP_ADD( AAFRESULT_NODATA );
	MAP_ADD( AAFRESULT_NOFRAMEINDEX );
	MAP_ADD( AAFRESULT_NOMEMORY );
	MAP_ADD( AAFRESULT_NOT_AAF_FILE );
	MAP_ADD( AAFRESULT_NOT_A_TRACK );
	MAP_ADD( AAFRESULT_NOT_COMPOSITION );
	MAP_ADD( AAFRESULT_NOT_EXTENDABLE );
	MAP_ADD( AAFRESULT_NOT_FILEMOB );
	MAP_ADD( AAFRESULT_NOT_IMPLEMENTED );
	MAP_ADD( AAFRESULT_NOT_INITIALIZED );
	MAP_ADD( AAFRESULT_NOT_IN_CURRENT_VERSION );
	MAP_ADD( AAFRESULT_NOT_LONGWORD );
	MAP_ADD( AAFRESULT_NOT_OPEN );
	MAP_ADD( AAFRESULT_NOT_READABLE );
	MAP_ADD( AAFRESULT_NOT_REGISTERED );
	MAP_ADD( AAFRESULT_NOT_REVERTABLE );
	MAP_ADD( AAFRESULT_NOT_SOURCE_CLIP );
	MAP_ADD( AAFRESULT_NOT_WRITEABLE );
	MAP_ADD( AAFRESULT_NO_ESSENCE_DESC );
	MAP_ADD( AAFRESULT_NO_MORE_FLAVOURS );
	MAP_ADD( AAFRESULT_NO_MORE_MOBS );
	MAP_ADD( AAFRESULT_NO_MORE_OBJECTS );
	MAP_ADD( AAFRESULT_NO_TIMECODE );
	MAP_ADD( AAFRESULT_NULLBUF );
	MAP_ADD( AAFRESULT_NULLOBJECT );
	MAP_ADD( AAFRESULT_NULL_CALLBACKFUNC );
	MAP_ADD( AAFRESULT_NULL_MATCHFUNC );
	MAP_ADD( AAFRESULT_NULL_PARAM );
	MAP_ADD( AAFRESULT_NULL_STREAMPROC );
	MAP_ADD( AAFRESULT_OBJECT_ALREADY_ATTACHED );
	MAP_ADD( AAFRESULT_OBJECT_ALREADY_IN_FILE );
	MAP_ADD( AAFRESULT_OBJECT_ALREADY_PERSISTENT );
	MAP_ADD( AAFRESULT_OBJECT_NOT_ATTACHED );
	MAP_ADD( AAFRESULT_OBJECT_NOT_FOUND );
	MAP_ADD( AAFRESULT_OBJECT_NOT_IN_FILE );
	MAP_ADD( AAFRESULT_OBJECT_NOT_PERSISTENT );
	MAP_ADD( AAFRESULT_OBJECT_SEMANTIC );
	MAP_ADD( AAFRESULT_OFFSET_SIZE );
	MAP_ADD( AAFRESULT_ONESAMPLEREAD );
	MAP_ADD( AAFRESULT_ONESAMPLEWRITE );
	MAP_ADD( AAFRESULT_OPERATION_NOT_PERMITTED );
	MAP_ADD( AAFRESULT_OPLIST_OVERFLOW );
	MAP_ADD( AAFRESULT_OVERFLOW64 );
	MAP_ADD( AAFRESULT_PARAMETER_NOT_FOUND );
	MAP_ADD( AAFRESULT_PARSE_EFFECT_AMBIGUOUS );
	MAP_ADD( AAFRESULT_PLUGIN_ALREADY_REGISTERED );
	MAP_ADD( AAFRESULT_PLUGIN_CIRCULAR_REFERENCE );
	MAP_ADD( AAFRESULT_PLUGIN_INVALID_REFERENCE_COUNT );
	MAP_ADD( AAFRESULT_PLUGIN_NOT_REGISTERED );
	MAP_ADD( AAFRESULT_PROPERTY_DUPLICATE );
	MAP_ADD( AAFRESULT_PROPERTY_NOT_FOUND );
	MAP_ADD( AAFRESULT_PROPID_MATCH );
	MAP_ADD( AAFRESULT_PROP_ALREADY_PRESENT );
	MAP_ADD( AAFRESULT_PROP_NOT_PRESENT );
	MAP_ADD( AAFRESULT_PULLDOWN_DIRECTION );
	MAP_ADD( AAFRESULT_PULLDOWN_FUNC );
	MAP_ADD( AAFRESULT_PULLDOWN_KIND );
	MAP_ADD( AAFRESULT_RENDER_NOT_FOUND );
	MAP_ADD( AAFRESULT_REQUIRED_POSITIVE );
	MAP_ADD( AAFRESULT_SEGMENT_NOT_FOUND );
	MAP_ADD( AAFRESULT_SINGLE_CHANNEL_OP );
	MAP_ADD( AAFRESULT_SLOT_EXISTS );
	MAP_ADD( AAFRESULT_SLOT_NOT_FOUND );
	MAP_ADD( AAFRESULT_SMALLBUF );
	MAP_ADD( AAFRESULT_SOURCEMOBLIST );
	MAP_ADD( AAFRESULT_STILLFRAME_BADLENGTH );
	MAP_ADD( AAFRESULT_STRACK_APPEND_ILLEGAL );
	MAP_ADD( AAFRESULT_STREAM_CLOSED );
	MAP_ADD( AAFRESULT_STREAM_REOPEN );
//	MAP_ADD( AAFRESULT_SUCCEEDED(Status) );
	MAP_ADD( AAFRESULT_SUCCESS );
	MAP_ADD( AAFRESULT_SWAB );
	MAP_ADD( AAFRESULT_SWABBUFSIZE );
	MAP_ADD( AAFRESULT_SWAP_SETUP );
	MAP_ADD( AAFRESULT_TABLE_BAD_HDL );
	MAP_ADD( AAFRESULT_TABLE_BAD_ITER );
	MAP_ADD( AAFRESULT_TABLE_DUP_KEY );
	MAP_ADD( AAFRESULT_TABLE_MISSING_COMPARE );
	MAP_ADD( AAFRESULT_TAPE_DESC_ONLY );
	MAP_ADD( AAFRESULT_TEST_FAILED );
	MAP_ADD( AAFRESULT_TEST_PARTIAL_SUCCESS );
	MAP_ADD( AAFRESULT_TIFFVERSION );
	MAP_ADD( AAFRESULT_TIMECODE_NOT_FOUND );
	MAP_ADD( AAFRESULT_TOO_MANY_FMT_OPS );
	MAP_ADD( AAFRESULT_TOO_MANY_TYPES );
	MAP_ADD( AAFRESULT_TRANSLATE );
	MAP_ADD( AAFRESULT_TRANSLATE_NON_INTEGRAL_RATE );
	MAP_ADD( AAFRESULT_TRANSLATE_SAMPLE_SIZE );
	MAP_ADD( AAFRESULT_TRAVERSAL_NOT_POSS );
	MAP_ADD( AAFRESULT_TYPE_NOT_FOUND );
	MAP_ADD( AAFRESULT_TYPE_SEMANTIC );
	MAP_ADD( AAFRESULT_UNEXPECTED_EXCEPTION );
	MAP_ADD( AAFRESULT_UNKNOWN_CONTAINER );
	MAP_ADD( AAFRESULT_UNKNOWN_PARAMETER_CLASS );
	MAP_ADD( AAFRESULT_UNSAVED_CHANGES );
	MAP_ADD( AAFRESULT_WRONG_FILETYPE );
	MAP_ADD( AAFRESULT_WRONG_MEDIATYPE );
	MAP_ADD( AAFRESULT_WRONG_OPENMODE );
	MAP_ADD( AAFRESULT_WRONG_SIZE );
	MAP_ADD( AAFRESULT_XFER_DUPCH );
	MAP_ADD( AAFRESULT_XFER_NOT_BYTES );
	MAP_ADD( AAFRESULT_ZERO_DIVIDE );
	MAP_ADD( AAFRESULT_ZERO_PIXELSIZE );
	MAP_ADD( AAFRESULT_ZERO_SAMPLESIZE );
	MAP_ADD( AAFRESULT_EVENT_SEMANTICS );

	// Misc. Win32 errors.
#if defined(OS_WINDOWS)

	MAP_ADD( ERROR_MOD_NOT_FOUND );
	MAP_ADD( E_NOINTERFACE );
	MAP_ADD( STG_E_FILEALREADYEXISTS );
	MAP_ADD( STG_E_PATHNOTFOUND );

	// FIXME - Find out what proprocessor macro defines this.
	// I would have expected ERROR_MOD_NOT_FOUND ????
	_map[ 0x8007007E ] = L"The specified module could not be found. ";
	
	// What is the macro definition for 0x80030111? The MSVC++ Error Lookup tool 
	// was used to translate it.  It is a structured storage error generated when
	// the SS file exceeds 2GB when writting large amounts of essence data.
	_map[ 0x80030111 ] = L"The compound file is too large for the current implementation.";
#endif

#undef MAP_ADD
}

const AxHrMap& AxHrMap::getInstance()
{
	static AxHrMap* instance = 0;

	if ( !instance ) {
		instance = new AxHrMap;
	}
	
	return *instance;
}

AxHrMap::~AxHrMap()
{}

const AxString& AxHrMap::getStr( HRESULT hr ) const
{
	// The only possible error is if hr is not found in the
	// map. This method is called from AxExHresult.  Avoid a
	// double exception by simply returning the hrUnkownStr to
	// indicate the error.

	std::map<HRESULT,AxString>::const_iterator iter = _map.find( hr );
	
	if ( iter == _map.end() ) {
		return hrUnkownStr;
	}

	return iter->second;
}
