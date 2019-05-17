#ifndef UI_ACTION_INTERVALACTIONS_SIZE_H_
#define UI_ACTION_INTERVALACTIONS_SIZE_H_
#pragma once

namespace ui
{
	class UILIB_API SizeBy : public IntervalAction
	{
	public:
		static SizeBy*	Create(float duration, const CSize& deltaSize);

		virtual SizeBy* Clone() const override;
		virtual SizeBy* Reverse() const  override;
		virtual void	StartWithTarget(Control* target) override;
		virtual void	Update(float time) override;

	protected:
		SizeBy() = default;

		/** initializes the action */
		bool			InitWithDuration(float duration, const CSize& deltaSize);

	protected:
		CSize			sizeDelta_;
		CSize			startSize_;
	};

	class SizeTo : public SizeBy
	{
	public:
		static SizeTo*	Create(float duration, const CSize& size);

		virtual SizeTo* Clone() const override;
		virtual SizeTo* Reverse() const  override;
		virtual void	StartWithTarget(Control* target) override;

	protected:
		SizeTo() = default;

		/**
		* initializes the action
		* @param duration in seconds
		*/
		bool			InitWithDuration(float duration, const CSize& size);

	protected:
		CSize			endSize_;
	};
}

#endif