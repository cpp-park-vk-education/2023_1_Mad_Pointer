class InputSystem : public ecs::System<InputSystem> {
private:
    int	m_NumKeys;
    unsigned char* m_OldKeyStates;

public:
    InputSystem();
    ~InputSystem();
    virtual void preUpdate(float deltaTime) override;
};