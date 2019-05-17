#ifndef UI_ACTION_INSTANTACTIONS_PLACE_H_
#define UI_ACTION_INSTANTACTIONS_PLACE_H_
#pragma once

namespace ui
{
	class UILIB_API Place : public InstantAction
	{

	public:
		static Place*	Create(const CPoint& left_top);

		virtual void	Update(float time) override;
		virtual Place*	Reverse() const override;
		virtual Place*	Clone() const override;

	protected:
		Place() = default;

		bool			InitWithPoint(const CPoint& left_top);

	private:
		CPoint left_top_;
	};
}

#endif