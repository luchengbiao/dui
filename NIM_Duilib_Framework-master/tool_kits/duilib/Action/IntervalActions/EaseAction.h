#ifndef UI_ACTION_INTERVALACTIONS_EASEACTION_H_
#define UI_ACTION_INTERVALACTIONS_EASEACTION_H_
#pragma once

namespace ui
{
	typedef nbase::GuardPtr<IntervalAction> IntervalActionGuardPtr;

	class UILIB_API EaseAction : public IntervalAction
	{
	public:
		/**
		@brief Get the pointer of the inner action.
		@return The pointer of the inner action.
		*/
		virtual IntervalAction*		GetInnerAction();

		//
		// Overrides
		//
		virtual void				StartWithTarget(Control* target) override;
		virtual void				Stop() override;
		virtual void				Update(float time) override;

	protected:
		EaseAction() = default;
		~EaseAction();
		/**
		@brief Initializes the action.
		@return Return true when the initialization success, otherwise return false.
		*/
		bool						InitWithAction(IntervalAction *action);

	protected:
		/** The inner action */
		IntervalActionGuardPtr		inner_;
	};

	class UILIB_API EaseRateAction : public EaseAction
	{
	public:
		static EaseRateAction*		Create(IntervalAction* action, float rate);
		/**
		@brief Set the rate value for the ease rate action.
		@param rate The value will be set.
		*/
		void						SetRate(float rate) { rate_ = rate; }
		/**
		@brief Get the rate value of the ease rate action.
		@return Return the rate value of the ease rate action.
		*/
		float						GetRate() const { return rate_; }

	protected:
		EaseRateAction() = default;
		/**
		@brief Initializes the action with the inner action and the rate parameter.
		@param pAction The pointer of the inner action.
		@param fRate The value of the rate parameter.
		@return Return true when the initialization success, otherwise return false.
		*/
		bool						InitWithAction(IntervalAction *pAction, float fRate);

	protected:
		float						rate_{ 0 };
	};

#define EASE_TEMPLATE_DECL_CLASS(CLASSNAME) \
	class UILIB_API CLASSNAME : public EaseAction \
	{ \
	protected: \
	CLASSNAME() = default; \
	public: \
	static CLASSNAME* Create(IntervalAction* action); \
	virtual CLASSNAME* Clone() const override; \
	virtual EaseAction* Reverse() const override; \
	virtual void Update(float time) override; \
	};

	/**
	@class EaseExponentialIn
	@brief Ease Exponential In action.
	@details The timeline of inner action will be changed by:
	\f${ 2 }^{ 10*(time-1) }-1*0.001\f$.
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseExponentialIn);

	/**
	@class EaseExponentialOut
	@brief Ease Exponential Out
	@details The timeline of inner action will be changed by:
	\f$1-{ 2 }^{ -10*(time-1) }\f$.
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseExponentialOut);

	/**
	@class EaseExponentialInOut
	@brief Ease Exponential InOut
	@details If time * 2 < 1, the timeline of inner action will be changed by:
	\f$0.5*{ 2 }^{ 10*(time-1) }\f$.
	else, the timeline of inner action will be changed by:
	\f$0.5*(2-{ 2 }^{ -10*(time-1) })\f$.
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseExponentialInOut);

	/**
	@class EaseSineIn
	@brief Ease Sine In
	@details The timeline of inner action will be changed by:
	\f$1-cos(time*\frac { \pi  }{ 2 } )\f$.
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseSineIn);

	/**
	@class EaseSineOut
	@brief Ease Sine Out
	@details The timeline of inner action will be changed by:
	\f$sin(time*\frac { \pi  }{ 2 } )\f$.
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseSineOut);

	/**
	@class EaseSineInOut
	@brief Ease Sine InOut
	@details The timeline of inner action will be changed by:
	\f$-0.5*(cos(\pi *time)-1)\f$.
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseSineInOut);

	/**
	@class EaseBounce
	@brief EaseBounce abstract class.
	@since v0.8.2
	@ingroup Actions
	*/
	class EaseBounce : public EaseAction {};

	/**
	@class EaseBounceIn
	@brief EaseBounceIn action.
	@warning This action doesn't use a bijective function.
	Actions like Sequence might have an unexpected result when used with this action.
	@since v0.8.2
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseBounceIn);

	/**
	@class EaseBounceOut
	@brief EaseBounceOut action.
	@warning This action doesn't use a bijective function.
	Actions like Sequence might have an unexpected result when used with this action.
	@since v0.8.2
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseBounceOut);

	/**
	@class EaseBounceInOut
	@brief EaseBounceInOut action.
	@warning This action doesn't use a bijective function.
	Actions like Sequence might have an unexpected result when used with this action.
	@since v0.8.2
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseBounceInOut);

	/**
	@class EaseBackIn
	@brief EaseBackIn action.
	@warning This action doesn't use a bijective function.
	Actions like Sequence might have an unexpected result when used with this action.
	@since v0.8.2
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseBackIn);

	/**
	@class EaseBackOut
	@brief EaseBackOut action.
	@warning This action doesn't use a bijective function.
	Actions like Sequence might have an unexpected result when used with this action.
	@since v0.8.2
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseBackOut);

	/**
	@class EaseBackInOut
	@brief EaseBackInOut action.
	@warning This action doesn't use a bijective function.
	Actions like Sequence might have an unexpected result when used with this action.
	@since v0.8.2
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseBackInOut);

	/**
	@class EaseQuadraticActionIn
	@brief Ease Quadratic In
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseQuadraticActionIn);

	/**
	@class EaseQuadraticActionOut
	@brief Ease Quadratic Out
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseQuadraticActionOut);

	/**
	@class EaseQuadraticActionInOut
	@brief Ease Quadratic InOut
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseQuadraticActionInOut);

	/**
	@class EaseQuarticActionIn
	@brief Ease Quartic In
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseQuarticActionIn);

	/**
	@class EaseQuarticActionOut
	@brief Ease Quartic Out
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseQuarticActionOut);

	/**
	@class EaseQuarticActionInOut
	@brief Ease Quartic InOut
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseQuarticActionInOut);

	/**
	@class EaseQuinticActionIn
	@brief Ease Quintic In
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseQuinticActionIn);

	/**
	@class EaseQuinticActionOut
	@brief Ease Quintic Out
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseQuinticActionOut);

	/**
	@class EaseQuinticActionInOut
	@brief Ease Quintic InOut
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseQuinticActionInOut);

	/**
	@class EaseCircleActionIn
	@brief Ease Circle In
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseCircleActionIn);

	/**
	@class EaseCircleActionOut
	@brief Ease Circle Out
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseCircleActionOut);

	/**
	@class EaseCircleActionInOut
	@brief Ease Circle InOut
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseCircleActionInOut);

	/**
	@class EaseCubicActionIn
	@brief Ease Cubic In
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseCubicActionIn);

	/**
	@class EaseCubicActionOut
	@brief Ease Cubic Out
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseCubicActionOut);

	/**
	@class EaseCubicActionInOut
	@brief Ease Cubic InOut
	@ingroup Actions
	*/
	EASE_TEMPLATE_DECL_CLASS(EaseCubicActionInOut);
}

#endif