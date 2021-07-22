#include "Test.h"

#include <GUIKit/GUIKit.h>

#include "PagingTest.h"
#include "ComponentsTest.h"
#include "FocusTest.h"

void Main() {
	Window::Resize(1280, 720);

	gui::GUIKit::AppendPage<LifeCycleTest>(U"LifeCycleTest");
	gui::GUIKit::AppendPage<ComponentsTest>(U"ComponentsTest");
	gui::GUIKit::AppendPage<FocusTest>(U"FocusTest");

	gui::GUIKit::Start();

	pagingTest.validate();
}