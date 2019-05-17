#include "StdAfx.h"
#include "ActionManager.h"
#include <algorithm>
#include <assert.h>

namespace ui
{
	ActionManager* ActionManager::instance_ = nullptr;
	bool ActionManager::instance_destructed_ = false;
	HWND ActionManager::timer_wnd_ = NULL;

	class ActionManager::TraversalGuard
	{
		friend class ActionManager;
		ActionManager& manager_;

		TraversalGuard(ActionManager& manager);
		~TraversalGuard();
		TraversalGuard(const TraversalGuard&) = delete;
		TraversalGuard& operator=(const TraversalGuard&) = delete;
	};

	ActionManager::TraversalGuard::TraversalGuard(ActionManager& manager)
	: manager_(manager)
	{
		++manager_.traversal_of_action_list_;
	}

	ActionManager::TraversalGuard::~TraversalGuard()
	{
		assert(manager_.traversal_of_action_list_);

		if (--manager_.traversal_of_action_list_ == 0)
		{
			auto& list = manager_.action_list_;
			list.erase(std::remove_if(list.begin(), list.end(), [](const ActionGuardPtr& ptr){ return ptr.IsNull(); }), list.end());
		}
	}

	ActionManager* ActionManager::GetInstance()
	{
		static ActionManager action_manager;

		if (instance_destructed_)
		{
			instance_destructed_ = false;

			new (&action_manager) ActionManager; // phoenix rebirth on the ash

			::atexit(DestructInstanceExplicitly);
		}

		return (instance_ = &action_manager);
	}

	void ActionManager::DestructInstanceExplicitly()
	{
		instance_->~ActionManager();
	}

	LRESULT ActionManager::WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
	{
		if (message == timer_msg_) 
		{
			ActionManager::GetInstance()->OnTimer(lparam);
			return 1L;
		}

		return ::DefWindowProcW(hwnd, message, wparam, lparam);
	}

	void ActionManager::TimeCallback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2)
	{
		::PostMessage(timer_wnd_, timer_msg_, 0, uTimerID); // in winmm thread
	}

	ActionManager::ActionManager()
	{
		this->CreateTimer();
	}

	ActionManager::~ActionManager()
	{
		if (instance_ == this)
		{
			instance_destructed_ = true;
		}
	}

	void ActionManager::AddAction(Action* action, Control* target)
	{
		action->StartWithTarget(target);

		action_list_.emplace_back(action);

		if (timer_id_ == 0)
		{
			this->StartTimer();
		}
	}

	void ActionManager::RemoveAction(Action* action)
	{
		if (!action) { return; }

		auto it = std::find_if(action_list_.begin(), action_list_.end(), [=](const ActionGuardPtr& ptr) { return ptr.Get() == action; });
		if (it != action_list_.end())
		{
			delete action;

			if (traversal_of_action_list_)
			{
				it->Reset();
			}
			else
			{
				action_list_.erase(it);
			}
		}
	}

	static inline void TimerOnAction(ActionGuardPtr& action, float dt)
	{
		if (action)
		{
			if (action->GetTarget())
			{
				action->Step(dt);
			}

			if (action->IsDone() || !action->GetTarget())
			{
				if (action->NeedToDeleteWhenStopped())
				{
					delete action;
				}

				action.Reset();
			}
		}
	}

	void ActionManager::CreateTimer()
	{
		LARGE_INTEGER frequency;
		QueryPerformanceFrequency(&frequency);
		performance_frequency_ = frequency.QuadPart;

		if (!timer_wnd_)
		{
			HINSTANCE hinst = ::GetModuleHandle(NULL);

			WNDCLASSEXW wc = { 0 };
			wc.cbSize = sizeof(wc);
			wc.lpfnWndProc = ActionManager::WndProc;
			wc.hInstance = hinst;
			wc.lpszClassName = L"UI_ACTION_MANAGER_ACTIONMANAGER_H_";
			::RegisterClassExW(&wc);

			timer_wnd_ = ::CreateWindowW(L"UI_ACTION_MANAGER_ACTIONMANAGER_H_", 0, 0, 0, 0, 0, 0, HWND_MESSAGE, 0, hinst, 0);
		}
	}

	void ActionManager::StartTimer()
	{
#if COUNT_NUMBER_OF_ACTION_OJBECTS
		Action::OutputNumberOfLivingObjects();
#endif

		QueryPerformanceCounter(&last_performance_counter);		
		timer_id_ = ::timeSetEvent(timer_interval_, timer_precision_, &ActionManager::TimeCallback, NULL, TIME_PERIODIC);

		ASSERT(timer_id_);
	}

	void ActionManager::StopTimer()
	{
#if COUNT_NUMBER_OF_ACTION_OJBECTS
		Action::OutputNumberOfLivingObjects();
#endif

		timeKillEvent(timer_id_);
		timer_id_ = 0;
	}

	void ActionManager::OnTimer(UINT uTimerID)
	{
		LARGE_INTEGER performance_counter;
		QueryPerformanceCounter(&performance_counter);

		float dt = (performance_counter.QuadPart - last_performance_counter.QuadPart) / performance_frequency_; // in second

		{
			TraversalGuard tg(*this);
			auto it = action_list_.begin();
			for (unsigned int i = 0; i < action_list_.size(); ++i, ++it)
			{
				TimerOnAction(*it, dt);
			}

			QueryPerformanceCounter(&last_performance_counter);
		}

		if (action_list_.empty())
		{
			this->StopTimer();
		}
	}
}