#include "StdAfx.h"
#include "EaseAction.h"

namespace ui
{
	bool EaseAction::InitWithAction(IntervalAction* action)
	{
		if (action == nullptr)
		{
			return false;
		}

		if (IntervalAction::InitWithDuration(action->GetDuration()))
		{
			inner_ = action;

			return true;
		}

		return false;
	}

	EaseAction::~EaseAction(void)
	{
		if (inner_)
		{
			if (inner_->NeedToDeleteWhenStopped())
			{
				delete inner_;
			}

			inner_.Reset();
		}
	}

	void EaseAction::StartWithTarget(Control* target)
	{
		if (target && inner_)
		{
			IntervalAction::StartWithTarget(target);
			inner_->StartWithTarget(target_);
		}
		else
		{
		}
	}

	void EaseAction::Stop(void)
	{
		if (inner_)
		{
			inner_->Stop();
		}

		IntervalAction::Stop();
	}

	void EaseAction::Update(float time)
	{
		if (inner_)
		{
			inner_->Update(time);
		}
	}

	IntervalAction* EaseAction::GetInnerAction()
	{
		return inner_;
	}

	EaseRateAction* EaseRateAction::Create(IntervalAction* action, float rate)
	{
		EaseRateAction *easeRateAction = new (std::nothrow) EaseRateAction();
		if (easeRateAction && easeRateAction->InitWithAction(action, rate))
		{
			return easeRateAction;
		}

		delete easeRateAction;

		return nullptr;
	}

	bool EaseRateAction::InitWithAction(IntervalAction *action, float rate)
	{
		if (EaseAction::InitWithAction(action))
		{
			rate_ = rate;

			return true;
		}

		return false;
	}

#define EASE_TEMPLATE_IMPL(CLASSNAME, TWEEN_FUNC, REVERSE_CLASSNAME) \
	CLASSNAME* CLASSNAME::Create(IntervalAction* action) \
	{ \
	CLASSNAME *ease = new (std::nothrow) CLASSNAME(); \
	if (ease && ease->InitWithAction(action)) { return ease; }\
	delete ease; \
	return nullptr; \
	} \
	CLASSNAME* CLASSNAME::Clone() const \
	{ \
	if (inner_) return CLASSNAME::Create(dynamic_cast<IntervalAction*>(inner_->Clone())); \
	return nullptr; \
	} \
	EaseAction* CLASSNAME::Reverse() const \
	{ \
	return REVERSE_CLASSNAME::Create(dynamic_cast<IntervalAction*>(inner_->Reverse())); \
	} \
	void CLASSNAME::Update(float time) \
	{ \
	if (inner_) inner_->Update(TWEEN_FUNC(time)); \
	}

	EASE_TEMPLATE_IMPL(EaseExponentialIn, tweenfunc::expoEaseIn, EaseExponentialOut);
	EASE_TEMPLATE_IMPL(EaseExponentialOut, tweenfunc::expoEaseOut, EaseExponentialIn);
	EASE_TEMPLATE_IMPL(EaseExponentialInOut, tweenfunc::expoEaseInOut, EaseExponentialInOut);
	EASE_TEMPLATE_IMPL(EaseSineIn, tweenfunc::sineEaseIn, EaseSineOut);
	EASE_TEMPLATE_IMPL(EaseSineOut, tweenfunc::sineEaseOut, EaseSineIn);
	EASE_TEMPLATE_IMPL(EaseSineInOut, tweenfunc::sineEaseInOut, EaseSineInOut);
	EASE_TEMPLATE_IMPL(EaseBounceIn, tweenfunc::bounceEaseIn, EaseBounceOut);
	EASE_TEMPLATE_IMPL(EaseBounceOut, tweenfunc::bounceEaseOut, EaseBounceIn);
	EASE_TEMPLATE_IMPL(EaseBounceInOut, tweenfunc::bounceEaseInOut, EaseBounceInOut);
	EASE_TEMPLATE_IMPL(EaseBackIn, tweenfunc::backEaseIn, EaseBackOut);
	EASE_TEMPLATE_IMPL(EaseBackOut, tweenfunc::backEaseOut, EaseBackIn);
	EASE_TEMPLATE_IMPL(EaseBackInOut, tweenfunc::backEaseInOut, EaseBackInOut);
	EASE_TEMPLATE_IMPL(EaseQuadraticActionIn, tweenfunc::quadraticIn, EaseQuadraticActionIn);
	EASE_TEMPLATE_IMPL(EaseQuadraticActionOut, tweenfunc::quadraticOut, EaseQuadraticActionOut);
	EASE_TEMPLATE_IMPL(EaseQuadraticActionInOut, tweenfunc::quadraticInOut, EaseQuadraticActionInOut);
	EASE_TEMPLATE_IMPL(EaseQuarticActionIn, tweenfunc::quartEaseIn, EaseQuarticActionIn);
	EASE_TEMPLATE_IMPL(EaseQuarticActionOut, tweenfunc::quartEaseOut, EaseQuarticActionOut);
	EASE_TEMPLATE_IMPL(EaseQuarticActionInOut, tweenfunc::quartEaseInOut, EaseQuarticActionInOut);
	EASE_TEMPLATE_IMPL(EaseQuinticActionIn, tweenfunc::quintEaseIn, EaseQuinticActionIn);
	EASE_TEMPLATE_IMPL(EaseQuinticActionOut, tweenfunc::quintEaseOut, EaseQuinticActionOut);
	EASE_TEMPLATE_IMPL(EaseQuinticActionInOut, tweenfunc::quintEaseInOut, EaseQuinticActionInOut);
	EASE_TEMPLATE_IMPL(EaseCircleActionIn, tweenfunc::circEaseIn, EaseCircleActionIn);
	EASE_TEMPLATE_IMPL(EaseCircleActionOut, tweenfunc::circEaseOut, EaseCircleActionOut);
	EASE_TEMPLATE_IMPL(EaseCircleActionInOut, tweenfunc::circEaseInOut, EaseCircleActionInOut);
	EASE_TEMPLATE_IMPL(EaseCubicActionIn, tweenfunc::cubicEaseIn, EaseCubicActionIn);
	EASE_TEMPLATE_IMPL(EaseCubicActionOut, tweenfunc::cubicEaseOut, EaseCubicActionOut);
	EASE_TEMPLATE_IMPL(EaseCubicActionInOut, tweenfunc::cubicEaseInOut, EaseCubicActionInOut);
}