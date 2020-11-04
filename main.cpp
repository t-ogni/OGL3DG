#include "engine/include/Game.h"
#include "engine/include/Engine.h"

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
        engine->camera->speed = 20.0f;
        engine->input->setLockedCursorPosition({engine-> window-> getWidth() / 2, engine-> window-> getHeight() / 2});
        engine->input->setLockStatus(true);
        engine->input->setCursorHidden(true);
    }

    void ProcessInput(float dt) override {
        if (engine->input->isKeyboardPressed(GLFW_KEY_W))
            engine->camera-> forward(dt);

        if (engine->input->isKeyboardPressed(GLFW_KEY_S))
            engine->camera-> backward(dt);

        if (engine->input->isKeyboardPressed(GLFW_KEY_A))
            engine->camera-> left(dt);

        if (engine->input->isKeyboardPressed(GLFW_KEY_D))
            engine->camera-> right(dt);

        if (engine->input->isKeyboardPressed(GLFW_KEY_LEFT_SHIFT))
            engine->camera-> up(dt);

        if (engine->input->isKeyboardPressed(GLFW_KEY_LEFT_CONTROL))
            engine->camera-> down(dt);

        if (engine->input->isKeyboardPressed(GLFW_KEY_Q))
            engine-> camera-> setPos({0.f, 100.f, -10.f});

        glm::vec2 mouseMoved = -(engine-> input-> getCursorPosition() - engine-> input-> getLockedCursorPosition()) * 0.2f;
        engine-> camera-> changeDirection(mouseMoved.x, mouseMoved.y, dt);
    }

    void Render() override {
        cube.draw(shader, engine->camera->getMVP());
        deer.draw(shader, engine->camera->getMVP());
    }

};


int main(int argc, char *argv[]) {
    Striker MainGame;
    Engine MainEng(&MainGame, new Window {"Ab", 1000, 900});
    return MainEng.run();
}