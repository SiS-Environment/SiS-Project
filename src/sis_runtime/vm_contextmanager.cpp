#include "vm_contextmanager.h"


namespace sis {


namespace vm {


const size_t CContextManager::s_cuSize = 1048576;


CContextManager::CContextManager()
	:m_oBuffer(s_cuSize)
{
	m_uMarker=0;
}


CContext* CContextManager::Alloc( uint uStackSize )
{
	CContext* pContext = nullptr;
	uint uBlockSize = sizeof( CContext ) + uStackSize + 1;
	if ( uBlockSize <= m_oBuffer.getSize() - m_uMarker)
	{
		char* p = &m_oBuffer[m_uMarker];
		CContext::CStack oStack( p, uStackSize );
		pContext = new (p)CContext( oStack );
		m_uMarker += uBlockSize;
		m_oBuffer[m_uMarker-1] = uBlockSize;
	}
	else
	{
		throw(std::logic_error( "" ));   // TODO
	}
	
	return pContext;
}




void CContextManager::Free( CContext* pContext )
{
	uint uBlockSize = m_oBuffer[m_uMarker-1];
	char* pLastBlock = &m_oBuffer[m_uMarker - uBlockSize];
	if ( (void*)pContext == (void*)pLastBlock )
	{
		m_uMarker -= uBlockSize; 
	}
	else
	{
		throw(std::logic_error( "" ));    //TODO
	}
}


CContextManager::~CContextManager()
{
}



} // namespace vm


} // namespace sis