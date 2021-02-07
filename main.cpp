#include "engine/source/core/Game.h"
#include "engine/source/core/Engine.h"
#include "engine/source/shaders/standartShader.h"

class Striker : public Game {
private:
    Object *map {}, *cube {};
    Shader *shader {};

public:
    Striker() : Game() {
        Log::loggingLevel = Log::DEBUG;
        Log::info("Striker game class created");
        title = "Striker v1.0";
        // k3rn3lp4nic.b4d
    };

    void Init() override {
        State = GAME_MENU;
        shader = new Shader("runtime/vertex/basic.vert", "runtime/fragment/basic.frag");

        auto *wood = new Material(new Texture("res/cube.png"));

        map = new Object("res/gameMap.obj", wood);
        map-> setShader(shader);
        engine-> renderer-> addToScene(map);
        cube = new Object("res/cube.obj", wood);
        cube-> setShader(shader);
        cube-> transform-> setPosition({1.0f, 0.0f, 10.0f});
        engine-> renderer-> addToScene(cube);
        engine-> renderer-> addLight(cube);

        // todo: make light shader

        engine->camera->setSpeed(100.0f);

        engine->input->setLockedCursorPosition({engine-> window-> getWidth() / 2, engine-> window-> getHeight() / 2});
        engine->input->setLockStatus(true);
        engine->input->setCursorHidden(true);

        engine-> renderer-> setAmbientStrength(1.0f);
        Log::info("Striker Init function ended");
    }

    void ProcessInput(float dt) override {
        if(engine-> window-> isActive() && State == GAME_ACTIVE) {
            if (engine->input->getKeyStatus(GLFW_KEY_SPACE)){
                if (engine->input->getKeyStatus(GLFW_KEY_W))
                    cube-> transform-> setPosition(cube-> transform-> getPosition() + glm::vec3 {1, 0, 0});

                if (engine->input->getKeyStatus(GLFW_KEY_S))
                    cube-> transform-> setPosition(cube-> transform-> getPosition() + glm::vec3 {-1, 0, 0});

                if (engine->input->getKeyStatus(GLFW_KEY_A))
                    cube-> transform-> setPosition(cube-> transform-> getPosition() + glm::vec3 {0, 0, -1});

                if (engine->input->getKeyStatus(GLFW_KEY_D))
                    cube-> transform-> setPosition(cube-> transform-> getPosition() + glm::vec3 {0, 0, 1});

                if (engine->input->getKeyStatus(GLFW_KEY_LEFT_SHIFT))
                    cube-> transform-> setPosition(cube-> transform-> getPosition() + glm::vec3 {0, 1, 0});

                if (engine->input->getKeyStatus(GLFW_KEY_LEFT_CONTROL))
                    cube-> transform-> setPosition(cube-> transform-> getPosition() + glm::vec3 {0, -1, 0});

            } else {
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
            }

            if (engine->input->getKeyStatus(GLFW_KEY_Q) == GLFW_PRESS)
                engine-> renderer -> drawMode(GL_LINE);
            else if (engine->input->getKeyStatus(GLFW_KEY_Q) == GLFW_RELEASE)
                engine-> renderer -> drawMode(GL_FILL);
            if (engine->input->isCursorMoved()) {
                glm::vec3 viewAngles = engine->camera->transform->getEulerAngles();
                glm::vec2 PositionDelta = engine->input->getLockedCursorPosition() - engine->input->getCursorPosition();
                engine->camera->transform-> setEulerAngles({0, viewAngles.y+(PositionDelta.x*dt), viewAngles.z+(PositionDelta.y * dt)});
            }

        } else {
            if (engine->input->getMouseStatus(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                State = GAME_ACTIVE;
            }
        }
    }

    void Render() override {
//        if(engine-> window-> isActive() && State == GAME_ACTIVE) {
//
//        }
    }

};


int main() {
    Striker MainGame;
    Engine MainEng(&MainGame, new Window {MainGame.title, 1000, 900});
    return MainEng.run();
}