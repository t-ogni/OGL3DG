#include "engine/include/Game.h"
#include "engine/include/Engine.h"

class Striker : public Game {
private:
    Object *cube;
    Shader *shader;
    int8_t fillTextures = 0;

public:
    Striker() : Game() {
        Console::message("Striker game class created");
    };

    void Init() override {
        shader = new Shader("shaders/vertex/basic.vert", "shaders/fragment/basic.frag");
        cube = new Object("res/cube.obj");
        engine->camera->speed = 20.0f;
        engine->input->setLockedCursorPosition({engine-> window-> getWidth() / 2, engine-> window-> getHeight() / 2});
        engine->input->setLockStatus(true);
        engine->input->setCursorHidden(true);
        Console::message("Init ended");
    }

    void ProcessInput(float dt) override {
        if(engine-> window-> isActive()) {
            if (engine->input->getKeyStatus(GLFW_KEY_W))
                engine->camera->forward(dt);

            if (engine->input->getKeyStatus(GLFW_KEY_S))
                engine->camera->backward(dt);

            if (engine->input->getKeyStatus(GLFW_KEY_A))
                engine->camera->left(dt);

            if (engine->input->getKeyStatus(GLFW_KEY_D))
                engine->camera->right(dt);

            if (engine->input->getKeyStatus(GLFW_KEY_LEFT_SHIFT))
                engine->camera->up(dt);

            if (engine->input->getKeyStatus(GLFW_KEY_LEFT_CONTROL))
                engine->camera->down(dt);

            if (engine->input->getKeyStatus(GLFW_KEY_Q) == GLFW_PRESS){
                if (fillTextures % 1000 == 0)
                    glPolygonMode(GL_FRONT_AND_BACK, (fillTextures % 2 == 0) ? GL_FILL : GL_LINE);
                else
                    fillTextures++;

            }

            glm::vec2 mouseMoved = -(engine->input->getCursorPosition() - engine->input->getLockedCursorPosition()) * 0.2f;
            engine->camera->changeDirection(mouseMoved.x, mouseMoved.y, dt);

            Console::message("pos: %d %d %d \t| looking at: %d %d",
                             engine-> camera-> getPosition().x,
                             engine-> camera-> getPosition().y,
                             engine-> camera-> getPosition().z,
                             engine-> camera-> getDirection().x,
                             engine-> camera-> getDirection().y);
        }
    }

    void Render() override {

    }

};


int main() {
    Striker MainGame;
    Engine MainEng(&MainGame, new Window {MainGame.title, 1000, 900});
    return MainEng.run();
}