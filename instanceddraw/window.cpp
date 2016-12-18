#include "window.h"
#include <QDebug>
#include <QCoreApplication>
#include <QMatrix4x4>
#include <QVector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/random.hpp>

using namespace Qt3DRender;

Window::Window(QWindow *parent): QWindow(parent)
{
    ///配置窗口
    this->setWidth(1200);
    this->setHeight(600);
    this->setSurfaceType(QSurface::OpenGLSurface);

    QSurfaceFormat format;
    format.setMajorVersion(3);
    format.setMinorVersion(3);

    this->setFormat(format);

    ///配置OpenGL的context
    context = new QOpenGLContext(this);
    context->setFormat(format);
    context->create();

}

bool Window::event(QEvent *e)
{
    switch(e->type())
    {
    case QEvent::UpdateRequest:
        update();
        return true;
    default:
        return QWindow::event(e);
    }
}

void Window::exposeEvent(QExposeEvent *e)
{
    Q_UNUSED(e);
    if(isExposed())
    {
        this->render();
    }
}

void Window::initShader()
{
    program = new QOpenGLShaderProgram(this);
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader.vert");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader.frag");
    program->link();
}

void Window::initBuffer()
{
    GLfloat vertices[] = {
        //后
        -0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        //前
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        //左
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        //右
         0.5f,  0.5f,  0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        //下
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
        //上
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
    };

    GLfloat modelZ[450000];

    glm::vec4 mz;

    for(int i = 0; i < 150000; i++)
    {
        mz = glm::vec4(glm::gaussRand(glm::vec3(0), glm::vec3(10)), 1);
        modelZ[i*3+0] = mz.x;
        modelZ[i*3+1] = mz.y;
        modelZ[i*3+2] = mz.z;
    }

    glGenBuffers(1, &VBO); ///返回一个可用缓冲区地址
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &ISZ);
    glBindBuffer(GL_ARRAY_BUFFER, ISZ);
    glBufferData(GL_ARRAY_BUFFER, sizeof(modelZ), modelZ, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glVertexAttribPointer(program->attributeLocation("position"), 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(program->attributeLocation("position"));
    glBindBuffer(GL_ARRAY_BUFFER, ISZ);
    glVertexAttribPointer(program->attributeLocation("isz"), 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(program->attributeLocation("isz"));
    glVertexAttribDivisor(program->attributeLocation("isz"), 1);
}

void Window::initCamera()
{
    camera.setProjectionType(QCameraLens::PerspectiveProjection);
    camera.setNearPlane(0.1f);
    camera.setFarPlane(1000.0f);
    camera.setAspectRatio(width()/height());
    camera.setFieldOfView(60.0f);

    camera.setPosition(QVector3D(0.0f, 0.0f, 500.0f));
    camera.setUpVector(QVector3D(0.0f, 1.0f, 0.0f));
    camera.setViewCenter(QVector3D(0.0f, 0.0f, -1.0f));
}

void Window::initModel()
{
    model.scale(1.5f);
}

void Window::update()
{
    context->makeCurrent(this);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    model.rotate(10.0f / this->screen()->refreshRate(), 1.0f, 0.0f ,1.0f);

    program->setUniformValue(program->uniformLocation("p"), camera.projectionMatrix());
    program->setUniformValue(program->uniformLocation("v"), camera.viewMatrix());
    program->setUniformValue(program->uniformLocation("m"), model);

    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 36);
    glPolygonMode(GL_FRONT, GL_LINE);
    glDrawArraysInstanced(GL_TRIANGLES, 0, 36, 150000);

    context->swapBuffers(this);
    QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
}

void Window::render()
{
    static bool isInitializedOpenGLFunctions = false;
    context->makeCurrent(this);

    if(!isInitializedOpenGLFunctions)
    {
        initializeOpenGLFunctions();
        initShader();
        initCamera();
        initModel();
        initBuffer();
        isInitializedOpenGLFunctions = true;
    }

    glViewport(0, 0, width(), height());
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    program->bind();

    this->update();
}

Window::~Window()
{

}
