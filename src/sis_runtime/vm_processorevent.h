#ifndef VM_PROCESSOR_EVENT_H
#define VM_PROCESSOR_EVENT_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Includes
//
#include "vm_runtime_global.h"
#include "vm_event.h"
#include <sis_core.h>
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class CProcessor;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace vm {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class SIS_RUNTIME_EXPORT CProcEvent : public CVMEvent
{
public:
	// Constructor and destructor
	inline CProcEvent( type eType )
		: CVMEvent( eType )
	{
	}
	virtual ~CProcEvent() = default;

protected:
	// Evaluate action for event manager
	virtual bool Eval( CVMEventManager* pEventManager ) const override final;
	// Evaluate action for processor
	virtual void Eval( CProcessor* pProcessor ) const = 0;
};


class SIS_RUNTIME_EXPORT CBreakEvent : public CProcEvent
{
public:
	// Constructor and destructor
	inline CBreakEvent( )
		: CProcEvent( type::Break )
	{
	}
	virtual ~CBreakEvent() = default;

protected:
	// Evaluate action for processor
	virtual void Eval( CProcessor* pProcessor ) const override;
};


class SIS_RUNTIME_EXPORT CContinueEvent final : public CProcEvent
{
public:
	// Constructor and destructor
	inline CContinueEvent()
		: CProcEvent( type::Continue )
	{
	}
	virtual ~CContinueEvent() = default;

protected:
	// Evaluate action for processor
	virtual void Eval( CProcessor* pProcessor ) const override;
};


class SIS_RUNTIME_EXPORT CStepInEvent final : public CProcEvent
{
public:
	// Constructor and destructor
	inline CStepInEvent()
		: CProcEvent( type::StepIn )
	{
	}
	virtual ~CStepInEvent() = default;

protected:
	// Evaluate action for processor
	virtual void Eval( CProcessor* pProcessor ) const override;
};


class SIS_RUNTIME_EXPORT CStepOutEvent final : public CProcEvent
{
public:
	// Constructor and destructor
	inline CStepOutEvent()
		: CProcEvent( type::StepOut )
	{
	}
	virtual ~CStepOutEvent() = default;

protected:
	// Evaluate action for processor
	virtual void Eval( CProcessor* pProcessor ) const override;
};


class SIS_RUNTIME_EXPORT CStepOverEvent final : public CProcEvent
{
public:
	// Constructor and destructor
	inline CStepOverEvent()
		: CProcEvent( type::StepOver )
	{
	}
	virtual ~CStepOverEvent() = default;

protected:
	// Evaluate action for processor
	virtual void Eval( CProcessor* pProcessor ) const override;
};


class SIS_RUNTIME_EXPORT CNewProcessorEvent final : public CProcEvent
{
public:
	// Constructor and destructor
	inline CNewProcessorEvent( CModuleRef oModule )
		: CProcEvent( type::NewProcessor ),
	      m_oModule( oModule )
	{
	}
	virtual ~CNewProcessorEvent() = default;

protected:
	// Evaluate action for processor
	virtual void Eval( CProcessor* pProcessor ) const override;

private:
	// Members
	CModuleRef m_oModule;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace vm
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // VM_PROCESSOR_EVENT_H
// end of file
