#include "engine/include/Game.h"
#include "engine/include/Engine.h"

class Striker : public Game {
private:
    Object *map, *cube;
    Object *baseLight;
    Shader *shader;
    bool fillTextures = true;
    bool started = false;

public:
    Striker() : Game() {
        Log::loggingLevel = Log::DEBUG;
        Log::info("Striker game class created");
        title = "Striker v1.0";
    };

    void Init() override {
        State = GAME_MENU;
        shader = new Shader("shaders/vertex/basic.vert", "shaders/fragment/basic.frag");
        map = new Object("res/gameMap.obj");
        map-> setShader(shader);
        engine-> renderer-> addToScene(map);

        cube = new Object("res/cube.obj", new Material(new Texture("res/cube.png"), glm::vec4 {00.1f}));
        cube-> setShader(shader);
        engine-> renderer-> addToScene(cube);

        baseLight = new Object();
        engine-> renderer-> addLight(baseLight);
        // todo: object main variables as position, speed etc
        // todo: split object and light
        // todo: make light shader
        // how much t0d0's by making light... uhh... ok... it will be hard *~*


        engine->camera->speed = 10.0f;

        engine->input->setLockedCursorPosition({engine-> window-> getWidth() / 2, engine-> window-> getHeight() / 2});
        engine->input->setLockStatus(true);
        engine->input->setCursorHidden(true);

        engine-> renderer-> setAmbientStrength(1.0f);
        Log::info("Init ended");
    }

    void ProcessInput(float dt) override {
        if(engine-> window-> isActive() && State == GAME_ACTIVE) {
            if (engine->input->getKeyStatus(GLFW_KEY_W))
                engine->camera->forward(dt);

            if (engine->input->getKeyStatus(GLFW_KEY_S))
                engine->camera->backward(dt);

            if (engine->input->getKeyStatus(GLFW_KEY_A))
                engine->camera->left(dt);

            if (engine->input->getKeyStatus(GLFW_KEY_D))
                engine->camera->right(dt);

            if (engine->input->getKeyStatus(GLFW_KEY_Q))
                engine->camera->roll(1.0f, dt);

            if (engine->input->getKeyStatus(GLFW_KEY_E))
                engine->camera->roll(-1.0f, dt);

            if (engine->input->getKeyStatus(GLFW_KEY_LEFT_SHIFT))
                engine->camera->up(dt);

            if (engine->input->getKeyStatus(GLFW_KEY_LEFT_CONTROL))
                engine->camera->down(dt);

            if (engine->input->getKeyStatus(GLFW_KEY_Q) == GLFW_PRESS) {
                engine-> renderer -> drawMode((fillTextures % 10 < 5) ? GL_FILL : GL_LINE);

            }
            if (engine->input->isCursorMoved()) {
                glm::vec2 viewAngles = engine->camera->getViewAngles();
                glm::vec2 mouseMoved =
                        -(engine->input->getCursorPosition() - engine->input->getLockedCursorPosition()) * 0.2f;
                // -90deg <= vertical <= 90deg or mouse going middle
                if (-1.57f <= viewAngles.y && viewAngles.y <= 1.57f)
                    engine->camera->changeDirection(mouseMoved.x, mouseMoved.y, dt);
                else
                    engine->camera->changeDirection(mouseMoved.x, 1.57 - (viewAngles.y + 0.1 / viewAngles.y), dt);

            }
        } else {
            if (engine->input->getMouseStatus(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
                State = GAME_ACTIVE;
            }
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