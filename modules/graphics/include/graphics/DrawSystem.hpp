#pragma once

class Render;
class Entity;

class DrawSystem : public flm::System
{
private:
    class Node final : public std::enable_shared_from_this<Node>
    {
    public:
        Node() = default;
        ~Node();

        Node(const Node&) = delete;
        Node& operator=(const Node&) = delete;
        Node(const Node&&) = delete;
        Node& operator=(const Node&&) = delete;

        bool operator<(const Node& other) const;

        flm::Id AddChild(std::shared_ptr<flm::Entity> entity, int64_t drawOrder);

        std::shared_ptr<DrawSystem::Node> GetChild(flm::Id id);

        bool RemoveChild(flm::Id id);

        void Apply(std::function<void(std::shared_ptr<flm::Entity>)> function);

        void Draw(std::shared_ptr<Render> render, const float dt);

    public:
        const flm::Id id = flm::UniqueId();
        int64_t drawOrder = 0;
        std::shared_ptr<flm::Entity> entity = nullptr;

    private:
        std::weak_ptr<Node> m_parent;
        std::vector<std::shared_ptr<Node>> m_children = {};
    };

public:
    DrawSystem(std::shared_ptr<Render> render);

    std::shared_ptr<DrawSystem::Node> GetRoot();

    void Update(float dt) override;

private:
    std::shared_ptr<Node> m_root = std::make_shared<Node>();
    std::shared_ptr<Render> m_render = nullptr;
};
