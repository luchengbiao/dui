#include "StdAfx.h"
#include "InstantAction.h"

namespace ui
{
	void InstantAction::StartWithTarget(Control *target)
	{
		FiniteTimeAction::StartWithTarget(target);

		done_ = false;
	}

	void InstantAction::Step(float /*dt*/)
	{
		Update(1);
	}

	void InstantAction::Update(float /*time*/)
	{
		done_ = true;
	}
}

