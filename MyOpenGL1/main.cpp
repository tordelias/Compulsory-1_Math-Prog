#include <iostream>
#include <fstream>
#include <iomanip>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <utility>
#include <vector>
#include <string>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


//vertex shader source 
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n" // x, y, y_next
"out vec3 dataOut;\n" // Pass y and y_next
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
"   dataOut = aPos;\n" // Pass y and y_next
"}\0";





// fragmenet shader source 
const char* fragmentShaderSource = "#version 330 core\n"
"in vec3 dataOut;\n" // y, y_next
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   if (dataOut.z > dataOut.y)\n" // Compare y_next with y
"       FragColor = vec4(0.0, 1.0, 0.0, 1.0); // Green\n"
"   else\n"
"       FragColor = vec4(1.0, 0.0, 0.0, 1.0); // Red\n"
"}\n\0";





void Outputfile(double x, double y, std:: string n)
{
    const char* fileName = "Output1Variable.txt";
    std::ofstream Outputfile(fileName, std::ios::app);
    if (Outputfile.is_open())
    {
        Outputfile << std::fixed << std::setprecision(3);
        Outputfile << x << ", " << y << ", 0.0, " << "color -->" << n << std::endl;
    }
    //else
    //{
    //    std::cout << "Unable to open file" << std::endl;
    //}
    Outputfile.close();
}

void Outputfile2(double x, double y, double z)
{
    const char* fileName = "Output2Variables.txt";
    std::ofstream Outputfile(fileName, std::ios::app);
    if (Outputfile.is_open())
    {
        Outputfile << std::fixed << std::setprecision(3);
        Outputfile << x << ", " << y << ", " << z << std::endl;
    }
    //else
    //{
    //    std::cout << "Unable to open file" << std::endl;
    //}
    Outputfile.close();
}
void Outputfile3(double x, double y, double z)
{
    const char* fileName = "OutputSpiral.txt";
    std::ofstream Outputfile(fileName, std::ios::app);
    if (Outputfile.is_open())
    {
        Outputfile << std::fixed << std::setprecision(3);
        Outputfile << x << ", " << y << ", " << z << std::endl;
    }
    //else
    //{
    //    std::cout << "Unable to open file" << std::endl;
    //}
    Outputfile.close();
}
void Readfile(const char* filename, GLfloat* vertices, size_t maxVertices) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }

    std::string line;
    // Skip the first line (header)
    std::getline(file, line);

    size_t i = 0;
    GLfloat x, y, z;
    char comma;

    if (file.is_open())
    {
        while (i < maxVertices * 3 && file >> x >> comma >> y >> comma >> z)
        {
            vertices[i++] = x;
            vertices[i++] = y;
            vertices[i++] = z;
        }
    }
    else
    {
        std::cout << "Unable to open file" << std::endl;
    }
    file.close();
}







//UpperBound
float upperBound = 10000.f;
//LowerBound
float lowerBound = -10000.f;

// Function f(x)
double f(double x)
{
    return x * x * x + 2 * x * x + 3;
}

// Derivative of f(x)
double df(double x)
{
    return 3 * x * x + 4 * x;
}

// The Newton-Raphson method for finding the root of f(x)
std::pair<double, int> newton(double x0) {
    int iter{ 0 };
    auto fx = f(x0);
    double x = x0;

    std::cout << "Newtons formula" << std::endl;

    // Iterate until the absolute value of f(x) is less than the desired tolerance
    while (std::abs(fx) > 0.01 && x >= lowerBound && x <= upperBound) {
        x -= fx / df(x); // Update x using the Newton formula
        fx = f(x); // Recalculate f(x) after updating x
        iter++;
        std::cout << "X position: " << x << "       Y position: " << fx << std::endl;

        //Outputfile(x, fx);
    }

    // Return a pair consisting of the root approximation and the number of iterations
    return std::pair<double, int>(x, iter);
}




int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    std::ofstream clearFile("Output1Variable.txt");
    clearFile.close();

    std::ofstream clearFile2("Output2Variables.txt");
    clearFile2.close();


    //math


    auto par = newton(0.785);
    std::cout << "Root: " << par.first << ", Iterations: " << par.second << std::endl;




    int const numVertices = 10000;
    GLfloat vertices[numVertices * 3]; // Increased size to hold x, y, z for each vertex
    float h = 0.05f;
    float x0, x1, y0, y1;
    x0 = 0.0f, y0 = 0.0f;


    const char* fileName = "Output1Variable.txt";
    std::ofstream GiveNumVertecies(fileName, std::ios::app);
    if (GiveNumVertecies.is_open())
    {
       GiveNumVertecies << "Number of Vertecies if upper/lowerbound not found: " << numVertices << std::endl;
        GiveNumVertecies.close();
    }


    //posetive
    for (int i = 0; i < numVertices; ++i) {
        std::string color; 
        x1 = i * h - 32;
        y1 = std::tan(x1 * x1); // Your function here

        if(y1 > upperBound || y1 < lowerBound || x1 > upperBound || x1 < lowerBound)
			break;

        float y_next = 0.0f;
        if (i < numVertices - 1) {
            float x_next = (i + 1) * h - 32;
            y_next = std::tan(x_next*x_next); // Your function here
        }

        if (y_next >= y1)
			color = "Green";
		else
			color = "Red";
        Outputfile(x1, y1, color);

        vertices[i * 3] = x1 / 32;
        vertices[i * 3 + 1] = y1 / 32;
        vertices[i * 3 + 2] = y_next / 32; // Next y-coordinate
    }
   
   const int  numVertices2 = 100;
   
    
    const char* fileName2 = "Output2Variables.txt";
    std::ofstream GiveNumVertecies2(fileName2, std::ios::app);
    if (GiveNumVertecies2.is_open()) // Corrected condition to check GiveNumVertecies2
    {
        GiveNumVertecies2 << "Number of Vertecies: " << numVertices2 * numVertices2 << std::endl;
        GiveNumVertecies2.close();
    }


    // function with 2 variables 
    float x2, y2, z1;
    x2, y2, z1 = 0.0f;
    for (int i = 0; i < numVertices2; ++i)
    {
        for (int o = 0; o < numVertices2; ++o)
        {
            x2 = i * h;
            y2 = o * h;

            z1 = (y2*y2) * (x2*x2); // Your function here
           Outputfile2(x2, y2, z1);
        }

    }

    //spiral
  const  int numVerticesSpiral = 1000;
    float M_PI = 3.14159265358979323846f;
    GLfloat vertices3[numVerticesSpiral * 3];

    float c = 2.0f; 
    float t_max = 4 * M_PI; 
    float dt = t_max / numVerticesSpiral; 

    std::vector<float> spiralX(numVerticesSpiral);
    std::vector<float> spiralY(numVerticesSpiral);
    std::vector<float> spiralZ(numVerticesSpiral);

    for (int i = 0; i < numVerticesSpiral; ++i) {
        float t = i * dt; 
        float r = t; 

        // Calculate the coordinates
        spiralX[i] = r * cos(t);
        spiralY[i] = r * sin(t);
        spiralZ[i] = c * t;

        Outputfile3(spiralX[i], spiralY[i], spiralZ[i]);
        vertices3[i * 3] = spiralX[i] / 32;
        vertices3[i * 3 + 1] = spiralY[i] / 32;
        vertices3[i * 3 + 2] = spiralZ[i] / 32;
    }

   


    // glfw window creation
// --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Triangle window", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // build and compile our shader program
   // ------------------------------------
   // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);




    // graph points



    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    //graf 2D
   // glBufferData(GL_ARRAY_BUFFER,  sizeof(vertices), vertices, GL_STATIC_DRAW);

    // graf 3D
    GLfloat vertices2[numVertices2 * numVertices2 * 3];
    Readfile("Output2Variables.txt", vertices2, numVertices2 * numVertices2 * 3);
    glBufferData(GL_ARRAY_BUFFER, numVertices2 * numVertices2 * 3 * sizeof(GLfloat), vertices2, GL_STATIC_DRAW);

    // Spiral
    //glBufferData(GL_ARRAY_BUFFER, numVerticesSpiral * 3 * sizeof(GLfloat), vertices3, GL_STATIC_DRAW);

    // Position attribute
   // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // Unbind VBO (optional, for clarity)
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Unbind VAO (optional, for clarity)
    glBindVertexArray(0);

    //glLineWidth(3.f); 






    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //color
        float timeValue = glfwGetTime();
        float GreenValue = (sin(timeValue) / 2.0f) + 0.5f;
        int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
        glUseProgram(shaderProgram);
        glUniform4f(vertexColorLocation, 0.0f,1.f, 0.0f, 1.0f);



        // draw our first triangle
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

        //2D graph
        //glDrawArrays(GL_LINE_STRIP, 0, numVertices);

        // 3D graph
        glDrawArrays(GL_LINE_STRIP, 0, numVertices2 * numVertices2);

        // Spiral
        //glDrawArrays(GL_LINE_STRIP, 0, numVerticesSpiral);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();




    return 0;



}


void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        std::cout << "A key pressed ..." << std::endl;
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
    std::cout << " windows resized with " << width << " Height " << height << std::endl;
}
