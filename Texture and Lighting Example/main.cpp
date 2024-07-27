#include <vector>
#include <algorithm>

#include "Model.h"
#include "func.h"

#define PI 3.14159265358979323846f  


const glm::mat4 WorldMatrix = glm::mat4(1.0f);


int WinWidth;
int WinHeight;


bool isRainEnabled = false;
bool RotationMode;


glm::vec3 CamPosition;
glm::vec3 CamTarget = glm::vec3(0);
bool CamMoved = false;
GLfloat CamSpeed = 0.07;


struct Rain {
    glm::vec3 position;
    glm::vec3 move_speed;
    // Constructor
    Rain(const glm::vec3& pos) : position(pos) {}
};

bool needToGenerateRainflake() {
    return ((0 + rand() % 100) <= 50);
}

int main() {
    srand(time(nullptr));

    GLFWwindow* window = InitAll(1024, 768, false);
    if (window == nullptr)
    {
        EndAll();
        return -1;
    }

    //Время запуска программы, нужно для анимации.
    double start_time = glfwGetTime();

    //Массивы для хранения атрибутов вершин
    vector<glm::vec3> temp_vertices, temp_normals, temp_colors;
    vector<glm::vec2> temp_textures;
    vector<GLuint> temp_indices;
    
    //Тигр
    Model modelTiger(window, 2);
    loadOBJ("Tiger.obj", temp_vertices, temp_textures, temp_normals);
    modelTiger.load_coords(temp_vertices.data(), temp_vertices.size());
    modelTiger.load_normals(temp_normals.data(), temp_normals.size());
    modelTiger.load_texcoord(temp_textures.data(), temp_textures.size());
    modelTiger.load_shaders("texvs.glsl", "texfs.glsl");
    modelTiger.setMaterial(glm::vec3(0), glm::vec3(0), glm::vec3(0), 256);
    modelTiger.load_texture("tiger.jpg", "");


    //Пальма
    Model modelPalm(window, 2);
    loadOBJ("PalmTree.obj", temp_vertices, temp_textures, temp_normals);
    modelPalm.load_coords(temp_vertices.data(), temp_vertices.size());
    modelPalm.load_normals(temp_normals.data(), temp_normals.size());
    modelPalm.load_texcoord(temp_textures.data(), temp_textures.size());
    modelPalm.load_shaders("texvs.glsl", "texfs.glsl");
    modelPalm.setMaterial(glm::vec3(0), glm::vec3(0), glm::vec3(0), 256);
    modelPalm.load_texture("PalmTree.jpg", "");

    //Дерево
    Model modelTree(window, 2);
    loadOBJ("tree.obj", temp_vertices, temp_textures, temp_normals);
    modelTree.load_coords(temp_vertices.data(), temp_vertices.size());
    modelTree.load_normals(temp_normals.data(), temp_normals.size());
    modelTree.load_texcoord(temp_textures.data(), temp_textures.size());
    modelTree.load_shaders("texvs.glsl", "texfs.glsl");
    modelTree.setMaterial(glm::vec3(0), glm::vec3(0), glm::vec3(0), 256);
    modelTree.load_texture("tree.jpg", "");

    //Солнце
    Model modelSun(window, 2);
    loadOBJ("Sun.obj", temp_vertices, temp_textures, temp_normals);
    modelSun.load_coords(temp_vertices.data(), temp_vertices.size());
    modelSun.load_normals(temp_normals.data(), temp_normals.size());
    modelSun.load_texcoord(temp_textures.data(), temp_textures.size());
    modelSun.load_shaders("texvs.glsl", "texfs.glsl");
    modelSun.setMaterial(glm::vec3(0), glm::vec3(0), glm::vec3(0), 256);
    modelSun.load_texture("Sun.jpg", "");

    //Лев
    Model modelLion(window, 2);
    loadOBJ("Lion.obj", temp_vertices, temp_textures, temp_normals);
    modelLion.load_coords(temp_vertices.data(), temp_vertices.size());
    modelLion.load_normals(temp_normals.data(), temp_normals.size());
    modelLion.load_texcoord(temp_textures.data(), temp_textures.size());
    modelLion.load_shaders("texvs.glsl", "texfs.glsl");
    modelLion.setMaterial(glm::vec3(0), glm::vec3(0), glm::vec3(0), 256);
    modelLion.load_texture("bulgaria-flag.png", "");

    //Monkey
    Model modelMonkey(window, 2);
    loadOBJ("monkey.obj", temp_vertices, temp_textures, temp_normals);
    modelMonkey.load_coords(temp_vertices.data(), temp_vertices.size());
    modelMonkey.load_normals(temp_normals.data(), temp_normals.size());
    modelMonkey.load_texcoord(temp_textures.data(), temp_textures.size());
    modelMonkey.load_shaders("texvs.glsl", "texfs.glsl");
    modelMonkey.setMaterial(glm::vec3(0), glm::vec3(0), glm::vec3(0), 256);
    modelMonkey.load_texture("monkey.jpg", "");


    //Песок
    Model modelSand(window, 2);
    genCylinder(temp_indices, temp_vertices, temp_textures, temp_normals, 3, 10, 5, 30, 50);
    modelSand.load_coords(temp_vertices.data(), temp_vertices.size());
    modelSand.load_normals(temp_normals.data(), temp_normals.size());
    modelSand.load_texcoord(temp_textures.data(), temp_textures.size());
    modelSand.load_indices(temp_indices.data(), temp_indices.size());
    modelSand.setMaterial(glm::vec3(0), glm::vec3(0), glm::vec3(0), 128);
    modelSand.load_shaders("texvs.glsl", "texfs.glsl");
    modelSand.load_texture("sand.jpg", "");

    //Океан
    Model modelOcean(window, 2);
    genCylinder(temp_indices, temp_vertices, temp_textures, temp_normals, 3, 10, 4.6, 30, 70);
    modelOcean.load_coords(temp_vertices.data(), temp_vertices.size());
    modelOcean.load_normals(temp_normals.data(), temp_normals.size());
    modelOcean.load_texcoord(temp_textures.data(), temp_textures.size());
    modelOcean.load_indices(temp_indices.data(), temp_indices.size());
    modelOcean.setMaterial(glm::vec3(0), glm::vec3(0), glm::vec3(0), 128);
    modelOcean.load_shaders("texvs.glsl", "texfs.glsl");
    modelOcean.load_texture("ocean.jpg", "");

    //дождь
    Model modelRain(window, 2);
    genSphere(temp_indices, temp_vertices, temp_textures, temp_normals, 0.02f, 5, 10);
    modelRain.load_coords(temp_vertices.data(), temp_vertices.size());
    modelRain.load_indices(temp_indices.data(), temp_indices.size());
    modelRain.load_normals(temp_normals.data(), temp_normals.size());
    modelRain.setMaterial(glm::vec3(0), glm::vec3(0), glm::vec3(0), 128);
    modelRain.load_shaders("texvs.glsl", "texfs.glsl");
    modelRain.load_texture("image.jpg", "");


    //Параметры освещения сцены
    LightsInfo Lights;

    Lights.numPLights = 2;
    Lights.numSLights = 1;

    glm::vec3 lightPos = {1, 1, 0},
        la = {0.2f, 0.2f, 0.2f},
        ld = {0.5f, 0.5f, 0.5f},
        ls = {1, 1, 1};

    DirLight lSource;
    lSource.ambient = la;
    lSource.diffuse = ld;
    lSource.specular = ls;
    lSource.direction = glm::vec3(0, -1, 0);

    Lights.dirLight = lSource;

    PointLight P;
    P.ambient = glm::vec3(0.0f, 0.4f, 0.0f);
    P.diffuse = glm::vec3(0.0f, 0.8f, 0.0f);
    P.specular = glm::vec3(1, 1, 1);
    P.position = lightPos;
    P.constant = 1;
    P.linear = 0.09;
    P.quadratic = 0.032;
    Lights.pointLights.push_back(P);

    P.ambient = glm::vec3(0.4f, 0.0f, 0.4f);
    P.diffuse = glm::vec3(0.8f, 0.0f, 0.8f);
    P.specular = glm::vec3(1, 1, 1);
    P.position = glm::vec3(-1, 1, 0);
    P.constant = 1;
    P.linear = 0.09;
    P.quadratic = 0.032;
    Lights.pointLights.push_back(P);


    SpotLight SP;
    SP.ambient = glm::vec3(0.1f, 0.1f, 0.1f);
    SP.diffuse = glm::vec3(1, 1, 1);
    SP.specular = glm::vec3(1, 1, 1);
    SP.position = glm::vec3(-1, -1, -1);
    SP.direction = glm::vec3(1, 1, 1);
    SP.cutOff = glm::cos(glm::radians(12.5f));
    SP.outerCutOff = glm::cos(glm::radians(15.0f));

    SP.constant = 1;
    SP.linear = 0.009;
    SP.quadratic = 0.0032;
    Lights.spotLights.push_back(SP);

  
    //Теперь создание матриц
    glm::mat4 MMatr = WorldMatrix,
        VMatr = WorldMatrix,
        PMatr = WorldMatrix;

    //Матрицу проецирования можно задать сразу же, менять её не надо будет
    PMatr = glm::perspective(
        glm::radians(67.0f),            // Угол обзора
        (float)WinWidth / WinHeight,    // Соотношение сторон
        0.01f,                          // Ближняя плоскость отсечения
        10000.0f                        // Дальняя плоскость отсечения
    );

    //Теперь начальные значения матрицы вида
    CamPosition = {0, 0, -2};
    VMatr = glm::lookAt(CamPosition, CamTarget, glm::vec3(0, 1, 0));

    //Цвет фона
    glClearColor(204.0f/255.0f, 245.0f/255.0f, 255.0f/255.0f, 1.0f);

    float rotation = 0;

    //И так как речь о 3d важно не забыть про буфер глубины (попробуйте убрать его)
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);


    std::vector<Rain> rainflakes;
    rainflakes.reserve(2048);


    float earthHeight = -6.5, oceanHeight = -6.0;
    int rainRadius = 20;

    bool isRainClearEnabled = true;


    while (!glfwWindowShouldClose(window)) {

        double elapsed = glfwGetTime() - start_time;
        glViewport(0, 0, WinWidth, WinHeight);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Если камеру двигали - надо пересчитать матрицу вида
        if (CamMoved)
        {
            VMatr = WorldMatrix;
            VMatr = glm::lookAt(CamPosition, CamTarget, glm::vec3(0, 1, 0));
            CamMoved = false;
        }

        rotation = RotationMode ? (float)elapsed : -(float)elapsed;

        // Ocean
        MMatr = WorldMatrix;
        MMatr = glm::rotate(MMatr, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
        MMatr = glm::translate(MMatr, glm::vec3(-10, -7, oceanHeight));
        modelOcean.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);

        // Песок
        MMatr = WorldMatrix;
        MMatr = glm::rotate(MMatr, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
        MMatr = glm::translate(MMatr, glm::vec3(0, -5, earthHeight));
        modelSand.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);


        // Тигр
        MMatr = WorldMatrix;
        MMatr = glm::translate(MMatr, glm::vec3(-0.6, -1.5f, 0.0));
        MMatr = glm::rotate(MMatr, PI, glm::vec3(0.0, 0.0, 1.0));
        MMatr = glm::rotate(MMatr, PI / 2, glm::vec3(1.0, 0.0, 0.0));
        MMatr = glm::scale(MMatr, glm::vec3(0.06f, 0.06f, 0.06f));
        modelTiger.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);


        // Пальма
        MMatr = WorldMatrix;
        MMatr = glm::translate(MMatr, glm::vec3(0.0, -1.5, 0.75));
        MMatr = glm::rotate(MMatr, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
        MMatr = glm::scale(MMatr, glm::vec3(0.004, 0.004, 0.004));
        modelPalm.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);

        // Дерево
        MMatr = WorldMatrix;
        MMatr = glm::translate(MMatr, glm::vec3(0.5, -1.6, 0.75));
        MMatr = glm::rotate(MMatr, glm::radians(-90.0f), glm::vec3(1.0, 0.0, 0.0));
        MMatr = glm::scale(MMatr, glm::vec3(0.05, 0.05, 0.05));
        modelTree.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);

        // Лев
        MMatr = WorldMatrix;
        MMatr = glm::translate(MMatr, glm::vec3(1.7, -0.9f, 0.0));
        MMatr = glm::rotate(MMatr, PI, glm::vec3(0.0, 0.0, 1.0));
        MMatr = glm::rotate(MMatr, PI / 2, glm::vec3(1.0, 0.0, 0.0));
        MMatr = glm::scale(MMatr, glm::vec3(0.005f, 0.005f, 0.005f));
        modelLion.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);

        // Monkey
        MMatr = WorldMatrix;
        MMatr = glm::translate(MMatr, glm::vec3(0.2, -1.0f, 0.75));
        MMatr = glm::rotate(MMatr, PI, glm::vec3(0.0, 0.0, 1.0));
        MMatr = glm::rotate(MMatr, PI / 2, glm::vec3(1.0, 0.0, 0.0));
        MMatr = glm::scale(MMatr, glm::vec3(0.005f, 0.005f, 0.005f));
        modelMonkey.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);
        
        // Солнце
        MMatr = WorldMatrix;
        MMatr = glm::translate(MMatr, glm::vec3(3.7, 0.5f, 0.0));
        MMatr = glm::rotate(MMatr, PI, glm::vec3(0.0, 0.0, 1.0));
        MMatr = glm::rotate(MMatr, PI / 2, glm::vec3(1.0, 0.0, 0.0));
        MMatr = glm::rotate(MMatr, PI - rotation, glm::vec3(1.0, 1.0, 1.0));
        MMatr = glm::translate(MMatr, glm::vec3(1.5, 4.5, 2.5)); //Движение по кругу
        MMatr = glm::scale(MMatr, glm::vec3(0.001f, 0.001f, 0.001f));
        modelSun.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);

        if (needToGenerateRainflake && isRainEnabled) {
            Rain newRainflake = Rain(glm::vec3(((0 + rand() % rainRadius * 2) - rainRadius) / 10.0f, 2.25f, ((0 + rand() % rainRadius * 2) - rainRadius) / 10.0f));
            newRainflake.move_speed = glm::vec3(0.0f, (1 + rand() % 10) / 1000.0f, 0.0f);
            rainflakes.push_back(newRainflake);

            isRainClearEnabled = true;
        }

        if (isRainClearEnabled) {
            for (auto& rainflake : rainflakes) {
                rainflake.position -= rainflake.move_speed;

                MMatr = WorldMatrix;
                MMatr = glm::translate(MMatr, rainflake.position);
                modelRain.render(MMatr, VMatr, PMatr, Lights, GL_TRIANGLES);
            }

            rainflakes.erase(remove_if(begin(rainflakes), end(rainflakes),
                [&](const Rain& snowflake) {

                    //cout << "Removed snowflake (total: " << snowflakes.size() + ")" << endl;
                    return snowflake.position.y < -1.2f;
                }), end(rainflakes));

            if (rainflakes.size() == 0) {
                isRainClearEnabled = false;
            }
        }
        

        
        glfwPollEvents();
        glfwSwapBuffers(window);
        if (GLFW_PRESS == glfwGetKey(window, GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window, 1);
        }
    }

    return 0;
}