#include "window.h"
#include <QDebug>

Window::Window(QWindow *parent): QWindow(parent)
{
    ///1.
    QSurfaceFormat format;
    format.setMajorVersion(3);
    format.setMinorVersion(3);

    this->setFormat(format);
    this->setSurfaceType(QSurface::OpenGLSurface);
    this->setWidth(400);
    this->setHeight(400);
    this->setTitle("Textrue");

    ///2.
    context = new QOpenGLContext(this);
    context->setFormat(format);
    context->create();
}

/// 4.
void Window::exposeEvent(QExposeEvent* e)
{
    Q_UNUSED(e);
    this->render();
}

Window::~Window()
{

}

void Window::initData()
{

    GLfloat vertices[] = {
        //位置                 //颜色              //纹理
        0.5f, 0.5f,  0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, //右上
        0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, //右下
       -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, //左下
        -0.5f, 0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  //左上
    };
    GLuint indices[] = {
        0, 1, 3,       //第一个三角形
        1, 2, 3        //第二个三角形
    };

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Window::initTexture()
{
    //创建纹理//纹理路径//
    texture = new QOpenGLTexture(QImage("f:/qq.jpg").mirrored());
    texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    texture->setMagnificationFilter(QOpenGLTexture::Linear);
}

void Window::initShader()
{
    program = new QOpenGLShaderProgram(this);
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, ":/shader.vert");
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, ":/shader.frag");
    program->link();
}

///3.
void Window::render()
{
    static bool isInitializedOpenGLFunctions = false;
    if(!isExposed())
    {
        return;
    }

    context->makeCurrent(this);

    if(!isInitializedOpenGLFunctions)
    {
        initializeOpenGLFunctions();

        initShader();
        initData();
        initTexture();
        isInitializedOpenGLFunctions = true;
    }

    glViewport(0, 0, this->width(), this->height());
    glClearColor(0.1f, 0.5f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    texture->bind();
    program->bind();
    glBindVertexArray(VAO);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    context->swapBuffers(this);
}
