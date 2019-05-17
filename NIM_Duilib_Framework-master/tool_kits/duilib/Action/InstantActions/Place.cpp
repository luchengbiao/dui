#include "StdAfx.h"
#include "Place.h"

namespace ui
{
	Place* Place::Create(const CPoint& left_top)
	{
		Place* ret = new (std::nothrow) Place();

		if (ret && ret->InitWithPoint(left_top))
		{
			return ret;
		}

		delete ret;

		return nullptr;
	}

	bool Place::InitWithPoint(const CPoint& left_top)
	{
		left_top_ = left_top;
		return true;
	}

	Place* Place::Clone() const
	{
		return Place::Create(left_top_);
	}

	Place* Place::Reverse() const
	{
		return this->Clone();
	}

	void Place::Update(float time)
	{
		InstantAction::Update(time);

		if (target_)
		{
			MoveLeftTopTo(target_, left_top_);
		}
	}
}

