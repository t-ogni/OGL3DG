#include "engine/source/core/Game.h"
#include "engine/source/core/Engine.h"
#include "engine/source/shaders/standartShader.h"
#include "engine/source/core/Console.h"
#include "engine/source/core/Time.h"

class Striker : public Game {
private:
    Object *cube {};
    Shader *shader;

public:
    Striker() :
        Game(),
        shader() {
        Log.loggingLevel = Log.WARNING;
        Log.info("Striker game class created");
        title = "Striker v1.0";
    };

    void Init() override {
        Window::setClearColor(0.1f, 0.7f, 0.9f);
        State = GAME_MENU;
        shader = new Shader("runtime/BASIC/basic.vert", "runtime/BASIC/basic.frag");
        auto lightShader = new Shader("runtime/light/basic.vert", "runtime/light/basic.frag");

        auto *wood = new Material(new Texture("res/cube.png"), glm::vec4 {1.0f});

//        auto map = new Object("res/spot/sportcenter_obj.obj");
        auto map = new Object("res/gameMap.obj", wood);
        map-> setShader(shader);
        engine-> renderer-> addToScene(*map);

        cube = new Object("res/cube.obj", wood);
        cube-> setShader(shader);
        cube-> transform-> setPosition({1.0f, 0.0f, 10.0f});
        engine-> renderer-> addToScene(*cube);

        auto light = new Object("res/cube.obj");
        light-> setMaterial(new Material(glm::vec4 {1.0f}));
        light-> setShader(lightShader);
        engine-> renderer-> addToScene(*light);
        engine-> renderer-> addLight(*light);

        // todo: make light shader

        engine->camera->setSpeed(5.0f);

        engine-> window-> mouse-> setLockedPosition(engine-> window-> getWidth() / 2, engine-> window-> getHeight() / 2);
        engine-> window-> mouse-> setLockStatus(true);
//        engine-> window-> mouse-> setCursorType(GLFW_CURSOR_HIDDEN);

        engine-> renderer-> setAmbientStrength(1.0f);
        Log.info("Striker Init function ended");
    }

    void ProcessInput(float dt) override {
        if(engine-> window-> isActive() && State == GAME_ACTIVE) {
            if(engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_G))
                cube-> transform-> setPitch(cube->transform->getPitch()+2*dt);
            if(engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_H))
                cube-> transform-> setYaw(cube->transform->getYaw()+2*dt);
            if(engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_J))
                cube-> transform-> setRoll(cube->transform->getRoll()+2*dt);
            if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_SPACE)){
                if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_W))
                    cube-> transform-> setPosition(cube-> transform-> getPosition() + glm::vec3 {1, 0, 0});

                if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_S))
                    cube-> transform-> setPosition(cube-> transform-> getPosition() + glm::vec3 {-1, 0, 0});

                if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_A))
                    cube-> transform-> setPosition(cube-> transform-> getPosition() + glm::vec3 {0, 0, -1});

                if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_D))
                    cube-> transform-> setPosition(cube-> transform-> getPosition() + glm::vec3 {0, 0, 1});

                if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_LEFT_SHIFT))
                    cube-> transform-> setPosition(cube-> transform-> getPosition() + glm::vec3 {0, 1, 0});

                if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_LEFT_CONTROL))
                    cube-> transform-> setPosition(cube-> transform-> getPosition() + glm::vec3 {0, -1, 0});

            } else {
                if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_W))
                    engine->camera->forward(dt);

                if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_S))
                    engine->camera->backward(dt);

                if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_A))
                    engine->camera->left(dt);

                if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_D))
                    engine->camera->right(dt);

                if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_LEFT_SHIFT))
                    engine->camera->up(dt);

                if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_LEFT_CONTROL))
                    engine->camera->down(dt);
            }

            if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_Q) == GLFW_PRESS)
                Renderer::drawMode(GL_LINE);
            else if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_Q) == GLFW_RELEASE)
                Renderer::drawMode(GL_FILL);

            if(engine-> window-> mouse-> isMoved()) {
                glm::vec3 viewAngles = engine->camera->transform->getEulerAngles();
                glm::vec2 PositionDelta = engine->window->mouse->getLockedPosition();
                PositionDelta -= engine->window->mouse->getPosition();
                engine->camera->transform->setEulerAngles(
                        {0, viewAngles.y + (PositionDelta.x * dt * 0.1), viewAngles.z + (PositionDelta.y * dt * 0.1)});
            }

        } else {
            if (engine->window->mouse->isPressed(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                State = GAME_ACTIVE;
            }
        }
    }
};


int main() {
    Striker MainGame;
    Engine MainEng(&MainGame, new Window {MainGame.title, 1500, 849});
    return MainEng.run();
}