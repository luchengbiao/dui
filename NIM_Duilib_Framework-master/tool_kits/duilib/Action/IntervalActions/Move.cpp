#include "StdAfx.h"
#include "Move.h"

namespace ui
{
	MoveBy* MoveBy::Create(float duration, const CPoint& deltaPosition)
	{
		MoveBy* ret = new (std::nothrow) MoveBy();

		if (ret && ret->InitWithDuration(duration, deltaPosition))
		{
			return ret;
		}

		delete ret;

		return nullptr;
	}

	bool MoveBy::InitWithDuration(float duration, const CPoint& deltaPosition)
	{
		bool ret = false;

		if (IntervalAction::InitWithDuration(duration))
		{
			positionDelta_ = deltaPosition;
			ret = true;
		}

		return ret;
	}

	MoveBy* MoveBy::Clone() const
	{
		// no copy constructor
		return MoveBy::Create(duration_, positionDelta_);
	}

	MoveBy* MoveBy::Reverse() const
	{
		return MoveBy::Create(duration_, -positionDelta_);
	}

	void MoveBy::StartWithTarget(Control* target)
	{
		IntervalAction::StartWithTarget(target);

		startPosition_ = LeftTop(target);
	}

	void MoveBy::Update(float t)
	{
		if (target_)
		{
			MoveLeftTopTo(target_, startPosition_ + positionDelta_ * t);
		}
	}

	MoveTo* MoveTo::Create(float duration, const CPoint& position)
	{
		MoveTo *ret = new (std::nothrow) MoveTo();

		if (ret && ret->InitWithDuration(duration, position))
		{
			return ret;
		}

		delete ret;

		return nullptr;
	}

	bool MoveTo::InitWithDuration(float duration, const CPoint& position)
	{
		bool ret = false;

		if (IntervalAction::InitWithDuration(duration))
		{
			endPosition_ = position;
			ret = true;
		}

		return ret;
	}

	MoveTo* MoveTo::Clone() const
	{
		return MoveTo::Create(duration_, endPosition_);
	}

	MoveTo* MoveTo::Reverse() const
	{
		assert(false);
		return nullptr;
	}

	void MoveTo::StartWithTarget(Control *target)
	{
		MoveBy::StartWithTarget(target);
		positionDelta_ = endPosition_ - LeftTop(target);
	}
}