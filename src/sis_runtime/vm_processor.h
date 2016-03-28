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
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace vm {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class IExpression;
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
	virtual ~CProcessor() = default;

	// Copy constructor and assignment operator
	CProcessor( CProcessor const& ) = delete;
	CProcessor& operator=( CProcessor const& ) = delete;

public:
	// Interface methods
	void Run( std::string const& sModuleName );

	// Enter to main loop
	void Enter();
	// Enter to main loop for debug mode
	void EnterDebug();

	// Debugging functions
	void StepIn();
	void StepOut();
	void StepOver();

	// Stop main loop
	void Stop();
	void Continue();

	// Load from module
	void LoadModule( std::string const& sModuleName, offset uOffset = -1 );

	// Get controller pointer
	CController* GetContoller() const
	{
		return m_pController;
	}

private:
	// Handle events
	virtual void HandleEvents() override;

	// Check breakpoint existence, only for debug mode
	void CheckBreakPoint();

private:
	// Members
	CController* m_pController;
	CModuleManager* m_pModuleManager;
	CContextManager m_oContextManager;
	bool m_bKeepRunning;
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
