////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Includes
//
#include "vm_processor.h"
#include "vm_controller.h"
#include "vm_modulemanager.h"
#include "vm_contextmanager.h"
#include <sis_expression.h>
// STL
#include <thread>
#include <chrono>
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace vm {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


CProcessor::CProcessor( CModuleManager* pModuleManager, CController* pController )
	: CVMEventManager(),
	  m_pController( pController ),
	  m_pModuleManager( pModuleManager ),
	  m_oContextManager(),
	  m_bKeepRunning( true )
{
	if ( nullptr == m_pController || nullptr == m_pModuleManager )
		throw - 1;	// TOOD
}



void CProcessor::Run( std::string const& sModuleName )
{
	LoadModule( sModuleName );
}


void CProcessor::Enter()
{
	offset uOffset = 0;
	CContext* pContext = nullptr;
	IExpression* pExpression = nullptr;
	m_bKeepRunning = true;
	do
	{
		pContext = m_oContextManager.Current();
		pContext->IncrementPC( uOffset );
		pExpression = pContext->ModuleRef()->GetExpression( pContext->GetPC() );
		uOffset = pExression->Eval( pContext );

		HandleEvents();
	}
	while ( m_bKeepRunning );
}


void CProcessor::EnterDebug()
{
	offset uOffset = 0;
	CContext* pContext = nullptr;
	IExpression* pExpression = nullptr;
	m_bKeepRunning = true;
	do
	{
		pContext = m_oContextManager.Current();
		pContext->IncrementPC( uOffset );
		pExpression = pContext->ModuleRef()->GetExpression( pContext->GetPC() );
		uOffset = pExression->Eval( pContext );

		CheckBreakPoint();
		HandleEvents();
	}
	while ( m_bKeepRunning );
}


void CProcessor::StepIn()
{
	CContext* pContext = m_oContextManager.Current();
	IExpression* pExpression = pContext->ModuleRef()->GetExpression( pContext->GetPC( ) );
	offset uOffset = pExpression->Eval();
	pContext->IncrementPC( uOffset );
}


void CProcessor::StepOut()
{
	uint64 const cuContextCount = m_oContextManager.GetContextCount();
	do
	{
		StepIn();
	}
	while ( m_oContextManager.GetContextCount() >= cuContextCount );
}


void CProcessor::StepOver()
{
	uint64 const cuContextCount = m_oContextManager.GetContextCount( );
	StepIn();
	if ( m_oContextManager.GetContextCount() >= cuContextCount )
		StepOut();
}


void CProcessor::LoadModule( std::string const& sModuleName, offset uOffset )
{
	CModuleRef oModule = m_pModuleManager->GetModule( sModuleName );
	if ( -1 == uOffset )
		uOffset = oModule->GetMain();

	CContext* pContext = m_oContextManager.Current();
	pContext->IncrementPC( uOffset );
	Enter();
}


void CProcessor::Stop()
{
	m_bKeepRunning = false;
}


void CProcessor::Continue()
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
