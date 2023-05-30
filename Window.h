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

	public:
		explicit Window(const utility::Rectangle rect) :
			window_(CursesAdapter::CreateWindowInstance(rect)),
			cursor_(Cursor::GetInstance()),
			rect_(rect) {}

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
		const utility::Rectangle& GetRect() const
		{
			return rect_;
		}

		void SetPos(const utility::Size2& p)
		{
			CursesAdapter::SetWindowPosition(window_, p);
			rect_ = utility::Rectangle(p, p + rect_.GetSize());
		}

		void SetSize(const utility::Size2& size)
		{
			CursesAdapter::SetWindowSize(window_, size);
			rect_ = utility::Rectangle(rect_.GetPos(), rect_.GetPos() + size);
		}

		void SetWidth(uint16_t width)
		{
			SetSize({ width, GetRect().GetWidth() });
		}

		void SetHeight(uint16_t height)
		{
			SetSize({ GetRect().GetHeight(), height });
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

