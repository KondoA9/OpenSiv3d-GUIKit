#include "ComponentStorage.hpp"

#include "src/AobaLog/AobaLog.hpp"

namespace s3d::aoba {
    ComponentStorage& ComponentStorage::Instance() {
        static ComponentStorage instance;
        return instance;
    }

    void ComponentStorage::Store(const std::shared_ptr<UIBase>& component) {
        Instance().releaseComponentsIfNeed();
        Instance().m_components.push_back(component);
    }

    void ComponentStorage::Release(size_t id) {
        for (auto& component : Instance().m_components) {
            if (component && component->id() == id) {
#if SIV3D_BUILD(DEBUG)
                AobaLog::Log(AobaLog::Type::Info,
                             U"ComponentStorage",
                             U"Destroy " + Unicode::Widen(std::string(typeid(*component).name())) + U" "
                                 + ToString(component->id()));
#endif
                component.reset();
                break;
            }
        }
    }

    std::shared_ptr<UIBase>& ComponentStorage::Get(size_t id) {
        for (auto& component : Instance().m_components) {
            if (component && component->id() == id) {
                return component;
            }
        }

        throw Error{U"A component with identifier \"{}\" not found."_fmt(id)};
    }

    void ComponentStorage::releaseUnusedComponents() {
        m_components.remove_if([](const std::shared_ptr<UIBase>& component) { return !component; });
    }

    void ComponentStorage::releaseComponentsIfNeed() {
        if (m_releaseCounter++; m_releaseCounter == 100) {
            releaseUnusedComponents();

            if (m_components.capacity() != m_components.size()) {
                m_components.shrink_to_fit();
            }

            m_releaseCounter = 0;
        }
    }
}
