#include <GLFW/glfw3.h>
#include <camera.h>
#include <iostream>
#include <map>
#include <model.h>
#include <shader.h>
#include <stb_image.h>

constexpr unsigned int SCR_WIDTH = 800, SCR_HEIGHT = 600;
static bool first_mouse = true;
float lastX = SCR_WIDTH / 2.0f, lastY = SCR_HEIGHT / 2.0f, deltaTime = 0.0f, lastFrame = 0.0f;
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
};

void mouse_callback(GLFWwindow *window, double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);
    if (first_mouse)
    {
        lastX = xpos, lastY = ypos;
        first_mouse = false;
    }
    float xoffset = xpos - lastX;
    float yoffset = -ypos + lastY;
    lastX = xpos;
    lastY = ypos;
    camera.ProcessMouseMovement(xoffset, yoffset);
};

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(static_cast<float>(yoffset));
};

void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
};

const char *path = "/Users/peterhuang98/test_code/C++/learn_opengl/src/4.advanced_opengl/";
string addpath(const string s)
{
    string ret = path;
    ret.append(s);
    return ret;
}

unsigned int loadTexture(char const *path)
{
    unsigned int textureID;
    glGenTextures(1, &textureID);

    int width, height, nrComponents;
    unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, format == GL_RGBA ? GL_CLAMP_TO_EDGE : GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        cout << "Texture failed to load at path: " << path << endl;
        stbi_image_free(data);
    }
    return textureID;
}

// GL_CCW=CCW
// float cubeVertices[] = {
//     // Back face
//     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // Bottom-left
//     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   // top-right
//     0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // bottom-right
//     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   // top-right
//     -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
//     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  // top-left
//     // Front face
//     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
//     0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  // bottom-right
//     0.5f, 0.5f, 0.5f, 1.0f, 1.0f,   // top-right
//     0.5f, 0.5f, 0.5f, 1.0f, 1.0f,   // top-right
//     -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  // top-left
//     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
//     // Left face
//     -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   // top-right
//     -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  // top-left
//     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
//     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
//     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  // bottom-right
//     -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   // top-right
//                                      // Right face
//     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    // top-left
//     0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  // bottom-right
//     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   // top-right
//     0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  // bottom-right
//     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    // top-left
//     0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   // bottom-left
//     // Bottom face
//     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
//     0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  // top-left
//     0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   // bottom-left
//     0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   // bottom-left
//     -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  // bottom-right
//     -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
//     // Top face
//     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
//     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   // bottom-right
//     0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  // top-right
//     0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   // bottom-right
//     -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
//     -0.5f, 0.5f, 0.5f, 0.0f, 0.0f   // bottom-left
// };
// GL_CCW=CCW
float cubeVertices[] = {
    // Back face
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // Bottom-left
    0.5f, -0.5f, -0.5f, 1.0f, 0.0f,  // bottom-right
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   // top-right
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   // top-right
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,  // top-left
    -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, // bottom-left
    // Front face
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,   // top-right
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,  // bottom-right
    0.5f, 0.5f, 0.5f, 1.0f, 1.0f,   // top-right
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, // bottom-left
    -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,  // top-left
    // Left face
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   // top-right
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
    -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  // top-left
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // bottom-left
    -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   // top-right
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  // bottom-right
                                     // Right face
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    // top-left
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,   // top-right
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  // bottom-right
    0.5f, -0.5f, -0.5f, 0.0f, 1.0f,  // bottom-right
    0.5f, -0.5f, 0.5f, 0.0f, 0.0f,   // bottom-left
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,    // top-left
    // Bottom face
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   // bottom-left
    0.5f, -0.5f, -0.5f, 1.0f, 1.0f,  // top-left
    0.5f, -0.5f, 0.5f, 1.0f, 0.0f,   // bottom-left
    -0.5f, -0.5f, -0.5f, 0.0f, 1.0f, // top-right
    -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,  // bottom-right
    // Top face
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f, // top-left
    0.5f, 0.5f, -0.5f, 1.0f, 1.0f,  // top-right
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   // bottom-right
    0.5f, 0.5f, 0.5f, 1.0f, 0.0f,   // bottom-right
    -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,  // bottom-left
    -0.5f, 0.5f, -0.5f, 0.0f, 1.0f  // top-left
};

int main(int argc, char const *argv[])
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    // for GL_CCW=CCW
    glCullFace(GL_BACK);
    // for GL_CCW=CW
    // glCullFace(GL_FRONT);
    Shader shader(addpath("3.2.blending.vs"), addpath("3.2.blending.fs"));

    unsigned int cubeVAO, cubeVBO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);
    glBindVertexArray(cubeVAO);
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

    glBindVertexArray(0);
    unsigned int cubeTexture =
        loadTexture("/Users/peterhuang98/test_code/C++/learn_opengl/resources/textures/marble.jpg");
    shader.use();
    shader.setInt("texture1", 0);
    float distance;
    glm::mat4 projection, view, model;
    while (!glfwWindowShouldClose(window))
    {
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        processInput(window);

        glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        view = camera.GetViewMatrix();
        model = glm::mat4(1.0f);
        shader.setMat4("projection", projection);
        shader.setMat4("view", view);

        glBindVertexArray(cubeVAO);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cubeTexture);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        shader.setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteBuffers(1, &cubeVBO);

    glfwTerminate();
    return 0;
};