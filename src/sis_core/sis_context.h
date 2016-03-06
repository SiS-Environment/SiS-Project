#ifndef SIS_CONTEXT_H
#define SIS_CONTEXT_H

////////////////////////////////////////////////////////////////////////////
//	includes
//
#include "sis_core_global.h"
#include "sis_buffer.h"
#include "sis_function.h"
//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////

class SIS_CORE_EXPORT CContext
{
public:
	//
	//	Type definitions
	//
	class SIS_CORE_EXPORT CStack : public CBuffer
	{
	public:
		inline CStack();
		inline CStack( byte* pBuffer, uint64 uSize );

	private:
		byte* m_pStack;
	};

public:
	// Constructor
	inline CContext( CBuffer const& oStack );

public:
	// Interface methods
	inline CStack& Stack();
	inline CStack const& Stack() const;

	inline void IncrementPC( uint64 uOffset );

private:
	// Members
	uint64 m_PC;  //offset
	CFunction m_oFunc;
	CStack m_oStack;
};

////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////


// include inl impl
//#include "sis_context_imp.h"


#endif // SIS_CONTEXT_H
