// #include <cmath>
#include <string>

#include "engine/source/core/Console.h"
#include "engine/source/core/Game.h"
#include "engine/source/core/Engine.h"
#include "engine/source/shaders/standardShader.h"
#include "engine/source/core/Time.h"

class Striker : public Game {
private:
    Object *light;

public:
    Striker() : Game(), light() {
        Log->info("Striker game class created");
        title = "Striker - First Person Shooter";
    };

    void Init() override {
        Window::setClearColor(0.1f, 0.7f, 0.9f);
        State = GAME_MENU;
        auto basicShader = new Shader("runtime/standard/basic.vert", "runtime/standard/basic.frag");
        auto lightShader = new Shader("runtime/light/basic.vert", "runtime/light/basic.frag");

        auto t_wood = new Texture("res/wood.png");
        auto m_wood = new Material(t_wood, glm::vec4 {1.0f});
        auto t_uvm = new Texture("res/uv_map.jpg");
        auto m_uvm = new Material(t_uvm, glm::vec4 {1.0f});
//        int dist = 10;
//        for (int i = -dist; i <= dist; ++i) {
//            for (int j = -dist; j <= dist; ++j) {
//                auto map = new Object((std::string("map") + std::to_string(i)+"_"+std::to_string(j)).c_str());
//                map->transform->setPosition({i, -1, j});
//                map->loadObjFromFile("res/square.obj");
//                map->setMaterial(m_wood);
//                map-> setShader(basicShader);
//                engine-> renderer-> addToScene(*map);
//            }
//        }

        auto map = new Object("map");
        map-> setShader(basicShader);
        map-> setMaterial(m_uvm);
        map-> loadObjFromFile("res/gameMap.obj");
        map-> transform-> setPosition({0, 0, 1});
        engine-> renderer-> addToScene(*map);

        auto cube = new Object("cube");
        cube-> setShader(basicShader);
        cube->setMaterial(m_wood);
        cube->loadObjFromFile("res/cube.obj");
        cube-> transform-> setPosition({1.0f, 1.0f, 9.0f});
        engine-> renderer-> addToScene(*cube);

        light = new Object("light");
        light-> setMaterial(new Material(glm::vec4 {1.0f}));
        light-> setShader(lightShader);
        light->loadObjFromFile("res/cube.obj");
        light-> transform-> setScale(0.1f);
        light-> transform-> setPosition({2.0f, 2.0f, 0});
        engine-> renderer-> addToScene(*light);
        engine-> renderer-> addLight(*light);

        engine->camera->setSpeed(5.0f);

        engine-> window-> mouse-> setLockedPosition(double(engine-> window-> getWidth()) / 2, double(engine-> window-> getHeight()) / 2);
        engine-> window-> mouse-> setLockStatus(true);
        engine-> window-> mouse-> setCursorType(GLFW_CURSOR_HIDDEN);

        engine-> renderer-> setAmbientStrength(0.1f);
        Log->info("Striker Init function ended");
    }

    void ProcessInput(float dt) override {
        if(engine-> window-> isActive() && State == GAME_ACTIVE) {

            if(engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_P))
                engine-> camera-> type = Camera::Perspective;
            else if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_O))
                engine-> camera-> type = Camera::Orthographic;

            if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_SPACE)){
                if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_W))
                    light-> transform-> setPosition(light-> transform-> getPosition() + glm::vec3 {1, 0, 0});

                if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_S))
                    light-> transform-> setPosition(light-> transform-> getPosition() + glm::vec3 {-1, 0, 0});

                if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_A))
                    light-> transform-> setPosition(light-> transform-> getPosition() + glm::vec3 {0, 0, -1});

                if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_D))
                    light-> transform-> setPosition(light-> transform-> getPosition() + glm::vec3 {0, 0, 1});

                if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_LEFT_SHIFT))
                    light-> transform-> setPosition(light-> transform-> getPosition() + glm::vec3 {0, 1, 0});

                if (engine-> window-> keyboard-> getKeyStatus(GLFW_KEY_LEFT_CONTROL))
                    light-> transform-> setPosition(light-> transform-> getPosition() + glm::vec3 {0, -1, 0});

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
    Log->loggingLevel = Logger::DEBUG;
    Striker MainGame;
    Engine MainEng(&MainGame, new Window {MainGame.title, 1600, 900});
    return MainEng.run();
}




//    void Update(float dt) override {
//
//        light-> transform-> setPitch((light->transform->getPitch() * 0.1f + 1) * std::cos(dt));
//        light-> transform-> setYaw((light->transform->getYaw() * 0.1f + 1) * std::sin(dt) );
//        glm::vec3 pos = light-> transform-> getPosition();
//        pos += glm::vec3{ sin(dt), sin(dt)*cos(dt), cos(dt)} / glm::vec3{10};
//        light-> transform-> setPosition(pos);
//    }