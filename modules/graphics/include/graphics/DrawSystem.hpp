#pragma once

class Render;

class DrawSystem : public flm::System
{
public:
    DrawSystem(std::shared_ptr<Render> render);

    std::shared_ptr<flm::Node<flm::Entity>> Root();

    void Update(float dt) override;

private:
    std::shared_ptr<flm::Node<flm::Entity>> m_root = std::make_shared<flm::Node<flm::Entity>>();
    std::shared_ptr<Render> m_render = nullptr;
};
