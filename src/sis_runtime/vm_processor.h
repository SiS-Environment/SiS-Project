#ifndef VM_PROCESSOR_H
#define VM_PROCESSOR_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Includes
//
#include "vm_runtime_global.h"
#include "vm_contextmanager.h"
#include "vm_eventmanager.h"
#include <sis_context.h>
#include <sis_module.h>
// STL
#include <string>
#include <queue>
#include <stack>
#include <thread>
#include <atomic>
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

class IExpression;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace vm {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class CModuleManager;
class CController;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	class CProcessor
//
class CProcessor final : public CVMEventManager
{
public:
	// Constructors, destructor
	CProcessor( CModuleManager* pModuleManager, CController* pController );
	virtual ~CProcessor();

	// Copy constructor and assignment operator
	CProcessor( CProcessor const& ) = delete;
	CProcessor& operator=( CProcessor const& ) = delete;

public:
	// Interface methods

	// Main function
	void Run( bool bDebug );

	// Enter to main loop
	inline void Enter()
	{
		if ( IsStopped() )
			m_oThread = std::thread( &CProcessor::_Enter, this );
	}
	// Enter to main loop for debug mode
	inline void EnterDebug()
	{
		if ( IsStopped() )
			m_oThread = std::thread( &CProcessor::_EnterDebug, this );
	}

	// Debugging functions
	inline void StepIn()
	{
		if ( IsStopped() )
			m_oThread = std::thread( &CProcessor::_StepIn, this );
	}
	inline void StepOut()
	{
		if ( IsStopped() )
			m_oThread = std::thread( &CProcessor::_StepOut, this );
	}
	inline void StepOver()
	{
		if ( IsStopped() )
			m_oThread = std::thread( &CProcessor::_StepOver, this );
	}

	// Stop main loop
	inline void Stop()
	{
		if ( IsRunning() )
			_Stop();
	}
	inline void Continue()
	{
		if ( IsStopped() )
			m_oThread = std::thread( &CProcessor::_Continue, this );
	}

	// Get controller pointer
	inline CController* GetContoller() const
	{
		return m_pController;
	}

	// Check state
	inline bool IsRunning() const
	{
		return m_bKeepRunning;
	}
	inline bool IsStopped() const
	{
		return !IsRunning();
	}

protected:
	// Handle events
	virtual void HandleEvents() override;

private:
	// Helper functions
	void _Enter();
	void _EnterDebug();
	void _StepIn();
	void _StepOut();
	void _StepOver();
	void _Stop();
	void _Continue();

	// Check breakpoint existence, only for debug mode
	void CheckBreakPoint();

private:
	// Members
	std::thread			m_oThread;
	CController*		m_pController;
	CModuleManager*		m_pModuleManager;
	CContextManager		m_oContextManager;
	std::atomic_bool	m_bKeepRunning;
};
//	CController
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace vm
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // VM_PROCESSOR_H
// end of file
