#include <GUIKit/GUIKitCore.h>
#include <GUIKit/WindowManager.h>
#include <GUIKit/UnifiedFont.h>

#include "PageManager/PageManager.h"

using namespace s3d::gui;

void GUIKitCore::initialize() {
	m_pageManager = new PageManager();

	UnifiedFont::Initialize();

	WindowManager::Initialize();

	Scene::SetScaleMode(ScaleMode::ResizeFill);

	System::SetTerminationTriggers(UserAction::None);
}

void GUIKitCore::start() {
	if (m_pageManager->initialize()) {
		run();
	}
	else {
		Logger << U"Error(GUIKitCore): No pages are registered.";
	}

	delete m_pageManager;
}

void GUIKitCore::run() {
	// Set scissor rect
	{
		RasterizerState rasterizer = RasterizerState::Default2D;
		rasterizer.scissorEnable = true;
		Graphics2D::Internal::SetRasterizerState(rasterizer);
	}

	while (System::Update()) {
		if (System::GetUserActions() == UserAction::CloseButtonClicked) {
			m_pageManager->setPageTransition(PageTransition::Termination);
		}

		updateGUIKit();
	}
}

void GUIKitCore::updateGUIKit() {
	// Update window state
	WindowManager::Update();

	// Update pages
	m_pageManager->update();

	for (auto& component : m_isolatedComponents) {
		if (component->updatable()) {
			component->updateMouseIntersection();
			component->updateInputEvents();
		}
	}

	UIComponent::CallInputEvents();

	updateMainThreadEvents();

	updateTimeouts();

	// Update color theme
	if (m_animateColor) {
		m_animateColor = animateColor();
	}

	// Draw pages, components and events
	m_pageManager->draw();

	// Draw isolated components
	for (auto& component : m_isolatedComponents) {
		if (component->drawable()) {
			component->draw();
		}
	}

	// Additional drawing events
	for (auto& f : m_drawingEvents) {
		f();
	}
	m_drawingEvents.release();
}

void GUIKitCore::updateMainThreadEvents() {
	std::lock_guard<std::mutex> lock(m_mainThreadInserterMutex);

	for (const auto& f : m_eventsRequestedToRunInMainThread) {
		f();
	}

	m_eventsRequestedToRunInMainThread.release();
}

void GUIKitCore::updateTimeouts() {
	bool alive = false;

	for (auto& timeout : m_timeouts) {
		timeout.update();
		alive |= timeout.isAlive();
	}

	if (!alive) {
		m_timeouts.release();
	}
}

void GUIKitCore::terminate() {
	m_pageManager->setPageTransition(PageTransition::Termination);
}
