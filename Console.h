#pragma once

#include "Singleton.h"
#include "CursesAdapter.h"

namespace re::core
{
	class Console final : public utility::Singleton<Console>
	{
		friend class utility::Singleton<Console>;

	protected:
		Console()
		{
			CursesAdapter::EnterDefaultCursesTerminal();
			if (CursesAdapter::CanUseColors())
			{
				CursesAdapter::UseDefaultColors();
			}
		}

		~Console() override
		{
			CursesAdapter::ExitCursesTerminal();
		}
	};
}
