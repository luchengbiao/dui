#ifndef UI_ACTION_INTERVALACTIONS_INTERVALACTION_H_
#define UI_ACTION_INTERVALACTIONS_INTERVALACTION_H_
#pragma once

namespace ui
{
	class UILIB_API IntervalAction : public FiniteTimeAction
	{
	public:
		float			GetElapsed() { return elapsed_; }

		virtual bool	IsDone() const override;

		virtual void	Step(float dt) override;

		virtual void	StartWithTarget(Control *target) override;

	protected:
		bool			InitWithDuration(float d);

	protected:
		float			elapsed_{ 0 };
		bool			firstTick_{ true };
		bool			done_{ false };
	};
}

#endif