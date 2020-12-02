#include "engine/include/Game.h"
#include "engine/include/Engine.h"

class Striker : public Game {
private:
    Object *map;
    Object *cube;
    Shader *shader;
    int8_t fillTextures = 0;
    bool started = false;

public:
    Striker() : Game() {
        Console::message("Striker game class created");
        title = "Striker v1.0";
    };

    void Init() override {
        shader = new Shader("shaders/vertex/basic.vert", "shaders/fragment/basic.frag");

        map = new Object("res/gameMap.obj");
        map-> setShader(shader);
        engine-> renderer-> addToScene(map);

        cube = new Object("res/cube.obj", new Material(new Texture("res/cube.png"), glm::vec4 {00.1f}));
        cube-> setShader(shader);
        engine-> renderer-> addToScene(cube);

        engine->camera->speed = 20.0f;

        engine->input->setLockedCursorPosition({engine-> window-> getWidth() / 2, engine-> window-> getHeight() / 2});
        engine->input->setLockStatus(true);
        engine->input->setCursorHidden(true);
        Console::message("Init ended");
    }

    void ProcessInput(float dt) override {
        if(engine-> window-> isActive() && started) {
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

            if (engine->input->getKeyStatus(GLFW_KEY_Q) == GLFW_PRESS){
                    glPolygonMode(GL_FRONT_AND_BACK, (fillTextures) ? GL_FILL : GL_LINE);
                    fillTextures = !fillTextures;
            }
            if(engine-> input-> isCursorMoved()){
                glm::vec2 viewAngles = engine-> camera-> getViewAngles();
                glm::vec2 mouseMoved = -(engine->input->getCursorPosition() - engine->input->getLockedCursorPosition()) * 0.2f;
                // -90deg <= vertical <= 90deg or mouse going middle
                if (-1.57f <= viewAngles.y && viewAngles.y <= 1.57f)
                    engine->camera->changeDirection(mouseMoved.x, mouseMoved.y, dt);
                else
                    engine->camera->changeDirection(mouseMoved.x, -0.1f/viewAngles.y, dt);

            }
        } else {
            if (engine->input->getKeyStatus(GLFW_KEY_ENTER))
                started = true;
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