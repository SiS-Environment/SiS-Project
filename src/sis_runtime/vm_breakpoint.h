#ifndef VM_BREAKPOINT_H
#define VM_BREAKPOINT_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Includes
//
#include "vm_runtime_global.h"
//
#include <sis_core.h>
// STL
#include <string>
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace vm {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class SIS_RUNTIME_EXPORT CBreakPoint
{
public:
	//
	//	Type definitions
	//
	class CLocation
	{
	public:
		// Constructor and destructor
		CLocation( std::string const& sFile, uint64 uLine )
			: m_csFile( sFile ),
			  m_cuLine( uLine )
		{
		}
		~CLocation() = default;

		// Copy constructor and assignment operator
		CLocation( CLocation const& ) = default;
		CLocation& operator=( CLocation const& ) = default;

	public:
		// Interface methods
		
		inline std::string const& FileName() const
		{
			return m_csFile;
		}
		inline uint64 GetLine() const
		{
			return m_cuLine;
		}

	private:
		// Members
		const std::string	m_csFile;
		const uint64		m_cuLine;
	};

public:
	// Constructor and destructor
	CBreakPoint( CLocation const& oLocation )
		: m_bEnabled( true ),
		  m_oLocation( oLocation )
	{
	}
	~CBreakPoint() = default;

	// Copy constructor and assignment operator
	CBreakPoint( CBreakPoint const& ) = delete;
	CBreakPoint& operator=( CBreakPoint const& ) = delete;

public:
	// Interface methods

	inline bool IsEnabled() const
	{
		return m_bEnabled;
	}
	inline void SetEnabled( bool b )
	{
		m_bEnabled = b;
	}
	inline void Enable()
	{
		SetEnabled( true );
	}
	inline void Disable()
	{
		SetEnabled( false );
	}

	inline CLocation const& Location() const
	{
		return m_oLocation;
	}

private:
	// Members
	bool m_bEnabled;
	CLocation m_oLocation;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace vm
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // VM_BREAKPOINT_H
// end of file
