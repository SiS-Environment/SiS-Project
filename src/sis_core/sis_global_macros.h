#ifndef SIS_GLOBAL_MACROS_H
#define SIS_GLOBAL_MAXROS_H


//////////////////////////////////////////////////////////////////////////////////
//	Global macros
//
#ifdef _WIN32 || _WIN64
#	ifndef SIS_EXPORT
#		define SIS_EXPORT	__declspec(dllexport)
#		define SIS_IMPORT	__declspec(dllimport)
#	endif
#else
#	define SIS_EXPORT
#	define SIS_IMPORT
#endif
//
//////////////////////////////////////////////////////////////////////////////////

#endif // SIS_GLOBAL_MAXROS_H
// end of file
