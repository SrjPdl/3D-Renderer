#include "Application.h"
#include "assimp/Importer.hpp"

Application::Application()
	:WINDOW_WIDTH(800),
	 WINDOW_HEIGHT(600),
	 WINDOW_POSITION(glm::vec2(100,50)),
     model(glm::mat4(1.0f)),
     projection(NULL),
     deltaTime(NULL)
{
	setup();
}

Application::~Application()
{
}

void Application::createRawMeshes()
{
    
    float floor[] = {
        //Positions          //Normals          //textureCoordinates
       -100.f, -1.1f, -100.f,     0.f, -1.f, 0.f,     0.f,  0.f,     //0
       -100.f, -1.1f,  100.f,     0.f, -1.f, 0.f,     0.f,  20.f,    //1
        100.f, -1.1f, -100.f,     0.f, -1.f, 0.f,     20.f,  0.f,     //2
        100.f, -1.1f,  100.f,     0.f, -1.f, 0.f,     20.f, 20.f      //3

    };

    uint32_t floorIndex[] = {
        0,1,2,
        1,2,3
    };

    shader.create("vertexShader.glsl", "fragmentShader.glsl");

    
    floorMesh.create(floor, sizeof(floor) / sizeof(float), floorIndex, sizeof(floorIndex) / sizeof(uint32_t), shader.getProgram());
}

void Application::setup()
{    
    window.create("Opengl Project", WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_POSITION);


    /*Initialize GLEW*/
    if (glewInit() != GLEW_OK)
    {
        std::cout << "ERROR::FAILED_TO_INITIALIZE_GLEW" << std::endl;
        glfwTerminate();
    }
    glewExperimental = GL_TRUE;

    //Z-Buffer setup
    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.f);
    glDepthFunc(GL_LESS);

    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE);
    glBlendEquation(GL_ADD);

    //Setting buffer swap interval
    glfwSwapInterval(1);

    createRawMeshes();

    model = glm::translate(model, glm::vec3(0.f, 0.f, -3.f));
    model = glm::scale(model, glm::vec3(0.6, 0.6, 0.6));
    projection = glm::perspective<float>(45.f, window.getViewportAspectRatio(), 1.f, 100.f);
}

void Application::update()
{   
    /*Pre-update settings*/
    float lastFrameTime = 0.f;
    float currentFrameTime = 0.f;

    float currAngle = 0.f;
   
    Camera camera(window.getWindow(),shader.getProgram());
    Light light(shader.getProgram());
    Material dmaterial(shader.getProgram(), 0.6f, 0.3f, 1.f, 64);
    Material smaterial(shader.getProgram(), 0.1f, 0.3f, 1.f, 256);


    Texture dissuseFloorTexture = Texture(shader.getProgram(), "textures/floor.jpg", 0);
    Texture specularFloorTexture = Texture(shader.getProgram(), "textures/floor_specular.jpg", 1);
   

    Model ship,watchTower,test;
    ship.load("models/ship/ship.obj", shader.getProgram());
    watchTower.load("models/watch tower/wooden watch tower2.obj", shader.getProgram());

    /*main loop*/
    while (window.isOpen())
    {
        currentFrameTime = glfwGetTime();
        deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        float xang = 1 * glm::cos(currentFrameTime);
        float zang = 1 * glm::sin(currentFrameTime);
        //std::cout << 1 / deltaTime << std::endl;

        if (glfwGetKey(window.getWindow(), GLFW_KEY_ESCAPE))
        {
            glfwSetWindowShouldClose(window.getWindow(), GL_TRUE);
        }

        //updating projection matrix to account for window resize
        projection = glm::perspective<float>(45.f, window.getViewportAspectRatio(), 1.f, 100.f);


        /* Poll for and process events */
        glfwPollEvents();


        /* Render here */
        glClearColor(0.8f, 1.f, 1.f, 0.8f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

        //updating camera
        camera.update(deltaTime,&projection);
        

        //updating lights
        light.update(glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 0.f, -1.f));

        /*Update and render floor mesh*/
        //model matrix for floor
        glm::mat4 floorModel = glm::mat4(1.f);

        dmaterial.update();
        dissuseFloorTexture.Activate();
        specularFloorTexture.Activate();
        floorMesh.update(&floorModel);
        floorMesh.render();
        
        currAngle = (currAngle > 360) ? 0 : currAngle + 1;

        //model matrix for ship
        glm::mat4 shipModel = glm::mat4(1.f);
        shipModel = glm::scale(shipModel, glm::vec3(0.5f, 0.5f, 0.5f));
        shipModel = glm::translate(shipModel, glm::vec3(0.f, 4.f, 0.f));
        
        ship.render(&shipModel);

        //model matrix for watchTower
        glm::mat4 watchTowerModel = glm::mat4(1.f);
        watchTowerModel = glm::translate(watchTowerModel, glm::vec3(0.f, 6.5f, -8.3f));
        watchTowerModel = glm::scale(watchTowerModel, glm::vec3(0.7f, 1.f, 0.7f));
        watchTower.render(&watchTowerModel);

        /* Swap front and back buffers */
        glfwSwapBuffers(window.getWindow());


    }
}

Application& Application::Get()
{
    static Application instance;
    return instance;
}