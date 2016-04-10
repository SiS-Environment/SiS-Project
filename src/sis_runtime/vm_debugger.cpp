////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Includes
//
#include "vm_controller.h"
#include "vm_processor.h"
#include "vm_event.h"
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace vm {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


CController::CDebugger::CDebugger(  CController* pController )
	: IDebugger(),
	  IIntDebugger(),
	  CNotifier(),
	  m_pController( pController )
{
}


void CController::CDebugger::StepIn( ProcID nID ) const
{
	CProcessor* pProcessor = m_pController->GetProcessor( nID );
	SIS_CHECKPTR( pProcessor );
	CProcEvent* pEvent = new CStepInEvent;
	pProcessor->AddEvent( pEvent );
}


void CController::CDebugger::StepOut( ProcID nID ) const
{
	CProcessor* pProcessor = m_pController->GetProcessor( nID );
	SIS_CHECKPTR( pProcessor );
	CProcEvent* pEvent = new CStepOutEvent;
	pProcessor->AddEvent( pEvent );
}


void CController::CDebugger::StepOver( ProcID nID ) const
{
	CProcessor* pProcessor = m_pController->GetProcessor( nID );
	SIS_CHECKPTR( pProcessor );
	CProcEvent* pEvent = new CStepOverEvent;
	pProcessor->AddEvent( pEvent );
}


void CController::CDebugger::Continue( ProcID nID ) const
{
	if ( -1 == nID )
		ContinueAll();

	CProcessor* pProcessor = m_pController->GetProcessor( nID );
	SIS_CHECKPTR( pProcessor );
	CProcEvent* pEvent = new CContinueEvent;
	pProcessor->AddEvent( pEvent );
}


void CController::CDebugger::Stop( ProcID nID ) const
{
	if ( -1 == nID )
		StopAll();

	CProcessor* pProcessor = m_pController->GetProcessor( nID );
	SIS_CHECKPTR( pProcessor );
	CProcEvent* pEvent = new CBreakEvent;
	pProcessor->AddEvent( pEvent );
}


void CController::CDebugger::NotifyBreak() const
{
	StopAll();
	Notify();
}


void CController::CDebugger::ContinueAll() const
{
	for ( ProcID nID = 0; nID < m_pController->GetProcessorCount( ); ++nID )
		Continue( nID );
}


void CController::CDebugger::StopAll() const
{
	for ( ProcID nID = 0; nID < m_pController->GetProcessorCount( ); ++nID )
		Stop( nID );
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace vm
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
