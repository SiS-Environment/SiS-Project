#ifndef VM_EVENT_MANAGER_H
#define VM_EVENT_MANAGER_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//	Includes
//
#include "vm_processorevent.h"
// STL
#include <thread>
#include <queue>
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace vm {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


class SIS_RUNTIME_EXPORT CVMEventManager
{
public:
	// Constructors and destructor
	CVMEventManager()
		: m_queEvents(),
		  m_oBackThread()
	{
		EventLoop();
	}
	virtual ~CVMEventManager()
	{
		if ( m_oBackThread.joinable() )
			m_oBackThread.join();

		while ( !m_queEvents.empty() )
		{
			CProcEvent* pEvent = m_queEvents.front();
			delete pEvent;
			m_queEvents.pop();
		}
	}

	// Copy constructor and assignment operator
	CVMEventManager( CVMEventManager const& ) = delete;
	CVMEventManager& operator=( CVMEventManager const& ) = delete;

public:
	// Interface methods

	// Event loop
	inline void EventLoop()
	{
		m_oBackThread = std::thread( &CVMEventManager::_EventLoop, this );
	}

	// Add event to event manager
	void AddEvent( CProcEvent* pEvent )
	{
		if ( nullptr != pEvent ) // TODO : Sync
			m_queEvents.push( pEvent );
	}

protected:
	// Handle events
	virtual void HandleEvents() = 0;

private:
	// Event loop
	void _EventLoop()
	{
		while ( true )
		{
			HandleEvents();
		}
	}

protected:
	// Members
	std::queue<CProcEvent*> m_queEvents;

private:
	// Members
	std::thread m_oBackThread;
};


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace vm
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // VM_EVENT_MANAGER_H
// end of file
 