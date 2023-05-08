struct Direction {
    bool m_right = false;
    bool m_left = false;
    bool m_up = false;
    bool m_down = false;
};

namespace ecs {
    class ComponentBase {

    };

    class VelocityComponent : ComponentBase {
        double m_velocity = 0;
        Direction m_direction;
    };

    class TextureComponent : ComponentBase {
        Texture* m_texture = nullptr;
    };

    class TransformComponent : ComponentBase {
        double m_x = 0;
        double m_y = 0;
    };

    class HeroControllerComponent : ComponentBase {

    };

    class BodyComponent : ComponentBase {

    };

    class ComponentStorage {
    public:
        ComponentStorage(size_t size = 100);

        inline size_t size() const {

        }

        inline
    };
}