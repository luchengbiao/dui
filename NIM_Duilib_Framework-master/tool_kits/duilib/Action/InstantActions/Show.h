#ifndef UI_ACTION_INSTANTACTIONS_SHOW_H_
#define UI_ACTION_INSTANTACTIONS_SHOW_H_
#pragma once

namespace ui
{
	class UILIB_API Show : public InstantAction
	{

	public:
		static Show*			Create();

		virtual void			Update(float time) override;
		virtual InstantAction*	Reverse() const override;
		virtual Show*			Clone() const override;

	protected:
		Show() = default;
	};
}

#endif