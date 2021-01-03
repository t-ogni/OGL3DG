#include "engine/source/core/Game.h"
#include "engine/source/core/Engine.h"

class Striker : public Game {
private:
    Object *map, *cube;
    Object *baseLight;
    Shader *shader;
    int secs;
    bool fillTextures = true;
    bool started = false;

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
        map = new Object("res/gameMap.obj");
        map-> setShader(shader);
        engine-> renderer-> addToScene(map);

        cube = new Object("res/cube.obj", new Material(new Texture("res/cube.png"), glm::vec4 {0.1f}));
        cube-> setShader(shader);
        cube-> transform-> setPosition({5.0f, 10.0f, -2.0f});
        engine-> renderer-> addToScene(cube);
        engine-> renderer-> addLight(cube);

        // todo: make light shader

        engine->camera->setSpeed(10.0f);

        engine->input->setLockedCursorPosition({engine-> window-> getWidth() / 2, engine-> window-> getHeight() / 2});
        engine->input->setLockStatus(true);
        engine->input->setCursorHidden(true);

        engine-> renderer-> setAmbientStrength(1.0f);
        Log::info("Init ended");
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
                glm::vec2 mouseMoved =
                        -(engine->input->getCursorPosition() - engine->input->getLockedCursorPosition()) * 0.2f;
                // -90deg <= vertical <= 90deg or mouse going middle
                if ((-1.57f <= viewAngles.y && viewAngles.y <= 1.57f) || abs(mouseMoved.y) < 1.57f)
                    engine->camera->transform-> setEulerAngles({mouseMoved.x*dt, mouseMoved.y*dt, 0});
                else
                    engine->camera->transform-> setEulerAngles({mouseMoved.x*dt, 1.57 - (viewAngles.y + 0.1 / viewAngles.y)*dt, 0});

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