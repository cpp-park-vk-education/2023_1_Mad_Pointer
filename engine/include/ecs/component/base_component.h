


namespace ecs {
    class ComponentBase {
    public:
        ComponentBase();
        virtual ~ComponentBase();

        ComponentId getComponentId() const {
            return m_componentId;
        }

        EntiryId getOwner() const {
            return m_owner;
        }

        void setActive(bool state) {
            m_enabled = state;
        }

        bool isActive() const {
            return m_enabled;
        }
    protected:
    ComponentId m_componentId;
    EntityId m_owner;
    bool m_enabled;
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


    struct Direction {
        bool m_right = false;
        bool m_left = false;
        bool m_up = false;
        bool m_down = false;
    };


}