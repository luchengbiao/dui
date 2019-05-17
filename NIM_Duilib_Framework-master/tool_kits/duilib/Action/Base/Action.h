#ifndef UI_ACTION_BASE_ACTION_H_
#define UI_ACTION_BASE_ACTION_H_
#pragma once
#include "base/memory/guard_ptr.h"
#include "base/memory/objectcounter.h"

namespace ui
{
	typedef nbase::GuardPtr<Control> ControlGuardPtr;

#define COUNT_NUMBER_OF_ACTION_OJBECTS 1

	class UILIB_API Action : public nbase::SupportGuardPtr
	{
	public:
		enum class DeletionPolicy
		{
			KeepWhenStopped = 0,
			DeleteWhenStopped,
		};

	public:
		/** Default tag used for all the actions. */
		static const int INVALID_TAG = -1;

		/** Returns a clone of action.
		*
		* @return A clone action.
		*/
		virtual Action* Clone() const
		{
			assert(0);
			return nullptr;
		}

		/** Returns a new action that performs the exact reverse of the action.
		*
		* @return A new action that performs the exact reverse of the action.
		*/
		virtual Action*	Reverse() const
		{
			assert(0);
			return nullptr;
		}

		/** Return true if the action has finished.
		*
		* @return Is true if the action has finished.
		*/
		virtual bool IsDone() const { return true; }

		/** Called before the action start. It will also set the target.
		*
		* @param target A certain target.
		*/
		virtual void StartWithTarget(Control* target) { target_ = target; }

		/**
		* Called after the action has finished. It will set the 'target' to nil.
		* IMPORTANT: You should never call "Action::stop()" manually. Instead, use: "target->stopAction(action);".
		*/
		virtual void Stop() { target_ = nullptr; }

		/** Called every frame with it's delta time, dt in seconds. DON'T override unless you know what you are doing.
		*
		* @param dt In seconds.
		*/
		virtual void Step(float dt) {}

		/**
		* Called once per frame. time a value between 0 and 1.

		* For example:
		* - 0 Means that the action just started.
		* - 0.5 Means that the action is in the middle.
		* - 1 Means that the action is over.
		*
		* @param time A value between 0 and 1.
		*/
		virtual void Update(float time) {}

		/** Return certain target.
		*
		* @return A certain target.
		*/
		Control* GetTarget() const { return target_; }

		/** The action will modify the target properties.
		*
		* @param target A certain target.
		*/
		void SetTarget(Control *target) { target_ = target; }

		/** Returns a tag that is used to identify the action easily.
		*
		* @return A tag.
		*/
		int GetTag() const { return tag_; }

		/** Changes the tag that is used to identify the action easily.
		*
		* @param tag Used to identify the action easily.
		*/
		void SetTag(int tag) { tag_ = tag; }

		/** Return a policy that is used to determine the deletion when done.
		*
		* @param A policy.
		*/
		DeletionPolicy getDeletionPolicy() const { return deletionPolicy_; }

		/** Return true if the DeletionPolicy is DeleteWhenStopped.
		*
		* @return Is true if the DeletionPolicy is DeleteWhenStopped.
		*/
		bool NeedToDeleteWhenStopped() const { return deletionPolicy_ == DeletionPolicy::DeleteWhenStopped; }

		/** Changes the policy that is used to determine the deletion when done.
		*
		* @param policy Used to determine the deletion when done.
		*/
		void SetDeletionPolicy(DeletionPolicy policy) { deletionPolicy_ = policy; }

	protected:
		Action() = default;

	protected:
		ControlGuardPtr target_;

		/** The action tag. An identifier of the action. */
		int				tag_{ INVALID_TAG };

		DeletionPolicy	deletionPolicy_{ DeletionPolicy::DeleteWhenStopped };

#if COUNT_NUMBER_OF_ACTION_OJBECTS
		COUNT_LIVE_OBJECTS_VIA_MEMBER(my_counter_);
		public: static void OutputNumberOfLivingObjects();
#endif
	};

	class UILIB_API FiniteTimeAction : public Action
	{
	public:
		float GetDuration() const { return duration_; }

		void SetDuration(float duration) { duration_ = duration; }

	public:
		FiniteTimeAction()
			: duration_(0)
		{}

	protected:
		//! Duration in seconds.
		float duration_;
	};

	// Extra action for making a Sequence or Spawn when only adding one action to it.
	class UILIB_API ExtraAction : public FiniteTimeAction
	{
	public:
		static ExtraAction*		Create() { return new (std::nothrow)ExtraAction; }
		virtual ExtraAction*	Clone() const override { return Create(); }
		virtual ExtraAction*	Reverse() const override { return Create(); }
		virtual void			Update(float time) override {}
		virtual void			Step(float dt) override {}
	};
}

#endif