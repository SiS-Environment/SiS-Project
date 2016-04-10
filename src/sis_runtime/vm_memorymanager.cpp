#include "vm_memorymanager.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace vm {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CMemoryManager::CMemoryManager()	
{
	 mp_bufFirst = new CBuffer(buf_size);
	 mp_bufSecond = new CBuffer(buf_size);
	 mp_bufThird = new CBuffer(buf_size);
	 m_firstFreeMarker = m_secondFreeMarker = m_thirdFreeMarker = 0;
	 std::vector<std::pair<uint8, CObject*> > mv_objPointers(vec_size);
	 for (int i = 0 ; i < vec_size-1 ; ++i)
	 	mv_objPointers[i].second = i+1;
	 mv_objPointers[vec_size-1] = 0 ;
}


CMemoryManager::uint64 m_New(Args... args)
{
	uint64 temp, 
	if(sizeof(Type) > buf_size - m_firstFreeMarker)
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
	for ( int i = 1 ; i < vec_size ; ++i )   ///to do
	  if ( !mv_objPointers[i].second->Counter() )
	  	if ( !mv_objPointers[vec_size-1].second )
	  		mv_objPointers[vec_size-1].second = i ;
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
