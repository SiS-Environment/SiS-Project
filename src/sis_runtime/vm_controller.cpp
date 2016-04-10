////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Includes
//
#include "vm_controller.h"
#include "vm_modulemanager.h"
#include "vm_processor.h"
// STL
#include <algorithm>
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace vm {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


CController::CController( CModuleManager* pModuleManager, IListener* pDebugger )
	  : m_pModuleManager( pModuleManager ),
		m_pDebugger( nullptr ),
	    m_arrProcessors()
{
	SIS_CHECKPTR( m_pModuleManager );
	if ( nullptr != pDebugger )
	{
		m_pDebugger = new CDebugger( this );
		m_pDebugger->Attach( pDebugger );
	}
}


CController::~CController()
{
	// Kill processors
	KillAll();
	// delete debugger
	if ( nullptr != m_pDebugger )
		delete m_pDebugger;
}


CProcessor* CController::CreateProcessor()
{
	CProcessor* pProcessor = new CProcessor( m_pModuleManager, this );
	m_arrProcessors.push_back( pProcessor ); 
	return pProcessor;
}


void CController::Start()
{
	RunNewProcessor();
}


void CController::RunNewProcessor()
{
	CProcessor* pProcessor = CreateProcessor();
	SIS_CHECKPTR( pProcessor );
	pProcessor->Run( ( nullptr == m_pDebugger ) ? false : true );
}


void CController::KillAll()
{
	while ( !m_arrProcessors.empty() )
	{
		CProcessor* pProcessor = m_arrProcessors.back();
		if ( pProcessor != nullptr )
			delete pProcessor;

		m_arrProcessors.pop_back();
	}
}


void CController::KillProcessor( CProcessor* pProcessor )
{
	if ( nullptr == pProcessor )
		return;

	std::vector<CProcessor*>::iterator iter = std::find( m_arrProcessors.begin(), m_arrProcessors.end(), pProcessor );
	if ( m_arrProcessors.end() != iter )
	{
		m_arrProcessors.erase( iter );
		delete pProcessor;
	}
}


CProcessor* CController::GetProcessor( ProcID nID ) const
{
	if ( nID < 0 || nID >= GetProcessorCount() )
		throw std::range_error( "Invalid processor ID" );

	return m_arrProcessors[size_t( nID )];
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace vm
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
