#ifndef UI_ACTION_MANAGER_ACTIONMANAGER_H_
#define UI_ACTION_MANAGER_ACTIONMANAGER_H_
#pragma once
#include <list>

namespace ui
{
	typedef nbase::GuardPtr<Action> ActionGuardPtr;
	typedef std::list<ActionGuardPtr> ActionList;

	class UILIB_API ActionManager
	{
	public:
		static ActionManager*	GetInstance();

		ActionManager(const ActionManager&) = delete;
		ActionManager& operator=(const ActionManager&) = delete;

		void					AddAction(Action* action, Control* target);
		void					RemoveAction(Action* action);

	private:
		ActionManager();
		~ActionManager();

		void					CreateTimer();

		void					StartTimer();
		void					StopTimer();

		void					OnTimer(UINT uTimerID);

		static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
		static void CALLBACK	TimeCallback(UINT uTimerID, UINT uMsg, DWORD_PTR dwUser, DWORD_PTR dw1, DWORD_PTR dw2);
		static void				DestructInstanceExplicitly();

	private:
		double					performance_frequency_;
		LARGE_INTEGER			last_performance_counter;
		UINT					timer_id_{ 0 };
		ActionList				action_list_;
		int						traversal_of_action_list_{ 0 };

		static ActionManager*	instance_;
		static bool				instance_destructed_;

		static HWND				timer_wnd_;
		static const UINT		timer_msg_{ WM_USER + 8888 };
		static const UINT		timer_interval_{ 16 }; // 1000 / 60 = 16 milliseconds
		static const UINT		timer_precision_{ 1 }; // 1 milliseconds

		class TraversalGuard;
		friend class TraversalGuard;
	};
}

#endif