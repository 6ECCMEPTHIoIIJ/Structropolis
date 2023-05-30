#pragma once

#include "CursesAdapter.h"

namespace re::core {
	class ICursorOwner {
	public:
		virtual ~ICursorOwner() = default;

		virtual void SetAsOwner() = 0;

		virtual void RemoveOwnership() = 0;

		[[nodiscard]] virtual bool IsOwner() const = 0;

		[[nodiscard]] virtual WINDOW* GetWindow() const = 0;
	};
}

