#include "Stdafx.h"
#include "ControlAdaptor.h"

namespace ui
{
	ControlAdaptor::ControlAdaptor(Control* ctrl) 
	: ctrl_(ctrl) 
	{}

	void ControlAdaptor::RunAction(Action* action)
	{
		ActionManager::GetInstance()->AddAction(action, ctrl_);
	}
}

