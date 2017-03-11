#pragma once

#include <tuple>
#include <string>
#include <iostream>
#include <functional>

namespace state
{
	namespace Cards
	{
		class Card;
	}

	namespace Events
	{
		namespace EventTypes
		{
			class OnTurnEnd
			{
			public:
				struct Context
				{
					state::State & state_;
					state::FlowContext & flow_context_;
				};

			public:
				typedef std::function<void(HandlersContainerController &, Context &)> FunctorType;
				typedef std::tuple<Context &> ArgsTuple;

				template <typename T,
					typename std::enable_if_t<std::is_same<std::decay_t<T>, FunctorType>::value, nullptr_t> = nullptr>
					explicit OnTurnEnd(T&& functor) : functor_(functor) {}

				void Handle(HandlersContainerController &controller, Context & context)
				{
					functor_(controller, context);
				}

			private:
				FunctorType functor_;
			};
		}
	}
}