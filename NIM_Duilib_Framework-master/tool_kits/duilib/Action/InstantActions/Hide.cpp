#include "StdAfx.h"
#include "Hide.h"

namespace ui
{
	Hide* Hide::Create()
	{
		return new (std::nothrow) Hide();
	}

	Hide* Hide::Clone() const
	{
		return Hide::Create();
	}

	InstantAction* Hide::Reverse() const
	{
		return Show::Create();
	}

	void Hide::Update(float time)
	{
		InstantAction::Update(time);

		if (target_)
		{
			target_->SetVisible(false);
		}
	}
}

