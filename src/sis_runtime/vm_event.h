#ifndef VM_EVENT_H
#define VM_EVENT_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Includes
//
#include "vm_runtime_global.h"
//
#include <sis_core.h>
// STL
#include <atomic>
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class CVMEventManager;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace vm {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


enum class EVMEventType
{
	LoadModul = 1,
	Exeption = 2,
	NewProcessor = 3,

	// Events for debugging
	Break = 4,
	Continue = 5,
	StepIn = 6,
	StepOver = 7,
	StepOut = 8,
	Stop = 9,
};


class SIS_RUNTIME_EXPORT CVMEvent
{
protected:
	typedef EVMEventType type;

public:
	// Constructor and destructor
	inline CVMEvent( type eType )
		: m_eType( eType ),
		  m_bAccepted()
	{
		m_bAccepted = false;
	}
	virtual ~CVMEvent() = default;

public:
	// Interface methods

	inline type Type() const
	{
		return m_eType;
	}
	
	inline void SetAccepted( bool bAccepted )
	{
		m_bAccepted = bAccepted;
	}
	inline void Accept( CVMEventManager* pEventManager )
	{
		bool bSuccess = Eval( pEventManager );
		SetAccepted( bSuccess );
	}

	inline void Ignore()
	{
		SetAccepted( false );
	}

	inline bool IsAccepted() const
	{
		return m_bAccepted;
	}
	inline bool IsIgnored() const
	{
		return !IsAccepted( );
	}

protected:
	// Evaluate action for processor
	virtual bool Eval( CVMEventManager* pEventManager ) const = 0;

private:
	// Members
	type m_eType;
	std::atomic_bool m_bAccepted;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace vm
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // VM_EVENT_H
// end of file
