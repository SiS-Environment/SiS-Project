#ifndef SIS_EXPRESSION_H
#define SIS_EXPRESSION_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Includes
//
#include "sis_core_global.h"
#include "sis_context.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Types
//
enum class EOpCode : byte
{
	Add,
	Sub,
	Mul,
	Div,

	Assign,

	LValue,
	RValue,

	Loop,

	Dummy
};

typedef EOpCode opcode;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Declarations
//
class IExpression;
class CAddExpression;
class CSubExpression;
class CMulExpression;
class CDivExpression;
class CAssignExpression;
class CLValueExpression;
class CRValueExpression;
class CDummyExpression;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Global Methods
//
inline IExpression* CreateExpression(byte* pBegin)
{
	opcode eOpCode = *(opcode*) (pBegin);
	IExpression* pExpression = nullptr;
	switch (eOpCode)
	{
	case opcode::Dummy:
		pExpression = new CDummyExpression();
		break;
	case opcode::LValue:
		pExpression = new CLValueExpression();
		break;
	case opcode::RValue:
		pExpression = new CRValueExpression();
		break;
	case opcode::Add:
		pExpression = new CAddExpression();
		break;
	case opcode::Sub:
		pExpression = new CSubExpression();
		break;
	case opcode::Mul:
		pExpression = new CMulExpression();
		break;
	case opcode::Div:
		pExpression = new CDivExpression();
		break;
	case opcode::Assign:
		pExpression = new CAssignExpression();
		break;
	case opcode::Loop:
		pExpression = new CLoopExpression();
		break;

	default:
		break;
	}

	return pExpression;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// abstract class IExpression
//
class SIS_CORE_EXPORT IExpression
{
public:// Constructor, Destructor
	inline IExpression() = default;

	virtual ~IExpression() = default;

public:// Static Methods

public:// Interface Methods
	virtual void	Init(byte* pBegin) = 0;
	virtual offset	Eval(CContext* pContext) = 0;
	virtual SiSType ResultType() = 0;

private:// Contents

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// class CDummyExpression
//
class  CDummyExpression : public IExpression
{
public:// Constructor, Destructor
	inline CDummyExpression() = default;

	~CDummyExpression() = default;

public:// Interface Methods
	virtual offset Eval(CContext* pContext) override
	{
		return sizeof(opcode);
	}
	virtual SiSType ResultType() override
	{
		return SiSType::Undefined;
	}
	virtual void Init(byte* pBegin) override
	{
		pBegin += sizeof(opcode);
	}

private:// Contents

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// class CConstValueExpression
//
class  CConstValueExpression : public IExpression
{
public:// Constructor, Destructor
	inline CConstValueExpression() = default;

	~CConstValueExpression() = default;

public:// Interface Methods
	inline offset Eval(CContext* pContext) override
	{
		IResult* m_pResult = (IResult*) (m_buffer);
		pContext->SetResult(m_pResult);

		return m_pResult->Size() + sizeof(opcode) + sizeof(SiSType);
	}
	inline SiSType ResultType() override
	{
		return m_eSisType;
	}
	inline void Init(byte* pBegin) override
	{
		m_eSisType = (SiSType) (*pBegin);
		pBegin += sizeof(SiSType);
		switch (m_eSisType)
		{
		case SiSType::Bool:
			new (m_buffer) CResult<bool>(pBegin);
			break;
		case SiSType::Char:
			new (m_buffer) CResult<char>(pBegin);
			break;

		case SiSType::Int8:
			new (m_buffer) CResult<int8>(pBegin);
			break;
		case SiSType::Int16:
			new (m_buffer) CResult<int16>(pBegin);
			break;
		case SiSType::Int32:
			new (m_buffer) CResult<int32>(pBegin);
			break;
		case SiSType::Int64:
			new (m_buffer) CResult<int64>(pBegin);
			break;

		case SiSType::UInt8:
			new (m_buffer) CResult<uint8>(pBegin);
			break;
		case SiSType::UInt16:
			new (m_buffer) CResult<uint16>(pBegin);
			break;
		case SiSType::UInt32:
			new (m_buffer) CResult<uint32>(pBegin);
			break;
		case SiSType::UInt64:
			new (m_buffer) CResult<uint64>(pBegin);
			break;

		case SiSType::Real32:
			new (m_buffer) CResult<real32>;
			break;
		case SiSType::Real64:
			new (m_buffer) CResult<real64>;
			break;

		default:
			new (m_buffer) CResult<void*>;
			break;
		}
	}

private:// Contents
	SiSType m_eSisType;
	byte m_buffer[16];
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// class CLValueExpression
//
class  CLValueExpression : public IExpression
{
public:// Constructor, Destructor
	inline CLValueExpression() = default;

	~CLValueExpression() = default;

public:// Interface Methods
	inline offset Eval(CContext* pContext) override
	{
		((IResult*) (m_buffer))->Init(&(pContext->Stack()[m_uDataOffset]));

		return sizeof(offset) + sizeof(opcode) + sizeof(SiSType);
	}
	inline SiSType ResultType() override
	{
		return m_eSisType;
	}
	inline void Init(byte* pBegin) override
	{
		m_eSisType = (SiSType) (*pBegin);
		pBegin += sizeof(SiSType);

		m_uDataOffset = *(offset*) (pBegin);

		switch (m_eSisType)
		{
		case SiSType::Bool:
			new (m_buffer) CResult<bool>;
			break;
		case SiSType::Char:
			new (m_buffer) CResult<char>;
			break;

		case SiSType::Int8:
			new (m_buffer) CResult<int8>;
			break;
		case SiSType::Int16:
			new (m_buffer) CResult<int16>;
			break;
		case SiSType::Int32:
			new (m_buffer) CResult<int32>;
			break;
		case SiSType::Int64:
			new (m_buffer) CResult<int64>;
			break;

		case SiSType::UInt8:
			new (m_buffer) CResult<uint8>;
			break;
		case SiSType::UInt16:
			new (m_buffer) CResult<uint16>;
			break;
		case SiSType::UInt32:
			new (m_buffer) CResult<uint32>;
			break;
		case SiSType::UInt64:
			new (m_buffer) CResult<uint64>;
			break;

		case SiSType::Real32:
			new (m_buffer) CResult<real32>;
			break;
		case SiSType::Real64:
			new (m_buffer) CResult<real64>;
			break;

		default:
			new (m_buffer) CResult<void*>;
			break;
		}
	}

private:// Contents
	SiSType m_eSisType;
	offset m_uDataOffset;
	byte m_buffer[16];
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// class CRValueExpression
//
class  CRValueExpression : public IExpression
{
public:// Constructor, Destructor
	inline CRValueExpression() = default;

	~CRValueExpression() = default;

public:// Interface Methods
	inline offset Eval(CContext* pContext) override
	{
		pContext->SetResult(((IResult*) (m_buffer))->Init(&(pContext->Stack()[m_uDataOffset])));

		return sizeof(offset);
	}
	inline SiSType ResultType() override
	{
		return m_eSisType;
	}
	inline void Init(byte* pBegin) override
	{
		m_eSisType = (SiSType) (*pBegin);
		pBegin += sizeof(SiSType);

		m_uDataOffset = *(offset*) (pBegin);

		switch (m_eSisType)
		{
		case SiSType::Bool:
			new (m_buffer) CResult<bool>;
			pBegin += 1;
			break;
		case SiSType::Char:
			new (m_buffer) CResult<char>;
			pBegin += 1;
			break;

		case SiSType::Int8:
			new (m_buffer) CResult<int8>;
			pBegin += 1;
			break;
		case SiSType::Int16:
			new (m_buffer) CResult<int16>;
			pBegin += 2;
			break;
		case SiSType::Int32:
			new (m_buffer) CResult<int32>;
			pBegin += 4;
			break;
		case SiSType::Int64:
			new (m_buffer) CResult<int64>;
			pBegin += 8;
			break;

		case SiSType::UInt8:
			new (m_buffer) CResult<uint8>;
			pBegin += 1;
			break;
		case SiSType::UInt16:
			new (m_buffer) CResult<uint16>;
			pBegin += 2;
			break;
		case SiSType::UInt32:
			new (m_buffer) CResult<uint32>;
			pBegin += 4;
			break;
		case SiSType::UInt64:
			new (m_buffer) CResult<uint64>;
			pBegin += 8;
			break;

		case SiSType::Real32:
			new (m_buffer) CResult<real32>;
			pBegin += 4;
			break;
		case SiSType::Real64:
			new (m_buffer) CResult<real64>;
			pBegin += 8;
			break;

		default:
			new (m_buffer) CResult<void*>;
			pBegin += 8;
			break;
		}
	}

private:// Contents
	SiSType m_eSisType;
	offset m_uDataOffset;
	byte m_buffer[16];
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// class CAddExpression
//
class  CAddExpression : public IExpression
{
public:// Constructor, Destructor
	inline CAddExpression() = default;

	~CAddExpression() = default;

public:// Interface Methods
	inline offset Eval(CContext* pContext) override
	{

		return 0;
	}
	inline SiSType ResultType() override
	{
		return SiSType::Void;
	}
	inline void Init(byte* pBegin) override
	{
		pBegin += sizeof(opcode);
		m_pLeftExpression = CreateExpression(pBegin);
		m_pLeftExpression->Init(pBegin);

		m_pRightExpression = CreateExpression(pBegin);
		m_pRightExpression->Init(pBegin);

		m_pLeftExpression->ResultType();
		m_pRightExpression->ResultType();
	}

protected:// Helper Methods
	template <typename T1, typename T2>
	IResult* Add(CResult<T1> arg1, CResult<T2> arg2)
	{
		arg1->
	}

private:// Contents
	IExpression* m_pLeftExpression;
	IExpression* m_pRightExpression;
	IResult* (*fAdd)();
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// class CSubExpression
//
class  CSubExpression : public IExpression
{
public:// Constructor, Destructor
	inline CSubExpression() = default;

	~CSubExpression() = default;

public:// Interface Methods
	inline offset Eval(CContext* pContext) override
	{
		return 0;
	}
	inline SiSType ResultType() override
	{
		return SiSType::Void;
	}
	inline void Init(byte* pBegin) override
	{
		pBegin += 3;
	}

private:// Contents

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// class CMulExpression
//
class  CMulExpression : public IExpression
{
public:// Constructor, Destructor
	inline CMulExpression() = default;

	~CMulExpression() = default;

public:// Interface Methods
	inline offset	Eval(CContext* pContext) override
	{
		return 0;
	}
	inline SiSType ResultType() override
	{
		return SiSType::Void;
	}
	inline void Init(byte* pBegin) override
	{
		pBegin += 3;
	}

private:// Contents

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// class CDivExpression
//
class  CDivExpression : public IExpression
{
public:// Constructor, Destructor
	inline CDivExpression() = default;

	~CDivExpression() = default;

public:// Interface Methods
	inline offset	Eval(CContext* pContext) override
	{
		return 0;
	}
	inline SiSType ResultType() override
	{
		return SiSType::Void;
	}
	inline void Init(byte* pBegin) override
	{
		pBegin += 3;
	}

private:// Contents

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// class CAssignExpression
//
class  CAssignExpression : public IExpression
{
public:// Constructor, Destructor
	inline CAssignExpression() = default;

	~CAssignExpression() = default;

public:// Interface Methods
	inline offset	Eval(CContext* pContext) override
	{
		return 0;
	}
	inline SiSType ResultType() override
	{
		return SiSType::Void;
	}
	inline void Init(byte* pBegin) override
	{
		pBegin += 1;
	}

private:// Contents

};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	class CLoopExpression
//
class  CLoopExpression : public IExpression
{
public:// Constructor, Destructor
	inline CLoopExpression() = default;

	~CLoopExpression() = default;

public:// Interface Methods
	inline offset Eval(CContext* pContext) override
	{
		IResult* m_pResult = (IResult*) (m_buffer);
		pContext->SetResult(m_pResult);

		return m_pResult->Size() + sizeof(opcode) + sizeof(SiSType);
	}
	inline SiSType ResultType() override
	{
		return m_eSisType;
	}
	inline void Init(byte* pBegin) override
	{
		m_eSisType = (SiSType) (*pBegin);
		pBegin += sizeof(SiSType);
		switch (m_eSisType)
		{
		case SiSType::Bool:
			new (m_buffer) CResult<bool>(pBegin);
			break;
		case SiSType::Char:
			new (m_buffer) CResult<char>(pBegin);
			break;

		case SiSType::Int8:
			new (m_buffer) CResult<int8>(pBegin);
			break;
		case SiSType::Int16:
			new (m_buffer) CResult<int16>(pBegin);
			break;
		case SiSType::Int32:
			new (m_buffer) CResult<int32>(pBegin);
			break;
		case SiSType::Int64:
			new (m_buffer) CResult<int64>(pBegin);
			break;

		case SiSType::UInt8:
			new (m_buffer) CResult<uint8>(pBegin);
			break;
		case SiSType::UInt16:
			new (m_buffer) CResult<uint16>(pBegin);
			break;
		case SiSType::UInt32:
			new (m_buffer) CResult<uint32>(pBegin);
			break;
		case SiSType::UInt64:
			new (m_buffer) CResult<uint64>(pBegin);
			break;

		case SiSType::Real32:
			new (m_buffer) CResult<real32>;
			break;
		case SiSType::Real64:
			new (m_buffer) CResult<real64>;
			break;

		default:
			new (m_buffer) CResult<void*>;
			break;
		}
	}

private:// Contents
	SiSType m_eSisType;
	byte m_buffer[16];
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // SIS_EXPRESSION_H
