#ifndef UI_ACTION_INSTANTACTIONS_REMOVESELF_H_
#define UI_ACTION_INSTANTACTIONS_REMOVESELF_H_
#pragma once

namespace ui
{
	class UILIB_API RemoveSelf : public InstantAction
	{

	public:
		static RemoveSelf*	Create();

		virtual void		Update(float time) override;
		virtual RemoveSelf*	Reverse() const override;
		virtual RemoveSelf*	Clone() const override;

	protected:
		RemoveSelf() = default;
	};
}

#endif