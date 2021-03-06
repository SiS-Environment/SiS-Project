#ifndef SIS_EXPRESSION_MANAGER_H
#define SIS_EXPRESSION_MANAGER_H

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	Includes
//
#include "sis_expressionbuilder.h"
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace sis {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
namespace vm {
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//	class CExpressionManager
//
class CExpressionManager : public IExpressionBuilder
{
public:// Constructor, Destructor
	inline CExpressionManager() = default;

	~CExpressionManager() = default;

public:// Static Methods

public:// Interface Methods
	virtual IExpresion* GetExpression(byte*);

private:// Contents
	CExpressionBuilder m_pExpressionBuilder;
};
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// class CExpressionBuilder
//

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////// Implementing Inline Methods //////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// class CExpressionManager
//

// Constructor, Destructor

// Interface Methods

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace vm
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
} // namespace sis
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif // SIS_EXPRESSION_MANAGER_H
