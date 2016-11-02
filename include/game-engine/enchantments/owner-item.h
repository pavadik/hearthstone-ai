#pragma once

#include "enchantments.h"

namespace GameEngine
{
	// This is a wrapper class for enchantments,
	// which has a reference to the enchantments manager
	// so the caller can call Remove() without parameter

	// This class also acts as a token to access the removal function in enchantments
	//    See: Enchantments::Remove()

	template <typename Target>
	class OwnerItem
	{
	public:
		typedef Enchantments<Target> Manager;
		typedef typename Manager::ManagedItem ManagedItem;

		OwnerItem(Enchantments<Target> & manager, ManagedItem const& item)
			: manager(manager), item(item)
		{
		}

		bool operator==(OwnerItem<Target> const& rhs) const = delete;
		bool operator!=(OwnerItem<Target> const& rhs) const = delete;

		Manager & GetManager() const { return this->manager; }
		ManagedItem Get() const { return this->item; }

	public:
		void Remove()
		{
			this->manager.Remove(this->item);
		}

	private:
		Manager & manager;
		ManagedItem item;
	};
} // namespace GameEngine