#include "stdafx.h"
#include "basic_form.h"

using namespace ui;

const std::wstring BasicForm::kClassName = L"Basic";

BasicForm::BasicForm()
{
}


BasicForm::~BasicForm()
{
}

std::wstring BasicForm::GetSkinFolder()
{
	return L"basic";
}

std::wstring BasicForm::GetSkinFile()
{
	return L"basic.xml";
}

std::wstring BasicForm::GetWindowClassName() const
{
	return kClassName;
}

void BasicForm::InitWindow()
{
	auto button = FindControlWithType<ui::Button>(L"maxbtn");
	nbase::GuardPtr<ui::Button> guard_button(button);

	/*
	nbase::GuardPtr<ui::Button> guard_button(button);

	StdClosure blink_task = [=]() {
	guard_button.TryToPerformClosureOnThread(kThreadUI, [=]{
	auto rect = guard_button->GetPos();
	rect.Offset(2, 2);

	guard_button->SetPos(rect);
	});
	};
	nbase::ThreadManager::PostRepeatedTask(kThreadGlobalMisc, ToWeakCallback(blink_task), nbase::TimeDelta::FromMilliseconds(16));
	*/

	nbase::ThreadManager::PostTask(kThreadUI, [=]{
		auto pt = LeftTop(button);
		CA(button).RunAction(Sequence::Create(MoveBy::Create(1.0f, CPoint(500, 500)),
											  Delay::Create(1),
											  EaseBackInOut::Create(MoveBy::Create(0.5f, CPoint(0, -500))),
											  Hide::Create(),
											  Delay::Create(1),
											  Show::Create(),
										      Place::Create(pt),
											  EaseBackOut::Create(MoveBy::Create(0.5f, CPoint(500, 500))),
											  RemoveSelf::Create(),
											  Show::Create()
											  ));
	});

	nbase::ThreadManager::PostDelayedTask(kThreadUI, [=]{
		if (guard_button)
		{
			guard_button->GetParent()->Remove(guard_button);
		}
	}, nbase::TimeDelta::FromSeconds(2));
}

LRESULT BasicForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}
