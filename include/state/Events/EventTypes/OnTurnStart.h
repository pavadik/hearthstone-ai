#pragma once

#include <tuple>
#include <string>
#include <iostream>
#include <functional>

#include "state/Events/HandlersContainerController.h"
#include "state/Cards/Card.h"
#include "FlowControl/FlowContext.h"

namespace state
{
	namespace Events
	{
		namespace EventTypes
		{
			class OnTurnStart
			{
			public:
				typedef void (*FunctorType)(HandlersContainerController &);
				typedef std::tuple<const Cards::Card &> ArgsTuple;

				template <typename T,
					typename std::enable_if_t<std::is_same<std::decay_t<T>, FunctorType>::value, nullptr_t> = nullptr>
					explicit OnTurnStart(T&& functor) : functor_(functor) {}

				void Handle(HandlersContainerController &controller)
				{
					functor_(controller);
				}

			private:
				FunctorType functor_;
			};
		}
	}
}