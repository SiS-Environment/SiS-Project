////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Includes
//
#include "vm_processor.h"
#include "vm_controller.h"
#include "vm_modulemanager.h"
#include "vm_contextmanager.h"
//
#include <sis_expression.h>
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace vm {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


CProcessor::CProcessor( CModuleManager* pModuleManager, CController* pController )
	: CVMEventManager(),
	  m_oThread(),
	  m_pController( pController ),
	  m_pModuleManager( pModuleManager ),
	  m_oContextManager(),
	  m_bKeepRunning()
{
	m_bKeepRunning = true;
	SIS_CHECKPTR( m_pController );
	SIS_CHECKPTR( m_pModuleManager );
}


CProcessor::~CProcessor()
{
	if ( m_oThread.joinable() )
		m_oThread.join();
}


void CProcessor::Run( bool bDebug )
{
	if ( bDebug )
		EnterDebug();
	else
		Enter();
}


void CProcessor::_Enter()
{
	offset uOffset = 0;
	CContext* pContext = nullptr;
	IExpression* pExpression = nullptr;
	m_bKeepRunning = true;
	do
	{
		pContext = m_oContextManager.GetCurrent();
		pContext->IncrementPC( uOffset );
		pExpression = pContext->ModuleRef()->GetExpression( pContext->GetPC() );
		uOffset = pExpression->Eval( pContext );
	}
	while ( IsRunning() );
}


void CProcessor::_EnterDebug()
{
	offset uOffset = 0;
	CContext* pContext = nullptr;
	IExpression* pExpression = nullptr;
	m_bKeepRunning = true;
	do
	{
		pContext = m_oContextManager.GetCurrent();
		pContext->IncrementPC( uOffset );
		pExpression = pContext->ModuleRef()->GetExpression( pContext->GetPC() );
		uOffset = pExpression->Eval( pContext );

		// Check break point
		CheckBreakPoint();
	}
	while ( IsRunning() );
}


void CProcessor::_StepIn()
{
	CContext* pContext = m_oContextManager.GetCurrent();
	IExpression* pExpression = pContext->ModuleRef()->GetExpression( pContext->GetPC() );
	offset uOffset = pExpression->Eval( pContext );
	pContext->IncrementPC( uOffset );
}


void CProcessor::_StepOut()
{
	uint64 const cuContextCount = m_oContextManager.GetContextCount();
	do
	{
		StepIn();
	}
	while ( m_oContextManager.GetContextCount() >= cuContextCount );
}


void CProcessor::_StepOver()
{
	uint64 const cuContextCount = m_oContextManager.GetContextCount( );
	StepIn();
	if ( m_oContextManager.GetContextCount() >= cuContextCount )
		StepOut();
}


void CProcessor::_Stop()
{
	m_bKeepRunning = false;
	if ( m_oThread.joinable() )
		m_oThread.join();
}


void CProcessor::_Continue()
{
	EnterDebug();
}


void CProcessor::HandleEvents()
{
	while ( !m_queEvents.empty() )
	{
		CProcEvent* pEvent = m_queEvents.front();
		if ( pEvent->IsIgnored() )
			pEvent->Accept( this );

		m_queEvents.pop();
		delete pEvent;
	}
}


void CProcessor::CheckBreakPoint()
{
	// TODO
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace vm
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
