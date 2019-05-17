#ifndef UI_ACTION_INTERVALACTIONS_SEQUENCE_H_
#define UI_ACTION_INTERVALACTIONS_SEQUENCE_H_
#pragma once

namespace ui
{
	typedef nbase::GuardPtr<FiniteTimeAction> FiniteTimeActionGuardPtr;

	class UILIB_API Sequence : public IntervalAction
	{
	public:
		/** Helper constructor to create an array of sequenceable actions.
		*
		* @return A Sequence object.
		*/
		template<typename... FiniteTimeActions>
		static Sequence*			Create(FiniteTimeActions*... actions);

		/** Helper constructor to create an array of sequenceable actions given an array.
		*
		* @param arrayOfActions An array of sequenceable actions.
		* @return A Sequence object.
		*/
		static Sequence*			Create(const std::vector<FiniteTimeAction*>& arrayOfActions);
		/** Creates the action.
		* @param actionOne The first sequenceable action.
		* @param actionTwo The second sequenceable action.
		* @return A Sequence object.
		*/
		static Sequence*			CreateWithTwoActions(FiniteTimeAction* action0, FiniteTimeAction* action1);

		//
		// Overrides
		//
		virtual Sequence*			Clone() const override;
		virtual Sequence*			Reverse() const override;
		virtual void				StartWithTarget(Control *target) override;
		virtual void				Stop() override;
		virtual bool				IsDone() const override;
		/**
		* @param t In seconds.
		*/
		virtual void				Update(float t) override;

	protected:
		virtual ~Sequence();

		/** initializes the action */
		bool						InitWithTwoActions(FiniteTimeAction *pActionOne, FiniteTimeAction *pActionTwo);
		bool						Init(const std::vector<FiniteTimeAction*>& arrayOfActions);

	protected:
		FiniteTimeActionGuardPtr	action0_;
		FiniteTimeActionGuardPtr	action1_;
		float						split_{ 0 };
		int							last_{ 0 };
	};

	template<typename... FiniteTimeActions>
	struct ActionsCollecter;

	template<typename FiniteTimeAction0, typename... FiniteTimeActions>
	struct ActionsCollecter<FiniteTimeAction0, FiniteTimeActions...>
	{
		static void Apply(std::vector<FiniteTimeAction*>& arrayOfActions, FiniteTimeAction* action0, FiniteTimeActions*... actions)
		{
			arrayOfActions.emplace_back(action0);

			ActionsCollecter<FiniteTimeActions...>::Apply(arrayOfActions, actions...);
		}
	};

	template<>
	struct ActionsCollecter<>
	{
		static void Apply(std::vector<FiniteTimeAction*>& arrayOfActions)
		{}
	};

	template<typename... FiniteTimeActions>
	Sequence* Sequence::Create(FiniteTimeActions*... actions)
	{
		std::vector<FiniteTimeAction*> arrayOfActions;
		ActionsCollecter<FiniteTimeActions...>::Apply(arrayOfActions, actions...);

		return Sequence::Create(arrayOfActions);
	}
}

#endif