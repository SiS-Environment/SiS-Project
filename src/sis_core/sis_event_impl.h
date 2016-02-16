// generic delegate impl
template <typename TSender, typename TReceiver, typename... TArguments>
Delegate<TSender, TReceiver, TArguments...>::Delegate(TReceiver& receiver, Callback callback) :
m_receiver(&receiver),
m_callback(callback)
{}

template <typename TSender, typename TReceiver, typename... TArguments>
Delegate<TSender, TReceiver, TArguments...>::Delegate(const Delegate& src)
{
	*this = src;
}

template <typename TSender, typename TReceiver, typename...TArguments>
const Delegate<TSender, TReceiver, TArguments...>& Delegate<TSender, TReceiver, TArguments...>::operator = (const Delegate& src)
{
	m_receiver = src.m_receiver;
	m_callback = src.m_callback;

	return *this;
}

template <typename TSender, typename TReceiver, typename... TArguments>
bool Delegate<TSender, TReceiver, TArguments...>::operator == (const Delegate& other) const
{
	return (m_receiver == other.m_receiver && m_callback == other.m_callback);
}

template <typename TSender, typename TReceiver, typename... TArguments>
bool Delegate<TSender, TReceiver, TArguments...>::operator != (const Delegate& other) const
{
	return !(operator == (other));
}

template <typename TSender, typename TReceiver, typename... TArguments>
void Delegate<TSender, TReceiver, TArguments...>::Fire(TSender* pSender, TArguments... args) const
{
	(m_receiver->*m_callback)(pSender, args...);
}

template <typename TSender, typename TReceiver, typename... TArguments>
void Delegate<TSender, TReceiver, TArguments...>::operator()(TSender* pSender, TArguments... args) const
{
	Fire(pSender, args);
}


// generic event impl
template <typename TSender, typename... TArguments>
Event<TSender, TArguments...>::Event()
{}

template <typename TSender, typename... TArguments>
Event<TSender, TArguments...>::Event(const Event& src)
{
	*this = src;
}

template <typename TSender, typename... TArguments>
const Event<TSender, TArguments...>& Event<TSender, TArguments...>::operator = (const Event& src)
{
	m_callers = src.m_callers;

	return *this;
}

template <typename TSender, typename... TArguments>
template <typename TReceiver>
void Event<TSender, TArguments...>::Add(const Delegate<TSender, TReceiver, TArguments...>& del)
{
	m_callers.push_back(DelegateCaller(reinterpret_cast<DummyReceiver&>(del.GetReceiver()),
		reinterpret_cast<Callback>(del.GetCallback())));
}

template <typename TSender, typename... TArguments>
template <typename TReceiver>
bool Event<TSender, TArguments...>::Remove(const Delegate<TSender, TReceiver, TArguments...>& del)
{
	DelegateCaller caller(reinterpret_cast<DummyReceiver&>(del.GetReceiver()),
		reinterpret_cast<Callback>(del.GetCallback()));

	std::vector<DelegateCaller>::iterator it = std::find(m_callers.begin(), m_callers.end(), caller);
	if (it == m_callers.end())
		return false;
	m_callers.erase(it);
	return true;
}

template <typename TSender, typename... TArguments>
template <typename TReceiver>
Event<TSender, TArguments...>& Event<TSender, TArguments...>::operator += (const Delegate<TSender, TReceiver, TArguments...>& del)
{
	Add<TReceiver>(del);
	return *this;
}

template <typename TSender, typename... TArguments>
template <typename TReceiver>
Event<TSender, TArguments...>& Event<TSender, TArguments...>::operator -= (const Delegate<TSender, TReceiver, TArguments...>& del)
{
	Remove<TReceiver>(del);
	return *this;
}

template <typename TSender, typename... TArguments>
template <typename TReceiver>
void Event<TSender, TArguments...>::Add(TReceiver& oReceiver, void (TReceiver::*CallbackProc)(TSender* pSender, TArguments... args))
{
	Add(Delegate<TSender, TReceiver, TArguments...>(oReceiver, CallbackProc));
}

template <typename TSender, typename... TArguments>
template <typename TReceiver>
bool Event<TSender, TArguments...>::Remove(TReceiver& oReceiver, void (TReceiver::*CallbackProc)(TSender* pSender, TArguments... args))
{
	return Remove(Delegate<TSender, TReceiver, TArguments...>(oReceiver, CallbackProc));
}

template <typename TSender, typename... TArguments>
void Event<TSender, TArguments...>::Fire(TSender* pSender, TArguments... args) const
{
	for (int i = 0; i < m_callers.size(); i++)
		m_callers.at(i).Fire(pSender, args...);
}

template <typename TSender, typename... TArguments>
void Event<TSender, TArguments...>::operator()(TSender* pSender, TArguments... args) const
{
	Fire(pSender, args...);
}
