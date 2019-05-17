#ifndef UI_ACTION_INSTANTACTIONS_HIDE_H_
#define UI_ACTION_INSTANTACTIONS_HIDE_H_
#pragma once

namespace ui
{
	class UILIB_API Hide : public InstantAction
	{

	public:
		static Hide*			Create();

		virtual void			Update(float time) override;
		virtual InstantAction*	Reverse() const override;
		virtual Hide*			Clone() const override;

	protected:
		Hide() = default;
	};
}

#endif