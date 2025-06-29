#include <iostream>
#include <cmath>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include "imgui/backends/imgui_impl_glfw.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "Shader.hpp"
#include "ObjModel.hpp"
#include "Camera.hpp"
#include <filesystem>
#include "Skybox.hpp"

const int WIDTH = 1280;
const int HEIGHT = 720;

Camera cam;
float lastX = WIDTH / 2.0f, lastY = HEIGHT / 2.0f;
bool firstMouse = true;
bool rightHeld = false;

enum OrbitMode { FREE, ORBIT_SUN, ORBIT_EARTH, ORBIT_MOON, ORBIT_MARS, ORBIT_VENUS };
OrbitMode orbitMode = FREE;

void framebuffer_size_callback(GLFWwindow*, int w, int h) { glViewport(0,0,w,h); }

void mouse_button_callback(GLFWwindow*, int button, int action, int){
    if(button == GLFW_MOUSE_BUTTON_RIGHT){
        if(action == GLFW_PRESS){ rightHeld=true; firstMouse=true; }
        if(action == GLFW_RELEASE) rightHeld=false;
    }
}

void cursor_callback(GLFWwindow*, double xpos, double ypos){
    if(!rightHeld) return;
    if(firstMouse){ lastX = (float)xpos; lastY = (float) ypos; firstMouse=false; }
    float dx = (float)(xpos-lastX);
    float dy = (float)(lastY-ypos);
    lastX = (float)xpos; lastY = (float) ypos;
    cam.ProcessMouseMovement(dx,dy);
}

void scroll_callback(GLFWwindow*, double, double y){ cam.ProcessMouseScroll((float)y); }

void processInput(GLFWwindow* w,float dt){
    if(glfwGetKey(w,GLFW_KEY_W)==GLFW_PRESS) cam.ProcessKeyboard(FORWARD ,dt);
    if(glfwGetKey(w,GLFW_KEY_S)==GLFW_PRESS) cam.ProcessKeyboard(BACKWARD,dt);
    if(glfwGetKey(w,GLFW_KEY_A)==GLFW_PRESS) cam.ProcessKeyboard(LEFT    ,dt);
    if(glfwGetKey(w,GLFW_KEY_D)==GLFW_PRESS) cam.ProcessKeyboard(RIGHT   ,dt);
}

int main(){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* win = glfwCreateWindow(WIDTH,HEIGHT,"Systeme Solaire",nullptr,nullptr);
    if(!win){ glfwTerminate(); return -1; }
    glfwMakeContextCurrent(win);
    glfwSetFramebufferSizeCallback(win,framebuffer_size_callback);
    glfwSetCursorPosCallback(win,cursor_callback);
    glfwSetMouseButtonCallback(win,mouse_button_callback);
    glfwSetScrollCallback(win,scroll_callback);
    glfwSetInputMode(win,GLFW_CURSOR,GLFW_CURSOR_NORMAL);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) return -1;
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_FRAMEBUFFER_SRGB);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(win,true);
    ImGui_ImplOpenGL3_Init("#version 330");

    Shader shader("assets/shaders/phong.vert","assets/shaders/phong.frag");
    shader.use();
    shader.setInt("uTexture", 0);

    ObjModel sun("assets/models/sphere.obj");
    ObjModel earth("assets/models/sphere.obj");
    ObjModel moon("assets/models/sphere.obj");
    ObjModel mars ("assets/models/sphere.obj");
    ObjModel venus("assets/models/sphere.obj");
    ObjModel earthNight("assets/models/sphere.obj");

    bool nightMode = false;

    sun.loadTexture("assets/textures/sun.jpg");
    earth.loadTexture("assets/textures/earth.jpg");
    moon.loadTexture("assets/textures/moon.jpg");
    mars .loadTexture("assets/textures/mars.jpg");
    venus.loadTexture("assets/textures/venus.jpg");
    earthNight.loadTexture("assets/textures/earth_night.jpg");

    

    Skybox sky({
        "assets/skybox/px.jpg",
        "assets/skybox/nx.jpg",
        "assets/skybox/py.jpg",
        "assets/skybox/ny.jpg",
        "assets/skybox/pz.jpg",
        "assets/skybox/nz.jpg"
    });

    float lastFrame=0;
    while(!glfwWindowShouldClose(win)){
        float cur=(float)glfwGetTime();
        float dt = cur-lastFrame; lastFrame=cur;

        glfwPollEvents();
        processInput(win,dt);

        float t = cur;
        float earthR = 8.0f;
        float moonR  = 2.0f;
        float venusR = 5.5f;
        float marsR  = 11.5f;
        glm::vec3 sunPos   = glm::vec3(0);
        glm::vec3 earthPos = glm::vec3(cos(t*0.5f)*earthR,0,sin(t*0.5f)*earthR);
        glm::vec3 moonPos  = earthPos + glm::vec3(cos(t*1.5f)*moonR,0,sin(t*1.5f)*moonR);
        glm::vec3 venusPos = glm::vec3(cos(t*0.7f)*venusR,0,sin(t*0.7f)*venusR);
        glm::vec3 marsPos  = glm::vec3(cos(t*0.4f)*marsR ,0,sin(t*0.4f)*marsR );

        if (orbitMode != FREE) {
            switch (orbitMode) {
                case ORBIT_SUN  : cam.Target = sunPos;   break;
                case ORBIT_EARTH: cam.Target = earthPos; break;
                case ORBIT_MOON : cam.Target = moonPos;  break;
                case ORBIT_MARS : cam.Target = marsPos;  break;
                case ORBIT_VENUS: cam.Target = venusPos; break;
                default: break;
            }
            cam.ProcessOrbit(dt*50.f,0);
        }

        glClearColor(0.02f,0.02f,0.05f,1);
        glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

        glm::mat4 view = cam.GetViewMatrix();
        glm::mat4 proj = glm::perspective(glm::radians(45.0f),
                                          WIDTH/(float)HEIGHT,0.1f,200.f);
        sky.draw(view, proj);

        shader.use();
        shader.setMat4("uView",glm::value_ptr(view));
        shader.setMat4("uProj",glm::value_ptr(proj));
        shader.setVec3("uViewPos",cam.Position.x,cam.Position.y,cam.Position.z);
        shader.setVec3("lightPos",0,0,0);
        shader.setVec3("lightColor",1,1,1);

        shader.setVec3("uKa",1.0f,0.85f,0.1f);
        shader.setVec3("uKd",1.0f,0.85f,0.1f);
        shader.setVec3("uKs",0.0f,0.0f,0.0f);
        shader.setFloat("uShin",4.0f);
        glm::mat4 sunM = glm::translate(glm::mat4(1),sunPos)*glm::scale(glm::mat4(1),glm::vec3(2));
        shader.setMat4("uModel",glm::value_ptr(sunM));
        sun.draw();

        ObjModel& earthToDraw = nightMode ? earthNight : earth;

        shader.setVec3("uKa",0.0f,0.15f,0.4f);
        shader.setVec3("uKd",0.0f,0.25f,0.8f);
        shader.setVec3("uKs",0.05f,0.05f,0.05f);
        shader.setFloat("uShin",8.0f);
        glm::mat4 earthM = glm::translate(glm::mat4(1), earthPos) *
                        glm::rotate(glm::mat4(1), t*4.0f, glm::vec3(0,1,0));
        shader.setMat4("uModel", glm::value_ptr(earthM));
        earthToDraw.draw();

        shader.setVec3("uKa",0.2f,0.2f,0.2f);
        shader.setVec3("uKd",0.6f,0.6f,0.6f);
        shader.setVec3("uKs",0.0f,0.0f,0.0f);
        shader.setFloat("uShin",4.0f);
        glm::mat4 moonM = glm::translate(glm::mat4(1),moonPos)*glm::scale(glm::mat4(1),glm::vec3(0.27f));
        shader.setMat4("uModel",glm::value_ptr(moonM));
        moon.draw();

        
        shader.setVec3("uKa", 0.9f, 0.7f, 0.5f);
        shader.setVec3("uKd", 1.0f, 0.8f, 0.6f);
        shader.setVec3("uKs", 0.1f, 0.1f, 0.1f);
        shader.setFloat("uShin", 4.0f);
        glm::mat4 venusM = glm::translate(glm::mat4(1), venusPos);
        shader.setMat4("uModel", glm::value_ptr(venusM));
        venus.draw();

        shader.setVec3("uKa", 0.4f, 0.15f, 0.05f);
        shader.setVec3("uKd", 0.8f, 0.3f, 0.1f);
        shader.setVec3("uKs", 0.05f, 0.05f, 0.05f);
        shader.setFloat("uShin", 6.0f);
        glm::mat4 marsM = glm::translate(glm::mat4(1), marsPos);
        shader.setMat4("uModel", glm::value_ptr(marsM));
        mars.draw();

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(WIDTH - 310, 10), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(300, 200), ImGuiCond_Always);
        ImGui::Begin("Orbitation",nullptr,ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse);

        if(ImGui::Button("Orbiter Autour Du Soleil",ImVec2(-1,0))) orbitMode = ORBIT_SUN;
        if(ImGui::Button("Orbiter Autour De la Terre",ImVec2(-1,0))) orbitMode = ORBIT_EARTH;
        if(ImGui::Button("Orbiter Autour De la Lune",ImVec2(-1,0)))  orbitMode = ORBIT_MOON;
        if(ImGui::Button("Orbiter Autour de Venus",ImVec2(-1,0)))    orbitMode = ORBIT_VENUS;
        if(ImGui::Button("Orbiter Autour de Mars", ImVec2(-1,0)))    orbitMode = ORBIT_MARS;
        if(ImGui::Button("Mode Libre",ImVec2(-1,0)))                  orbitMode = FREE;

        ImGui::End();

        ImGui::SetNextWindowPos(ImVec2(10,10), ImGuiCond_Always);
        ImGui::SetNextWindowSize(ImVec2(120,85), ImGuiCond_Always);
        ImGui::Begin("Mode Jour/Nuit", nullptr, ImGuiWindowFlags_NoResize|ImGuiWindowFlags_NoCollapse);

        if(ImGui::Button("Mode Jour", ImVec2(-1,0)))  nightMode = false;
        if(ImGui::Button("Mode Nuit", ImVec2(-1,0)))  nightMode = true;

        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(win);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
    return 0;

    
}
