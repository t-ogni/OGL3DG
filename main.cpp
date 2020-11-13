#include "engine/include/Game.h"
#include "engine/include/Engine.h"

class Striker : public Game {
private:
    Object cube, plane;
    Shader shader;
    bool fillTextures = true;

public:
    explicit Striker() : Game() {
        Console::message("Striker game class created");
    };

    void Init() override {
        shader("shaders/vertex/basic.vert", "shaders/fragment/basic.frag");
        cube("res/cube.obj", new Texture("res/cube.png"));
        cube.setShader(&shader);
        ///plane("res/biplane.obj");
        engine->camera->speed = 20.0f;
        engine->input->setLockedCursorPosition({engine-> window-> getWidth() / 2, engine-> window-> getHeight() / 2});
        engine->input->setLockStatus(true);
        engine->input->setCursorHidden(true);
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
                fillTextures = !fillTextures;
                glPolygonMode(GL_FRONT_AND_BACK, fillTextures ? GL_FILL : GL_LINE);
            }

            float vertical = engine-> camera-> getDirection().y;
            glm::vec2 mouseMoved = {0.f, 0.f};
            if (-90.0f < vertical or vertical < 90.0f){
                mouseMoved =
                    -(engine->input->getCursorPosition() - engine->input->getLockedCursorPosition()) * 0.2f;
            } else {
                mouseMoved =
                    -(glm::vec2 {0, 90} - engine-> camera-> getDirection() +
                    (glm::vec2{engine->input->getCursorPosition().x - engine->input->getLockedCursorPosition().x, 0}) * 0.2f) ;
            }
            engine->camera->changeDirection(mouseMoved.x, mouseMoved.y, dt);
        }
    }

    void Render() override {
        cube.draw(engine->camera->getMVP());
        //deer.draw(shader, engine->camera->getMVP());
    }

};


int main() {
    Striker MainGame;
    Engine MainEng(&MainGame, new Window {"Ab", 1000, 900});
    return MainEng.run();
}