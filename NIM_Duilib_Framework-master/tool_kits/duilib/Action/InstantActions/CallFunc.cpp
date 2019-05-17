#include "StdAfx.h"
#include "CallFunc.h"

namespace ui
{
	CallFunc* CallFunc::Create(const Closure& closure)
	{
		CallFunc* ret = new (std::nothrow) CallFunc();

		if (ret && ret->InitWithFunction(closure))
		{
			return ret;
		}

		delete ret;

		return nullptr;
	}

	bool CallFunc::InitWithFunction(const Closure& closure)
	{
		closure_ = closure;

		return true;
	}

	CallFunc* CallFunc::Clone() const
	{
		return CallFunc::Create(closure_);
	}

	CallFunc* CallFunc::Reverse() const
	{
		return this->Clone();
	}

	void CallFunc::Update(float time)
	{
		InstantAction::Update(time);

		this->Execute();
	}

	void CallFunc::Execute()
	{
		if (closure_)
		{
			closure_();
		}
	}
}