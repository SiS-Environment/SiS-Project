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
	 std::vector<CObject*> mv_objPointers(vec_size);
	 for (int i = 0 ; i < vec_size-1 ; ++i)
	 	mv_objPointers[i] = i+1;
	 mv_objPointers[vec_size-1] = 0 ;
}


CMemoryManager::Type& m_New(Args... args)
{
	uint64 temp, 
	if(sizeof(Type) > buf_size - m_firstFreeMarker)
		m_GC(1);
	CObject* p_newObject = new (mp_bufFirst+m_firstFreeMarker) Type(args); ////////// operator+ for buffer
	temp = mv_objPointers[0];
	mv_objPointers[0] = mv_objPointers[mv_objPointers[0]] ;
	mv_objPointers[temp] = p_newObject;
	return *((Type*)(p_newObject));
	//return temp;
}

void CMemoryManager::m_GC(int level)
{
	if ( level == 3 )
		return;
	for ( int i = 1 ; i < vec_size ; ++i )   ///to do
	  if ( !mv_objPointers[i]->Counter() )
	  	if ( !mv_objPointers[vec_size-1] )
	  		mv_objPointers[vec_size-1] = i ;
	  	else
	  		mv_objPointers[mv_objPointers[0]] = i ;
	for ( int i = 1 ; i < vec_size ; ++i)
		//move objects in mp_buf second
}



CMemoryManager::~CMemoryManager()
{
	delete mp_bufFirst;
	delete mp_bufSecond;
	delete mp_bufThird;
	delete [] mv_objPointers;
	

}	
	
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace vm
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
