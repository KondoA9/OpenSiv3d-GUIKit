﻿#pragma once

#include "Aoba/Component/UIButton.hpp"
#include "Aoba/Component/UIView.hpp"
#include "Aoba/Factory.hpp"

AobaCreateEventComponentNS(TabView, Switched);

namespace s3d::aoba {
    class UITabView : public UIView {
        struct Tab {
            size_t index;
            UIView& view;
            UIButton& selector;

            bool enabled = true;

            void show() {
                selector.setFont(UnifiedFontStyle::DefaultBold);
                view.hidden = false;
            }

            void hide() {
                selector.setFont(UnifiedFontStyle::DefaultLight);
                view.hidden = true;
            }
        };

    private:
        UIView& ui_tabView         = Factory::Create<UIView>(*this);
        UIView& ui_tabSelectorView = Factory::Create<UIView>(*this);

        Array<Tab> m_tabs;
        size_t m_tabIndex = 0;

    public:
        using UIView::UIView;

        size_t index() const {
            return m_tabIndex;
        }

        template <class T>
        T& appendTab(const String& name) {
            static_assert(std::is_base_of<UIView, T>::value, "Specified Type does not inherit gui::UIView.");

            auto& view     = Factory::Create<T>(ui_tabView);
            auto& selector = Factory::Create<UIButton>(ui_tabSelectorView);

            initializeTab(name, selector, view);

            return view;
        }

        void setTab(size_t index);

        void setTabEnabled(size_t index, bool enabled);

    protected:
        void initialize() override;

    private:
        void initializeTab(const String& name, UIButton& selector, UIView& view);
    };
}