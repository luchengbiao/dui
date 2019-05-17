#include "StdAfx.h"
#include "Show.h"

namespace ui
{
	Show* Show::Create()
	{
		return new (std::nothrow) Show();
	}

	Show* Show::Clone() const
	{
		return Show::Create();
	}

	InstantAction* Show::Reverse() const
	{
		return Hide::Create();
	}

	void Show::Update(float time)
	{
		InstantAction::Update(time);

		if (target_)
		{
			target_->SetVisible(true);
		}
	}
}

