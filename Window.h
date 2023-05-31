#pragma once

#include "Cursor.h"
#include "ICursorOwner.h"
#include "CursesAdapter.h"
#include "Rectangle.h"

namespace re::core {

	class Window : public ICursorOwner {
	private:
		WINDOW* window_;
		Cursor& cursor_;
		utility::Rectangle rect_;
		bool is_owner_ = false;

		static Window default_;

		std::function<void(utility::Rectangle)> on_rect_changed_;

	public:
		explicit Window(const utility::Rectangle rect) :
			window_(CursesAdapter::CreateWindowInstance(rect)),
			cursor_(Cursor::GetInstance()),
			rect_(rect) {
			on_rect_changed_ = [this](const utility::Rectangle rect)
			{
				CursesAdapter::SetWindowPosition(window_, rect.GetPos());
				CursesAdapter::SetWindowSize(window_, rect.GetSize());
			};

			rect_.OnChanged.Connect(on_rect_changed_);
		}

		explicit Window(WINDOW* win) :
			window_(win),
			cursor_(Cursor::GetInstance()),
			rect_(CursesAdapter::GetWindowRect(win)) {}

		~Window() override
		{
			CursesAdapter::DestroyWindowInstance(window_);
		}

		[[nodiscard]]
		WINDOW* GetWindow() const override
		{
			return window_;
		}

		[[nodiscard]]
		Cursor& GetCursor() const
		{
			return cursor_;
		}

		[[nodiscard]]
		bool IsOwner() const override
		{
			return is_owner_;
		}

		[[nodiscard]]
		utility::Rectangle& GetRect()
		{
			return rect_;
		}

		void Update()
		{
			CursesAdapter::UpdateWindow(window_);
		}

		void SetAsOwner() override
		{
			cursor_.SetOwner(*this);
			is_owner_ = true;
		}

		void RemoveOwnership() override
		{
			is_owner_ = false;
		}

		void FillCell(const char ch, const uint32_t attr = 0)
		{
			CursesAdapter::FillWindowCell(window_, ch, attr);
		}

		void ClearCell()
		{
			CursesAdapter::ClearWindowCell(window_);
		}

		void Clear()
		{
			CursesAdapter::ClearWindow(window_);
		}

		void ShowBorder()
		{
			CursesAdapter::ShowWindowBorder(window_);
		}

		static Window& GetDefault()
		{
			return default_;
		}

		void Overlay(const Window& lower) const
		{
			CursesAdapter::OverlayWindow(window_, lower.GetWindow());
		}

		void OverlayBy(const Window& higher) const
		{
			CursesAdapter::OverlayWindow(higher.GetWindow(), window_);
		}

		void Overwrite(const Window& lower) const
		{
			CursesAdapter::OverwriteWindow(window_, lower.GetWindow());
		}

		void OverwriteBy(const Window& higher) const
		{
			CursesAdapter::OverwriteWindow(higher.GetWindow(), window_);
		}

	private:
		Window() :
			window_(CursesAdapter::GetDefaultWindow()),
			cursor_(Cursor::GetInstance()),
			rect_(CursesAdapter::GetWindowRect(CursesAdapter::GetDefaultWindow())),
			is_owner_(true)
		{
			cursor_.SetOwner(*this);
		}
	};

	Window Window::default_{};
}

