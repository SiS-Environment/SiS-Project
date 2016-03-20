////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Includes
//
#include "vm_processorevent.h"
#include "vm_processor.h"
#include "vm_controller.h"
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace vm {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void CBreakEvent::Eval( CProcessor* pProcessor ) const
{
	pProcessor->Stop();
}


void CLoadModulEvent::Eval( CProcessor* pProcessor ) const
{
	pProcessor->LoadModule( m_csModuleName, m_cuOffset );
}


void CContinueEvent::Eval( CProcessor* pProcessor ) const
{
	pProcessor->Continue();
}


void CStepInEvent::Eval( CProcessor* pProcessor ) const
{
	pProcessor->StepIn();
}


void CStepOutEvent::Eval( CProcessor* pProcessor ) const
{
	pProcessor->StepOut();
}


void CStepOverEvent::Eval( CProcessor* pProcessor ) const
{
	pProcessor->StepOver();
}


void CNewProcessorEvent::Eval( CProcessor* pProcessor ) const
{
	CController* pController = pProcessor->GetContoller();
	if ( nullptr != pController )
		pController->RunNewProcessor( m_csModule );
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace vm
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////