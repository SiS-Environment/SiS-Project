#ifndef VM_CONTROLLER_H
#define VM_CONTROLLER_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Includes
//
#include "vm_runtime_global.h"
#include "vm_breakpoint.h"
//
#include <sis_listener.h>
#include <sis_module.h>
#include <sis_core.h>
#include <sis_listener.h>
//STL
#include <vector>
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace vm {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
class CProcessor;
class CModuleManager;
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	class CController
//
class SIS_RUNTIME_EXPORT CController
{
public:
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	Type definitions
	//
	typedef int64 ProcID;
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	class IBreakDebugger
	{
	public:
		// Constructor and destructor
		IBreakDebugger() = default;
		virtual ~IBreakDebugger() = default;

		// Copy constructor and assignment operator
		IBreakDebugger( IBreakDebugger const& ) = default;
		IBreakDebugger& operator=( IBreakDebugger const& ) = default;

	public:
		// Interface methods

		// Register breakpoint
		virtual void RegisterBreakPoint( CBreakPoint* ) = 0;
		// Unregister breakpoint
		virtual void UnRegisterBreakPoint( CBreakPoint::CLocation const& ) = 0;
		// Get break point
		virtual CBreakPoint* GetBreakPoint( CBreakPoint::CLocation const& ) = 0;
	};
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	IDebugger interface for debugger module
	//
	class IDebugger : virtual public IBreakDebugger
	{
	public:
		// Constructor and destructor
		IDebugger() = default;
		virtual ~IDebugger() = default;

		// Copy constructor and assignment operator
		IDebugger( IDebugger const& ) = default;
		IDebugger& operator=( IDebugger const& ) = default;

	public:
		// Interface methods

		// If ProcID is -1, than all processors will do corresponding command
		virtual void Continue( ProcID = -1 ) const = 0;
		virtual void Stop( ProcID = -1 ) const = 0;
		// ...
		virtual void StepIn( ProcID ) const = 0;
		virtual void StepOut( ProcID ) const = 0;
		virtual void StepOver( ProcID ) const = 0;
	};
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	IIntDebugger interface for processors
	//
	class IIntDebugger : virtual public IBreakDebugger
	{
	public:
		// Constructor and destructor
		IIntDebugger() = default;
		virtual ~IIntDebugger() = default;

		// Copy constructor and assignment operator
		IIntDebugger( IIntDebugger const& ) = default;
		IIntDebugger& operator=( IIntDebugger const& ) = default;

	public:
		// Interface methods
		virtual void NotifyBreak() const = 0;
	};
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//	class debugger
	//
	class CDebugger final : public IDebugger, public IIntDebugger, public CNotifier
	{
	public:
		// Constructor and destructor
		CDebugger( CController* );
		virtual ~CDebugger() = default;

		// Copy constructor and assignment operator
		CDebugger( CDebugger const& ) = delete;
		CDebugger& operator=( CDebugger const& ) = delete;

	public:
		// Interface methods

		// Interface IDebugger
		virtual void StepIn( ProcID nID ) const override;
		virtual void StepOut( ProcID nID ) const override;
		virtual void StepOver( ProcID nID ) const override;
		virtual void Continue( ProcID nID ) const override;
		virtual void Stop( ProcID nID ) const override;

		// Interface IIntDebugger
		virtual void NotifyBreak() const override;

		virtual void RegisterBreakPoint( CBreakPoint* ) override;						// TODO
		virtual void UnRegisterBreakPoint( CBreakPoint::CLocation const& ) override;	// TODO
		virtual CBreakPoint* GetBreakPoint( CBreakPoint::CLocation const& ) override;	// TODO

	private:
		//  Helper functions
		void ContinueAll() const;
		void StopAll() const;

	private:
		// Members
		CController* m_pController;
	};
	//
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
public:
	// Constructors, destructor
	CController( CModuleManager* pModuleManager, IListener* pDebugger = nullptr );
	virtual ~CController();

	// Copy constructor and assignment operator
	CController( CController const& ) = delete;
	CController& operator=( CController const& ) = delete;

public:
	// Interface methods

	// Start running
	void Start();
	// Create new processor and run it
	void RunNewProcessor();
	// Delete all processes
	void KillAll();

	// Debugging interface access methods
	inline IDebugger* GetDebugger() const
	{
		return m_pDebugger;
	}
	inline IIntDebugger* GetIntDebbuger() const
	{
		return m_pDebugger;
	}

	// ...
	inline int64 GetProcessorCount() const
	{
		return int64( m_arrProcessors.size() );
	}
	CProcessor* GetProcessor( ProcID nID ) const;
	
private:
	// Create new processor
	CProcessor* CreateProcessor();
	// Kill processor
	void KillProcessor( CProcessor* );

private:
	// Members
	CModuleManager* m_pModuleManager;
	CDebugger* m_pDebugger;
	std::vector<CProcessor*> m_arrProcessors;
};
//	CController
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace vm
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // VM_CONTROLLER_H
// end of file
