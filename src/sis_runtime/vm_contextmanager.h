#ifndef VM_CONTEXT_MANAGER_H
#define VM_CONTEXT_MANAGER_H

////////////////////////////////////////////////////////////////////////////
//	includes
//
#include <sis_context.h>
// STL
#include <iostream>
#include <stack>
#include <stdexcept>
//
////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////
namespace vm {
////////////////////////////////////////////////////////////////////////////


class CContextManager
{
private:
	//
	//	Static members
	//	
	static const uint64 s_cuSize;		// size of one mb

public:
	// Constructor and destructor
	CContextManager();
	~CContextManager();

	// Copy constructor and assignment operator
	CContextManager( const CContextManager& ) = delete;
	CContextManager& operator=(const CContextManager&) = delete;

public:
	// Interface methods

	CContext* Alloc( uint64 uStackSize );
	void Free( CContext* );

	inline CContext* GetCurrent() const;	
	inline uint64 GetContextCount() const;	

private:
	// Members
	std::stack<CBuffer> m_oBuffer;
	std::stack<uint64> m_uMarker;
	CContext* mp_currContext;
	uint64 m_contextCount;
};


////////////////////////////////////////////////////////////////////////////////////
} // namespace vm
////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////


#endif // CONTEXT_MANAGER
// end of file
