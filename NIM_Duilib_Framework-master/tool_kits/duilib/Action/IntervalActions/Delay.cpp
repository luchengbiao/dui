#include "StdAfx.h"
#include "Delay.h"

namespace ui
{
	Delay* Delay::Create(float duration)
	{
		Delay* ret = new (std::nothrow) Delay();

		if (ret && ret->InitWithDuration(duration))
		{
			return ret;
		}

		delete ret;

		return nullptr;
	}

	Delay* Delay::Clone() const
	{
		return Delay::Create(duration_);
	}

	Delay* Delay::Reverse() const
	{
		return this->Clone();
	}

	void Delay::StartWithTarget(Control* target)
	{
		IntervalAction::StartWithTarget(target);
	}
}