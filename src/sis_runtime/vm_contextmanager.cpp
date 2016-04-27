#include "vm_contextmanager.h"


namespace sis {


namespace vm {


const size_t CContextManager::s_cuSize = 1048576;


CContextManager::CContextManager()
{
	m_oBuffer.push(s_cuSize);
	m_uMarker.push(0);
	mp_currContext = nullptr;
	m_contextCount = 0;
}


CContext* CContextManager::Alloc( uint uStackSize )
{
	CContext* pContext = nullptr;
	CBuffer& oBuffer = m_oBuffer.top();
	uint64& uMarker = m_uMarker.top();
	uint64 uBlockSize = sizeof( CContext ) + uStackSize + 1;
	if ( uBlockSize <= oBuffer.getSize() - uMarker)
	{
		char* p = &oBuffer[uMarker];
		CContext::CStack oStack( p, uStackSize );
		pContext = new (p)CContext( oStack );
		uMarker += uBlockSize;
		oBuffer[uMarker-1] = uBlockSize;
	}
	else
	{
		m_oBuffer.push(s_cuSize);
		m_uMarker.push(0);
		Alloc(uStackSize);
	}
	mp_currContext = pContext;
	m_contextCount++;
	return pContext;
}

void CContextManager::Free( CContext* pContext )
{
	CBuffer& oBuffer = m_oBuffer.top();  
	uint64& uMarker = m_uMarker.top();
	uint64 uBlockSize = oBuffer[uMarker-1];
	char* pLastBlock = &oBuffer[uMarker - uBlockSize];
	if ( (void*)pContext == (void*)pLastBlock )
	{
		m_uMarker -= uBlockSize; 
	}
	else
	{
		throw(std::logic_error( "Invalid Context pointer" ));    
  	}
}

CContext* GetCurrent() const
{
	return mp_currContext;
}

uint64 GetContextCount() const
{
	return m_contextCount;
}

CContextManager::~CContextManager()
{
}



} // namespace vm


} // namespace sis
