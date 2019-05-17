#include "StdAfx.h"
#include "IntervalAction.h"

namespace ui
{
	bool IntervalAction::InitWithDuration(float d)
	{
		duration_ = abs(d) <= MATH_EPSILON ? MATH_EPSILON : d;
		elapsed_ = 0;
		firstTick_ = true;
		done_ = false;

		return true;
	}

	bool IntervalAction::IsDone() const
	{
		return done_;
	}

	void IntervalAction::Step(float dt)
	{
		if (firstTick_)
		{
			firstTick_ = false;
			elapsed_ = MATH_EPSILON;
		}
		else
		{
			elapsed_ += dt;
		}

		// needed for rewind. elapsed could be negative
		float updateDt = CLAMP(elapsed_ / duration_, 0.0f, 1.0f);

		this->Update(updateDt);

		done_ = elapsed_ >= duration_;
	}

	void IntervalAction::StartWithTarget(Control *target)
	{
		FiniteTimeAction::StartWithTarget(target);
		elapsed_ = 0.0f;
		firstTick_ = true;
		done_ = false;
	}
}