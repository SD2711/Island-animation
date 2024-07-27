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
/// �������� ������� �� ������
/// </summary>
/// <param name="filename">���� � �����.</param>
/// <returns>������ � ����� �������.</returns>
string LoadShader(const char* filename);

GLFWwindow* InitAll(int w = 640, int h = 480, bool Fullscreen = false);

void EndAll();

//����� ������� ��� ��������� �������

/// <summary>
/// ���������� ��������� ������� ����.
/// </summary>
/// <param name="window">��������� �� ����.</param>
/// <param name="width">����� ������ ����.</param>
/// <param name="height">����� ������ ����.</param>
void window_size_callback(GLFWwindow* window, int width, int height);
/// <summary>
/// ���������� ������� ������.
/// </summary>
/// <param name="window">��������� �� ����.</param>
/// <param name="key">��� �������.</param>
/// <param name="scancode">��� �������.</param>
/// <param name="action">��������.</param>
/// <param name="mods">��������� ������������� �������.</param>
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
/// ��������������� ������� ��� ���������� ������������� ��������� ������ ��������.
/// </summary>
/// <param name="sectorCount">����� ������.</param>
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
