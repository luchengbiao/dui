#include "StdAfx.h"
#include "Action.h"

namespace ui
{
#if COUNT_NUMBER_OF_ACTION_OJBECTS
	void Action::OutputNumberOfLivingObjects()
	{
		std::string str = "the current number of living Actions is " + std::to_string(Action::live()) + "\n";
		OutputDebugStringA(str.c_str());
	}
#endif
}