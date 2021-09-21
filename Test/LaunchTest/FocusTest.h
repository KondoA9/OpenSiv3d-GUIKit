class FocusTest : public gui::Page {
	using Page::Page;

	void onLoaded() override;
};

void FocusTest::onLoaded() {
	auto& rect = gui::GUIFactory::Create<gui::UIRect>(view);

	const size_t focusTimeout = gui::GUIKit::SetTimeout([] {
		Test::Assert(false, "Focused the component, but event was not triggered");
		}, 3000, false);

	gui::GUIKit::SetTimeout([&rect] {
		rect.focus();
		Test::Assert(rect.isFocused(), "Focused a component, but it is not focused");
		}, 1500, false);

	rect.addEventListener<gui::Focused>([&rect, focusTimeout] {
		gui::GUIKit::StopTimeout(focusTimeout);

		const size_t unfocusTimeout = gui::GUIKit::SetTimeout([] {
			Test::Assert(false, "UnFocused the component, but event was not triggered");
			}, 3000, false);

		gui::GUIKit::SetTimeout([&rect] {
			rect.unFocus();
			Test::Assert(!rect.isFocused(), "UnFocused a component, but it is focused");
			}, 1500, false);

		rect.addEventListener<gui::UnFocused>([unfocusTimeout] {
			gui::GUIKit::StopTimeout(unfocusTimeout);
			});
		});

	// 5sec later, terminate app
	gui::GUIKit::SetTimeout([] {
		gui::GUIKit::Terminate();
		}, 5000, true);
}
