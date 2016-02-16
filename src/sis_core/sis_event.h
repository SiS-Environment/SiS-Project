#ifndef MYM_EVENT_H
#define MYM_EVENT_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Includes
//

// STL Includes
#include <vector>
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	template class Delegate
//
template <typename TSender, typename TReceiver, typename... TArguments>
class Delegate
{
public:// Native Types
	typedef void (TReceiver::*Callback)(TSender* pSender, TArguments... args);

public:// Constructors, Destructor
	Delegate(TReceiver& receiver, Callback callback);
	Delegate(const Delegate& src);

public:// Interface Methods
	const Delegate& operator = (const Delegate& src);

	bool operator == (const Delegate& other) const;
	bool operator != (const Delegate& other) const;

	void Fire(TSender* pSender, TArguments... args) const;
	void operator()(TSender* pSender, TArguments... args) const;

	TReceiver& GetReceiver() const
	{
		return *m_receiver;
	}
	Callback GetCallback() const
	{
		return m_callback;
	}

private:// Contents
	TReceiver*	m_receiver;
	Callback	m_callback;
};


template <typename TSender, typename... TArguments>
class Event
{
public:
	Event();
	Event(const Event& src);
	const Event& operator = (const Event& src);

	template <typename TReceiver>
	void Add(const Delegate<TSender, TReceiver, TArguments...>& del);
	template <typename TReceiver>
	bool Remove(const Delegate<TSender, TReceiver, TArguments...>& del);

	template <typename TReceiver>
	Event& operator += (const Delegate<TSender, TReceiver, TArguments...>& del);
	template <typename TReceiver>
	Event& operator -= (const Delegate<TSender, TReceiver, TArguments...>& del);

	template <typename TReceiver>
	void Add(TReceiver& oReceiver, void (TReceiver::*CallbackProc)(TSender* pSender, TArguments... args));
	template <typename TReceiver>
	bool Remove(TReceiver& oReceiver, void (TReceiver::*CallbackProc)(TSender* pSender, TArguments... args));

	void Fire(TSender* pSender, TArguments... args) const;
	void operator()(TSender* pSender, TArguments... args) const;

private:
	class DummyReceiver
	{};

	typedef Delegate<TSender, DummyReceiver, TArguments...> DelegateCaller;
	typedef void (DummyReceiver::*Callback)(TSender* pSender, TArguments... args);

	std::vector<DelegateCaller> m_callers;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#define MYM_DELEGATE(_Delegate_Name_)											\
	&_Delegate_Name_##Delegate

#define MYM_DECLARE_DELEGATE_2(_Delegate_Name_)									\
	/* Template callback procedure */											\
	template <typename TSender, typename TArg1, typename TArg2>					\
	void _Delegate_Name_##Delegate(TSender* pSender, TArg1 arg1, TArg2 arg2)	\
		{ _Delegate_Name_(pSender, arg1, arg2); }

#define MYM_DECLARE_AUTO_DELEGATE_2(_Delegate_Name_)							\
	MYM_DECLARE_DELEGATE_2(_Delegate_Name_)										\
	/* default implementation */												\
	template <typename TSender, typename TArg1, typename TArg2>					\
	void _Delegate_Name_(TSender* pSender, TArg1 arg1, TArg2 arg2) { }



#define MYM_DECLARE_DELEGATE_1(_Delegate_Name_)									\
	/* Template callback procedure */											\
	template <typename TSender, typename TArg1>									\
	void _Delegate_Name_##Delegate(TSender* pSender, TArg1 arg1)				\
		{ _Delegate_Name_(pSender, arg1); }

#define MYM_DECLARE_AUTO_DELEGATE_1(_Delegate_Name_)							\
	MYM_DECLARE_DELEGATE_1(_Delegate_Name_)										\
	/* default implementation */												\
	template <typename TSender, typename TArg1>									\
	void _Delegate_Name_(TSender* pSender, TArg1 arg1) { }


#define MYM_DECLARE_DELEGATE(_Delegate_Name_)									\
	MYM_DECLARE_DELEGATE_1(_Delegate_Name_)										\
	MYM_DECLARE_DELEGATE_2(_Delegate_Name_)

#define MYM_DECLARE_AUTO_DELEGATE(_Delegate_Name_)								\
	MYM_DECLARE_AUTO_DELEGATE_1(_Delegate_Name_)								\
	MYM_DECLARE_AUTO_DELEGATE_2(_Delegate_Name_)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Implementation of inline methods
#include "sis_event_impl.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // MYM_EVENT_H

