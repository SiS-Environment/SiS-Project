#ifndef SIS_LISTENER_H
#define SIS_LISTENER_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	includes
//
#include "sis_core_global.h"
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Interface IListener
//
class SIS_CORE_EXPORT IListener
{
public:
	// Constructor and destructor
	IListener() = default;
	virtual ~IListener() = default;

	// Copy constructor and assignment operator
	IListener( IListener const& ) = default;
	IListener& operator=( IListener const& ) = default;

public:
	// Interface methods
	virtual void Update( CNotifier const* ) = 0;
};
// IListener
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	class CNotifier
//
class SIS_CORE_EXPORT CNotifier
{
protected:
	//
	// Type definitions
	//
	typedef std::vector<IListener*> t_Listeners;

public:
	// Constructor and destructor
	CNotifier() = default;
	virtual ~CNotifier() = default;

	// Copy constructor and assignment operator
	CNotifier( CNotifier const& ) = default;
	CNotifier& operator=( CNotifier const& ) = default;

public:
	// Interface methods

	// Attach listener
	void Attach( IListener* pListener )
	{
		if ( nullptr != pListener )
			m_arrListeners.push_back( pListener );
	}
	// Detach listener
	void Detach( IListener* pListener )
	{
		if ( nullptr != pListener )
		{
			t_Listeners::iterator it = std::find( m_arrListeners.begin(), m_arrListeners.end(), pListener );
			if ( m_arrListeners.end() != it )
				m_arrListeners.erase( it );
		}
	}
	// Notify to listeners
	void Notify() const
	{
		for ( size_t uPos = 0; uPos < m_arrListeners.size(); ++uPos )
		{
			IListener* pListener = m_arrListeners[uPos];
			pListener->Update( this );
		}
	}

private:
	// Members
	t_Listeners m_arrListeners;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#endif // SIS_LISTENER_H
// end if file