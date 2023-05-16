// GameObjectFile

class ControllerBase {
public:

    ControllerBase() {}

    virtual ~ControllerBase() {}

    virtual bool Possess(const GameObjectId gameObjectId) = 0;

    virtual void Unpossess() = 0;

    virtual GameObjectId GetPossessed() const = 0;

    virtual void Update(float deltaTime) = 0;

}; // class IController