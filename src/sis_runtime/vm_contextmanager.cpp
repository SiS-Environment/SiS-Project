#include "vm_contextmanager.h"


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace vm {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


const uint64 CContextManager::s_cuSize = 1048576;


CContextManager::CContextManager()
{
	m_stackBuffer.push( CBuffer( s_cuSize ) );
	m_stackMarker.push( 0 );
	m_pCurrContext = nullptr;
	m_uContextCount = 0;
}


CContext* CContextManager::Alloc( uint64 uStackSize )
{
	if ( uStackSize > s_cuSize )
		return nullptr; // TODO

	CContext* pContext = nullptr;
	CBuffer& oBuffer = m_stackBuffer.top();
	uint64& uMarker = m_stackMarker.top();
	uint64 uBlockSize = sizeof( CContext ) + uStackSize + 1;
	if ( uBlockSize <= oBuffer.GetSize() - uMarker)
	{
		byte* p = &oBuffer[uMarker];
		CStack oStack( p, uStackSize );
		pContext = new (p)CContext( oStack );
		uMarker += uBlockSize;
		oBuffer[uMarker-1] = uBlockSize;
	}
	else
	{
		m_stackBuffer.push( CBuffer( s_cuSize ) );
		m_stackMarker.push( 0 );
		Alloc( uStackSize );
	}
	m_pCurrContext = pContext;
	++m_uContextCount;
	return pContext;
}

void CContextManager::Free( CContext* pContext )
{
	CBuffer& oBuffer = m_stackBuffer.top();  
	uint64& uMarker = m_stackMarker.top();
	uint64 uBlockSize = oBuffer[uMarker-1];
	byte* pLastBlock = &oBuffer[uMarker - uBlockSize];
	if ( (void*)pContext == (void*)pLastBlock )
		uMarker -= uBlockSize;
	else
		throw std::logic_error( "Invalid Context pointer" );
}

CContext* CContextManager::GetCurrent() const
{
	return m_pCurrContext;
}

uint64 CContextManager::GetContextCount() const
{
	return m_uContextCount;
}

CContextManager::~CContextManager()
{
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace vm
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
