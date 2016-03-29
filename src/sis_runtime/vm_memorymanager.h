#ifndef VM_MEMORY_MANAGER_H
#define VM_MEMORY_MANAGER_H

#define buf_size 64*1024
////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	includes
//
#include "vm_runtime_global.h"
// STL
#include <iostream>
#include <vector>

//
////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace vm {
////////////////////////////////////////////////////////////////////////////////////////////////////////////


class CMemoryManager
{
public: 
	/////////////// Constructor, Destructor/////////////////
	CMemoryManager();
	~CMemoryManager();


public:
	////////// Interface methods///
	template <typename Type,typename... Args>
	Type& m_New(Args... args);

private:
	////////Private methods///
	void m_GC(int);


private: 
	//////////////////////////// members///////////////////
	CBuffer* mp_bufferFirst;
	CBuffer* mp_bufferSecond;
	CBuffer* mp_bufferThird;
	uint64 m_firstFreeMarker; 
	uint64 m_secondFreeMarker;
	uint64 m_thirdFreeMarker;
	std::vector<CObject*> mv_objPointers;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace vm
////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // VM_MEMORY_MANAGER_H
