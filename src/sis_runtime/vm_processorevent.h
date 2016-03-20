#ifndef VM_PROCESSOR_EVENT_H
#define VM_PROCESSOR_EVENT_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Includes
//
#include "vm_runtime_global.h"
#include <sis_core.h>
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class CProcessor;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace vm {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


enum class EProcEventType
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


class SIS_RUNTIME_EXPORT CProcEvent
{
protected:
	typedef EProcEventType type;

public:
	// Constructor and destructor
	inline CProcEvent( type eType )
		: m_eType( eType ),
		  m_bAccepted( false )
	{ 
	}
	virtual ~CProcEvent() = default;

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
	inline void Accept( CProcessor* pProcessor )
	{
		if ( nullptr != pProcessor )
		{
			Eval( pProcessor );
			SetAccepted( true );
		}
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
		return !IsAccepted();
	}

protected:
	// Evaluate action for processor
	virtual void Eval( CProcessor* pProcessor ) = 0;

private:
	// Members
	type m_eType;
	bool m_bAccepted;
};


class SIS_RUNTIME_EXPORT CBreakEvent : public CProcEvent
{
public:
	// Constructor and destructor
	inline CBreakEvent( uint64 uLine )
		: CProcEvent( type::Break ),
		  m_cuLine( uLine )
	{
	}
	virtual ~CBreakEvent() = default;

public:
	// Interface methods
	inline uint64 GetLine() const
	{
		return m_cuLine;
	}

protected:
	// Evaluate action for processor
	virtual void Eval( CProcessor* pProcessor ) const;

private:
	// Members
	uint64 const m_cuLine;
};


class SIS_RUNTIME_EXPORT CLoadModulEvent final : public CProcEvent
{
public:
	// Constructor and destructor
	inline CLoadModulEvent( std::string const& sModuleName, offset uOffset )
		: CProcEvent( type::LoadModul ),
		  m_csModuleName( sModuleName ),
		  m_cuOffset( uOffset )
	{
	}
	virtual ~CLoadModulEvent() = default;

public:
	// Interface methods
	inline std::string const& ModuleName() const
	{ 
		return m_csModuleName;
	}
	inline offset GetOffset() const
	{
		return m_cuOffset;
	}

protected:
	// Evaluate action for processor
	virtual void Eval( CProcessor* pProcessor ) const;

private:
	// Members
	std::string const m_csModuleName;
	offset const m_cuOffset;
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
	virtual void Eval( CProcessor* pProcessor ) const;
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
	virtual void Eval( CProcessor* pProcessor ) const;
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
	virtual void Eval( CProcessor* pProcessor ) const;
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
	virtual void Eval( CProcessor* pProcessor ) const;
};


class SIS_RUNTIME_EXPORT CNewProcessorEvent final : public CProcEvent
{
public:
	// Constructor and destructor
	inline CNewProcessorEvent( std::string const& sModuleName )
		: CProcEvent( type::NewProcessor ),
	      m_csModule( sModuleName )
	{
	}
	virtual ~CNewProcessorEvent() = default;

protected:
	// Evaluate action for processor
	virtual void Eval( CProcessor* pProcessor ) const;

private:
	// Members
	std::string const m_csModule;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace vm
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // VM_PROCESSOR_EVENT_H
// end of file
