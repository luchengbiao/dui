#ifndef UI_ACTION_INTERVALACTIONS_DELAY_H_
#define UI_ACTION_INTERVALACTIONS_DELAY_H_
#pragma once

namespace ui
{
	class UILIB_API Delay : public IntervalAction
	{
	public:
		static Delay*	Create(float duration);

		virtual Delay*	Clone() const override;
		virtual Delay*	Reverse() const  override;
		virtual void	StartWithTarget(Control* target) override;

	protected:
		Delay() = default;
	};
}

#endif