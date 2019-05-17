#ifndef UI_ACTION_INSTANTACTIONS_CALLFUNC_H_
#define UI_ACTION_INSTANTACTIONS_CALLFUNC_H_
#pragma once

namespace ui
{
	class UILIB_API CallFunc : public InstantAction
	{
	public:
		typedef std::function<void()> Closure;

	public:
		static CallFunc*	Create(const Closure& closure);

		/** Executes the callback.
		*/
		virtual void		Execute();

		virtual void		Update(float time) override;
		virtual CallFunc*	Reverse() const override;
		virtual CallFunc*	Clone() const override;

	protected:
		CallFunc() = default;

		/** initializes the action with the std::function<void()>
		*/
		bool				InitWithFunction(const Closure& closure);

	protected:
		/** function that will be called */
		Closure				closure_;
	};
}

#endif