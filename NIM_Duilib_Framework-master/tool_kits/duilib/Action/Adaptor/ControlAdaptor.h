#ifndef UI_ACTION_ADAPTOR_CONTROLADAPTOR_H_
#define UI_ACTION_ADAPTOR_CONTROLADAPTOR_H_
#pragma once

namespace ui
{
	class UILIB_API ControlAdaptor
	{
	public:
		ControlAdaptor(Control* ctrl);

		void RunAction(Action* action);

	private:
		Control* ctrl_;
	};
}

#endif