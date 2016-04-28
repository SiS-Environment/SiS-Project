#include "vm_memorymanager.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace vm {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

const size_t CMemoryManager::s_cuBuffSize = 65536; //64 Kb
const size_t CMemoryManager::s_cuVecSize = 100000;


CMemoryManager::CMemoryManager()	
{
	 mp_bufFirst = new CBuffer(s_cuBuffSize);
	 mp_bufSecond = new CBuffer(s_cuBuffSize);
	 mp_bufThird = new CBuffer(s_cuBuffSize);
	 m_firstFreeMarker = m_secondFreeMarker = m_thirdFreeMarker = 0;
	 std::vector<std::pair<uint8, CObject*> > mv_objPointers(s_cuVecSize);
	 for (int i = 0 ; i < s_cuVecSize-1 ; ++i)
	 	mv_objPointers[i].second = i+1;
	 mv_objPointers[s_cuVecSize-1] = 0 ;
}


CMemoryManager::uint64 m_New(Args... args)
{
	uint64 temp, 
	if(sizeof(Type) > s_cuBuffSize - m_firstFreeMarker)
		m_GC(1);
	CObject* p_newObject = new (mp_bufFirst+m_firstFreeMarker) Type(args); ////////// operator+ for buffer
	temp = mv_objPointers[0].second;
	mv_objPointers[0].second = mv_objPointers[mv_objPointers[0].second].second ;
	mv_objPointers[temp].second = p_newObject;
	mv_objPointers[temp].first = 1 ;
	//return *((Type*)(p_newObject));
	return temp;
}

CMemoryManager::CObject* m_Object(uint64 index)
{
	return mv_objPointers[index].second;
}

void CMemoryManager::m_GC(int level)
{
	if ( level == 3 )
		return;
	for ( int i = 1 ; i < s_cuVecSize ; ++i )   ///to do
	  if ( !mv_objPointers[i].second->Counter() )
	  	if ( !mv_objPointers[s_cuVecSize-1].second )
	  		mv_objPointers[s_cuVecSize-1].second = i ;
	  	else
	  		mv_objPointers[mv_objPointers[0].second].second = i ;
	  else
		//move objects in mp_buf second
		mv_objPointers[i].first++;
}



CMemoryManager::~CMemoryManager()
{
	delete mp_bufFirst;
	delete mp_bufSecond;
	delete mp_bufThird;
	

}	
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace vm
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
