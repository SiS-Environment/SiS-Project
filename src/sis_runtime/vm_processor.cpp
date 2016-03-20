////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Includes
//
#include "vm_processor.h"
#include "vm_controller.h"
#include "vm_modulemanager.h"
#include "vm_contextmanager.h"
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
	: CProceEventManager(),
	  m_pController( pController ),
	  m_pModuleManager( pModuleManager ),
	  m_oContextManager()
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
	if ( m_stackModule.empty() )
		throw - 1; // TODO

	CModuleRef oModule = m_stackModule.top();
	offset uOffset = 0;
	CContext* pContext = nullptr;
	IExpression* pExpression = nullptr;
	do
	{
		HandleEvents();

		pContext = m_oContextManager.Current();
		pContext->IncrementPC( uOffset );
		pExpression = oModule.GetExpression( pContext->GetPC() );
		uOffset = pExression->Eval( pContext );
	}
	while ( true );
}


void CProcessor::EnterDebug()
{
	if ( m_stackModule.empty() )
		throw - 1; // TODO

	CModuleRef oModule = m_stackModule.top();
	offset uOffset = 0;
	CContext* pContext = nullptr;
	IExpression* pExpression = nullptr;
	do
	{
		CheckBreakPoint();
		HandleEvents();

		pContext = m_oContextManager.Current();
		pContext->IncrementPC( uOffset );
		pExpression = oModule.GetExpression( pContext->GetPC() );
		uOffset = pExression->Eval( pContext );
	}
	while ( true );
}


void CProcessor::StepIn()
{
	if ( m_stackModule.empty() )
		throw - 1; // TODO

	CModuleRef oModule = m_stackModule.top();
	CContext* pContext = m_oContextManager.Current();
	IExpression* pExpression = oModule.GetExpression( pContext->GetPC() );
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
	m_stackModule.push( oModule );
	if ( -1 == uOffset )
		uOffset = oModule->GetMain();

	CContext* pContext = m_oContextManager.Current();
	pContext->IncrementPC( uOffset );
	Enter();

	m_stackModule.pop();
}


void CProcessor::Stop()
{
	std::this_thread::sleep_for( std::chrono::seconds( 1 ) );
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
