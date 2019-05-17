#include "StdAfx.h"
#include "RemoveSelf.h"

namespace ui
{
	RemoveSelf* RemoveSelf::Create()
	{
		return new (std::nothrow) RemoveSelf();
	}

	RemoveSelf* RemoveSelf::Clone() const
	{
		return RemoveSelf::Create();
	}

	RemoveSelf* RemoveSelf::Reverse() const
	{
		return this->Clone();
	}

	void RemoveSelf::Update(float time)
	{
		InstantAction::Update(time);

		if (target_)
		{
			auto box = target_->GetParent();
			if (box)
			{
				box->Remove(target_);
			}
			else
			{
				delete target_;
			}
		}
	}
}

