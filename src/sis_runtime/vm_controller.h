#ifndef VM_CONTROLLER_H
#define VM_CONTROLLER_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Includes
//
#include "vm_runtime_global.h"
#include <sis_module.h>
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
	// Constructors, destructor
	CController( CModuleManager* pModuleManager );
	~CController();

	// Copy constructor and assignment operator
	CController( CController const& ) = delete;
	CController& operator=( CController const& ) = delete;

public:
	// Interface methods
	void Start();
	void RunNewProcessor( CModuleRef oModule );

	void KillAll();
	
private:
	// Create new processor
	CProcessor* CreateProcessor();
	// Kill processor
	void KillProcessor( CProcessor* );

private:
	// Members
	CModuleManager* m_pModuleManager;
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
