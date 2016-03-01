#ifndef SIS_OBJECT_H
#define SIS_OBJECT_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Includes
//
#include "sis_core_global.h"

// STL Includes
#include <atomic>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CRefCounter
// Implements Generic reference counter
//
class CRefCounter
{
public :
	// Default constructor (inits counter with 0)
	inline CRefCounter() = default;
	// Special constructor (inits counter with 1)
	struct One {};
	inline CRefCounter( One const& );

	// Atomically increments the value of this counter.
	inline void AddRef();

	// Atomically decrements the value of this QAtomicInt.
	// Returns true if the previous value is non - zero, false otherwise.
	inline bool DeRef();

	// Returns true if counter > 0, false otherwise (counter == 0)
	inline operator bool() const;

	// Allows comparison with one
	inline bool operator == (One const&) const;
	inline bool operator != (One const&) const;
	inline bool operator >= (One const&) const;
	inline bool operator <= (One const&) const;
	inline bool operator > (One const&) const;

private:
	std::atomic_uint	m_nCount;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CObject
// Base class for all vm managed objects 
//
class CObject 
{
public:
	// Default constructor
	inline CObject();
	// destructor
	inline ~CObject() = default;

public:
	// Interface
	inline CRefCounter& Counter();
	inline CRefCounter const& Counter() const;

private:
	// Contents
	CRefCounter	m_nCounter;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// CObjectRef
// Reference to Object (automatically increaes decreases ref counter)
//
class CObjectRef
{
public:
	// Default constructor
	inline CObjectRef();
	// destructor
	inline ~CObjectRef() = default;

public:
	// Interface
	//inline bool IsNull() const;
	//inline CObject* operator*();
	//inline CObject const* operator*() const;
	//inline CObject* operator->();
	//inline CObject const* operator->() const;

	inline operator CObject&();
	inline operator CObject const&() const;

	template<typename T> inline operator T&(); 
	template<typename T> inline operator T const&() const;

private:
	// Contents
	CObject*	m_pObject;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////// Implementing Inline Methods //////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// class CRefCounter
//

inline CRefCounter::CRefCounter( One const& )
{
	m_nCount = 1;
}

inline void CRefCounter::AddRef()
{
	m_nCount.fetch_add( 1 );
}

inline bool CRefCounter::DeRef()
{
	bool bOk = false;
	if (static_cast<unsigned int>(m_nCount) > 0)
		bOk = (m_nCount.fetch_sub( 1 ) == 1);
	return bOk;
}

inline CRefCounter::operator bool() const
{
	return bool( static_cast<unsigned int>(m_nCount) );
}

inline bool CRefCounter::operator == (One const&) const
{
	return (static_cast<unsigned int>(m_nCount) == 1);
}

inline bool CRefCounter::operator != (One const&) const
{
	return (static_cast<unsigned int>(m_nCount) != 1);
}

inline bool CRefCounter::operator >= (One const&) const
{
	return (static_cast<unsigned int>(m_nCount) >= 1);
}

inline bool CRefCounter::operator <= (One const&) const
{
	return (static_cast<unsigned int>(m_nCount) <= 1);
}

inline bool CRefCounter::operator > (One const&) const
{
	return (static_cast<unsigned int>(m_nCount) > 1);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // SIS_OBJECT_H