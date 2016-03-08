//////////////////////////////////////////////////////////////////////////////////
namespace sis {
//////////////////////////////////////////////////////////////////////////////////

template <typename T>
inline CReference<T>::CReference( T* pContent )
{
	if ( nullptr == pContent )
		throw -1; // TODO

	m_pContent = pContent;
}


template <typename T>
inline CReference<T>::CReference( CReference<T> const& oSource )
{
	operator=( oSource );
}


template <typename T>
inline CReference<T>& CReference<T>::operator=( CReference<T> const& oSource )
{
	if ( this != &oSource )
		m_pContent = oSource.m_pContent;

	return *this;
}


template <typename T>
inline CReference<T>::operator T&()
{
	return *m_pContent;
}


template <typename T>
inline CReference<T>::operator T const&() const
{
	return *m_pContent;
}


template <typename T>
inline T& CReference<T>::operator*()
{
	return *m_pContent;
}


template <typename T>
inline T const& CReference<T>::operator*() const
{
	return *m_pContent;
}


template <typename T>
inline T* CReference<T>::operator->()
{
	return m_pContent;
}


template <typename T>
inline const T* CReference<T>::operator->() const
{
	return m_pContent;
}


//////////////////////////////////////////////////////////////////////////////////
} // namespace sis
//////////////////////////////////////////////////////////////////////////////////