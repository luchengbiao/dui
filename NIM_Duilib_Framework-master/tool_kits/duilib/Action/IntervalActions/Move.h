#ifndef UI_ACTION_INTERVALACTIONS_MOVE_H_
#define UI_ACTION_INTERVALACTIONS_MOVE_H_
#pragma once

namespace ui
{
	class UILIB_API MoveBy : public IntervalAction
	{
	public:
		static MoveBy*	Create(float duration, const CPoint& deltaPosition);

		virtual MoveBy* Clone() const override;
		virtual MoveBy* Reverse() const  override;
		virtual void	StartWithTarget(Control* target) override;
		virtual void	Update(float time) override;

	protected:
		MoveBy() = default;

		/** initializes the action */
		bool			InitWithDuration(float duration, const CPoint& deltaPosition);

	protected:
		CPoint			positionDelta_;
		CPoint			startPosition_;
	};

	class UILIB_API MoveTo : public MoveBy
	{
	public:
		static MoveTo*	Create(float duration, const CPoint& position);

		virtual MoveTo* Clone() const override;
		virtual MoveTo* Reverse() const  override;
		virtual void	StartWithTarget(Control *target) override;

	protected:
		MoveTo() = default;

		/**
		* initializes the action
		* @param duration in seconds
		*/
		bool			InitWithDuration(float duration, const CPoint& position);

	protected:
		CPoint			endPosition_;
	};
}

#endif