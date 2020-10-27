#include "Game.h"
#include "Engine.h"

class Striker : public Game {
private:
    Object cube, deer;
    Shader shader;

public:
    explicit Striker() : Game() {
        Console::message("Striker game class created");
    };

    void Init() override {
        shader("shaders/vertex/basic.vert", "shaders/fragment/basic.frag");
        cube("common/cube.obj");
        deer("common/Deer.obj");
        engine->camera->speed = 10.0f;
        engine->input->setLockedCursorPosition({500, 400});
    }

    void ProcessInput(float dt) override {
        if (engine->input->isKeyboardPressed(GLFW_KEY_W))
            this->engine->camera-> forward(dt);

        if (engine->input->isKeyboardPressed(GLFW_KEY_S))
            this->engine->camera-> backward(dt);

        if (engine->input->isKeyboardPressed(GLFW_KEY_A))
            this->engine->camera-> left(dt);

        if (engine->input->isKeyboardPressed(GLFW_KEY_D))
            this->engine->camera-> right(dt);

        if (engine->input->isKeyboardPressed(GLFW_KEY_LEFT_SHIFT))
            this->engine->camera-> up(dt);

        if (engine->input->isKeyboardPressed(GLFW_KEY_LEFT_CONTROL))
            this->engine->camera-> down(dt);
        glm::vec2 mouseMoved = engine-> input-> getCursorPosition() - glm::vec2 {500, 400};
        engine-> camera-> changeDirection(mouseMoved.x, mouseMoved.y, dt);
    }

    void Render() override {
        cube.draw(shader, engine->camera->getMVP());
        deer.draw(shader, engine->camera->getMVP());
    }

};


auto main() -> int {
    Striker MainGame;
    Engine MainEng(&MainGame);
    return MainEng.run();
}