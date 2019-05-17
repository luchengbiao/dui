#include "StdAfx.h"
#include "Size.h"

namespace ui
{
	SizeBy* SizeBy::Create(float duration, const CSize& deltaSize)
	{
		SizeBy *ret = new (std::nothrow) SizeBy();

		if (ret && ret->InitWithDuration(duration, deltaSize))
		{
			return ret;
		}

		delete ret;

		return nullptr;
	}

	bool SizeBy::InitWithDuration(float duration, const CSize& deltaSize)
	{
		bool ret = false;

		if (IntervalAction::InitWithDuration(duration))
		{
			sizeDelta_ = deltaSize;
			ret = true;
		}

		return ret;
	}

	SizeBy* SizeBy::Clone() const
	{
		return SizeBy::Create(duration_, sizeDelta_);
	}

	SizeBy* SizeBy::Reverse() const
	{
		return SizeBy::Create(duration_, -sizeDelta_);
	}

	void SizeBy::StartWithTarget(Control* target)
	{
		IntervalAction::StartWithTarget(target);
		startSize_ = SizeOf(target);
	}

	void SizeBy::Update(float t)
	{
		if (target_)
		{
			CSize sz = startSize_ + sizeDelta_ * t;
			target_->SetFixedWidth(MAX(sz.cx, 0));
			target_->SetFixedHeight(MAX(sz.cy, 0));
		}
	}

	SizeTo* SizeTo::Create(float duration, const CSize& size)
	{
		SizeTo *ret = new (std::nothrow) SizeTo();

		if (ret && ret->InitWithDuration(duration, size))
		{
			return ret;
		}

		delete ret;

		return nullptr;
	}

	bool SizeTo::InitWithDuration(float duration, const CSize& size)
	{
		bool ret = false;

		if (IntervalAction::InitWithDuration(duration))
		{
			endSize_ = size;
			ret = true;
		}

		return ret;
	}

	SizeTo* SizeTo::Clone() const
	{
		return SizeTo::Create(duration_, endSize_);
	}

	SizeTo* SizeTo::Reverse() const
	{
		assert(false);
		return nullptr;
	}

	void SizeTo::StartWithTarget(Control* target)
	{
		SizeBy::StartWithTarget(target);
		sizeDelta_ = endSize_ - SizeOf(target_);
	}
}