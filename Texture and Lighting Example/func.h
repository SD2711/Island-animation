#pragma once

#include <GL/glew.h> 
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

#include "Model.h"

using namespace std;

/// <summary>
/// Загрузка шейдера из файлаю
/// </summary>
/// <param name="filename">Путь к файлу.</param>
/// <returns>Строка с кодом шейдера.</returns>
string LoadShader(const char* filename);

GLFWwindow* InitAll(int w = 640, int h = 480, bool Fullscreen = false);

void EndAll();

//Набор функций для обработки событий

/// <summary>
/// Обработчик изменения размера окна.
/// </summary>
/// <param name="window">Указатель на окно.</param>
/// <param name="width">Новая ширина окна.</param>
/// <param name="height">Новая высота окна.</param>
void window_size_callback(GLFWwindow* window, int width, int height);
/// <summary>
/// Обработчик нажатия клавиш.
/// </summary>
/// <param name="window">Указатель на окно.</param>
/// <param name="key">Код клавиши.</param>
/// <param name="scancode">Код символа.</param>
/// <param name="action">Действие.</param>
/// <param name="mods">Состояние модификаторов нажатия.</param>
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

bool loadOBJ(
    const char* path,
    std::vector < glm::vec3 >& outVertices,
    std::vector < glm::vec2 >& outTextures,
    std::vector < glm::vec3 >& outNormals
);

void genSphere(
    std::vector < GLuint >& outIndexes,
    std::vector < glm::vec3 >& outVertices,
    std::vector < glm::vec2 >& outTextures,
    std::vector < glm::vec3 >& outNormals,
    float radius,
    int sectorCount,
    int stackCount
);

void genCylinder(
    std::vector < GLuint >& outIndexes,
    std::vector < glm::vec3 >& outVertices,
    std::vector < glm::vec2 >& outTextures,
    std::vector < glm::vec3 >& outNormals,
    float baseRadius,
    float topRadius,
    float height,
    int sectorCount,
    int stackCount
);
/// <summary>
/// Вспомогательная функция для вычисления относительных координат секции цилиндра.
/// </summary>
/// <param name="sectorCount">Число граней.</param>
/// <returns></returns>
std::vector < glm::vec3 > getUnitCircleVertices(
    int sectorCount
);

void genTorus(
    std::vector < GLuint >& outIndexes,
    std::vector < glm::vec3 >& outVertices,
    std::vector < glm::vec2 >& outTextures,
    std::vector < glm::vec3 >& outNormals,
    float outerRadius,
    float tubeRadius,
    int sectorCount,
    int stackCount
);
