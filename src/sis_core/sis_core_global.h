#ifndef SIS_CORE_GLOBAL_H
#define SIS_CORE_GLOBAL_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Includes
//
#include "sis_global_types.h"
#include "sis_global_macros.h"
//#include "sis_buffer.h"
//#include "sis_module.h"
//#include "sis_function.h"
//#include "sis_context.h"

// STL Includes
#include <list>
#include <vector>
#include <string>
#include <memory>
#include <exception>
#include <stdexcept>
#include <cassert>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Helper macros
//
#ifdef SIS_CORE_LIB
#	define SIS_CORE_EXPORT SIS_EXPORT
#else
#	define SIS_CORE_EXPORT SIS_IMPORT
#endif
//
#ifdef _DEBUG
#	define	SIS_ASSERT( _cond_ )			assert( _cond_ )
#	define	SIS_ASSERTX( _cond_, _msg_ )	assert( _cond_, _msg_ )
#else
#	define	SIS_ASSERT(_cond_)
#	define	SIS_ASSERTX( _cond_, _msg_ )
#endif
//
#	define	SIS_CHECKPTR( _PTR_ )			if ( nullptr == _PTR_ ) { SIS_ASSERT(false); throw std::logic_error( "NULL pointer" ); }
#	define	SIS_CHECK( _cond_ )				if ( _cond_ ) { SIS_ASSERT(false); throw std::invalid_argument( "Invalid conditon" ); }
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // SIS_CORE_GLOBAL_H
// end of file
