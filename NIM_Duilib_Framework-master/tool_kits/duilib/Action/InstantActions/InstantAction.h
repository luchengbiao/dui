#ifndef UI_ACTION_INSTANTACTIONS_INSTANTACTION_H_
#define UI_ACTION_INSTANTACTIONS_INSTANTACTION_H_
#pragma once

namespace ui
{
	class UILIB_API InstantAction : public FiniteTimeAction
	{
	public:
		virtual bool	IsDone() const override { return done_; }

		virtual void	Step(float dt) override;

		virtual void	StartWithTarget(Control *target) override;

		virtual void	Update(float time) override;

	protected:
		bool			InitWithDuration(float d);

	protected:
		bool			done_{ false };
	};
}

#endif