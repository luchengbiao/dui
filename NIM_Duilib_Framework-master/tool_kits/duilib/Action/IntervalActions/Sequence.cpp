#include "StdAfx.h"
#include "Sequence.h"

namespace ui
{
	Sequence* Sequence::Create(const std::vector<FiniteTimeAction*>& arrayOfActions)
	{
		Sequence* seq = new (std::nothrow) Sequence;

		if (seq && seq->Init(arrayOfActions))
		{
			return seq;
		}

		delete seq;

		return nullptr;
	}

	Sequence* Sequence::CreateWithTwoActions(FiniteTimeAction *actionOne, FiniteTimeAction *actionTwo)
	{
		Sequence *sequence = new (std::nothrow) Sequence();
		if (sequence && sequence->InitWithTwoActions(actionOne, actionTwo))
		{
			return sequence;
		}

		delete sequence;

		return nullptr;
	}

	bool Sequence::Init(const std::vector<FiniteTimeAction*>& arrayOfActions)
	{
		auto count = arrayOfActions.size();

		if (count == 0)
			return false;

		if (count == 1)
			return InitWithTwoActions(arrayOfActions.at(0), ExtraAction::Create());

		// else size > 1
		auto prev = arrayOfActions.at(0);
		for (unsigned int i = 1; i < count - 1; ++i)
		{
			prev = CreateWithTwoActions(prev, arrayOfActions.at(i));
		}

		return InitWithTwoActions(prev, arrayOfActions.at(count - 1));
	}

	bool Sequence::InitWithTwoActions(FiniteTimeAction* action0, FiniteTimeAction* action1)
	{
		assert(action0);
		assert(action1);
		if (action0 == nullptr || action1 == nullptr)
		{
			return false;
		}

		float d = action0->GetDuration() + action1->GetDuration();
		IntervalAction::InitWithDuration(d);

		action0_ = action0;
		action1_ = action1;

		return true;
	}

	bool Sequence::IsDone() const
	{
		if (dynamic_cast<InstantAction*>(action1_.Get()))
			return (done_ && action1_->IsDone());
		else
			return done_;
	}

	Sequence* Sequence::Clone() const
	{
		// no copy constructor
		if (action0_ && action1_)
		{
			return Sequence::Create(dynamic_cast<FiniteTimeAction*>(action0_->Clone()), dynamic_cast<FiniteTimeAction*>(action1_->Clone()));
		}

		return nullptr;
	}

	Sequence::~Sequence()
	{
		if (action0_)
		{
			if (action0_->NeedToDeleteWhenStopped())
			{
				delete action0_;
			}

			action0_.Reset();
		}

		if (action1_)
		{
			if (action1_->NeedToDeleteWhenStopped())
			{
				delete action1_;
			}

			action1_.Reset();
		}
	}

	void Sequence::StartWithTarget(Control* target)
	{
		if (target == nullptr)
		{
			//log("Sequence::startWithTarget error: target is nullptr!");
			return;
		}

		if (action0_ == nullptr || action1_ == nullptr)
		{
			//log("Sequence::startWithTarget error: action0_ or action1_ is nullptr!");
			return;
		}

		if (duration_ > FLT_EPSILON)
			// fix #14936 - FLT_EPSILON (instant action) / very fast duration (0.001) leads to wrong split, that leads to call instant action few times
			split_ = action0_->GetDuration() > FLT_EPSILON ? action0_->GetDuration() / duration_ : 0;

		IntervalAction::StartWithTarget(target);

		last_ = -1;
	}

	void Sequence::Stop()
	{
		FiniteTimeAction* last_action = (last_ >= 0) ? (last_ == 0 ? action0_ : action1_) : nullptr;
		if (last_action)
		{
			last_action->Stop();
		}

		IntervalAction::Stop();
	}

	void Sequence::Update(float t)
	{
		int found = 0;
		float new_t = 0.0f;

		if (t < split_)
		{
			// action0
			found = 0;

			if (split_ != 0)
				new_t = t / split_;
			else
				new_t = 1;

		}
		else
		{
			// action1
			found = 1;

			if (split_ == 1)
				new_t = 1;
			else
				new_t = (t - split_) / (1 - split_);
		}

		if (found == 1)
		{
			if (last_ == -1)
			{
				// action0 was skipped, execute it.
				action0_->StartWithTarget(target_);
				action0_->Update(1.0f);
				action0_->Stop();
			}
			else if (last_ == 0)
			{
				// switching to action 1. stop action 0.
				action0_->Update(1.0f);
				action0_->Stop();
			}
		}
		else if (found == 0 && last_ == 1)
		{
			// Reverse mode ?
			// FIXME: Bug. this case doesn't contemplate when last_==-1, found=0 and in "reverse mode"
			// since it will require a hack to know if an action is on reverse mode or not.
			// "step" should be overridden, and the "reverseMode" value propagated to inner Sequences.
			action1_->Update(0);
			action1_->Stop();
		}

		FiniteTimeAction* found_action = found == 0 ? action0_ : action1_;

		if (found_action)
		{
			// Last action found and it is done.
			if (found == last_ && found_action->IsDone())
			{
				return;
			}

			// Last action found and it is done
			if (found != last_)
			{
				found_action->StartWithTarget(target_);
			}

			found_action->Update(new_t);
		}
		else
		{
			return;
		}

		last_ = found;
	}

	Sequence* Sequence::Reverse() const
	{
		if (action0_ && action1_)
		{
			return Sequence::CreateWithTwoActions(dynamic_cast<FiniteTimeAction*>(action1_->Reverse()), dynamic_cast<FiniteTimeAction*>(action0_->Reverse()));
		}

		return nullptr;
	}
}