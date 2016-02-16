#include "vm_contextmanager.h"


namespace sis
{


namespace vm
{


const size_t CContextManager::SIZE = 1048576;


CContextManager::CContextManager()
{
	m_ptr = new char[SIZE];
	m_pMarker = m_ptr;
}


CContext* CContextManager::Alloc(uint uStackSize)
{
	CContext* pContext = nullptr;
	uint uBlockSize = sizeof(CContext) + uStackSize;
	if (uBlockSize <= m_oBuffer.getSize() - m_uMarker)
	{
		char* p = &m_oBuffer[m_uMarker];
		CBuffer oStack(p, uStackSize);
		pContext = new (p) CContext(oStack);
		m_uMarker += uBlockSize;
	}
	else
	{
		throw(std::logic_error(""));   // TODO
	}

	return pContext;
}




void CContextManager::DeliteMem(CContext* pContext)
{
	t_ui size = m_stackSize.top();
	if ((void*) pContext == (void*) (m_pMarker - size))
	{
		m_stackSize.pop();
		m_pMarker -= size;
	}
	else
	{
		throw(std::logic_error(""));
	}
}


CContextManager::~CContextManager()
{
	delete m_ptr;
}



} // namespace vm


} // namespace sis

