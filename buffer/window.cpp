#include "window.h"
#include <QDebug>

Window::Window(QWindow *parent): QWindow(parent)
{
    ///1 .
    QSurfaceFormat format;
    format.setMajorVersion(4);
    format.setMinorVersion(5);

    this->setFormat(format);
    this->setSurfaceType(QSurface::OpenGLSurface);
    this->setWidth(400);
    this->setHeight(400);

    ///2.
    context = new QOpenGLContext(this);
    context->setFormat(format);
    context->create();

}

/// 状态机 缓冲
void Window::initData()
{
    /*
    GLfloat vertices[] =
    {
        0.0f, 1.0f,   1.0f, 0.0f, 0.0f,
        -1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
        1.0f, -1.0f,  0.0f, 0.0f, 1.0f
        ///位置        ///颜色
    };
    */

    GLfloat vertices[] =
    {
        0.0f, 1.0f,
        -1.0f, -1.0f,
        1.0f, -1.0f,
        ///位置
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f
        ///颜色
    };

    glGenBuffers(1, &VBO1);
    glGenBuffers(1, &VBO2);

    glBindBuffer(GL_ARRAY_BUFFER ,VBO1);
    //glBindBuffer(GL_ARRAY_BUFFER ,VBO2);

    /* 如果不绑定 打印错误
    //glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glNamedBufferData(VBO2, sizeof(vertices), vertices, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER ,VBO2);

    GLfloat data[9];
    //glGetNamedBufferSubData(VBO2, sizeof(GLfloat)*5, sizeof(GLfloat)*10, data);
    glGetBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6, sizeof(GLfloat)*9, data);
    for(int i = 0; i < 9; i++)
    {
        qDebug()<<data[i];
    }
    */

    /*
    ///查询
    GLfloat data[9];
    //glGetNamedBufferSubData(VBO2, sizeof(GLfloat)*5, sizeof(GLfloat)*10, data);
    glGetBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6, sizeof(vertices)*3/5, data);
    for(int i = 0; i < 9; i++)
    {
        qDebug()<<data[i];
    }
    */


    /*
    ///清理 / 更新
    GLfloat voidData[] = {};
    glBufferData(GL_ARRAY_BUFFER, sizeof(voidData), voidData, GL_STATIC_DRAW);

    GLint bufferSize = 8888;
    glGetNamedBufferParameteriv(VBO2, GL_BUFFER_SIZE, &bufferSize);
    qDebug()<<bufferSize;
    */

    /* 局部更新
    GLfloat color[] = {
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f,
        0.5f, 0.5f, 0.5f
    };
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6, sizeof(vertices)*3/5, color);

    GLfloat data[9];
    //glGetNamedBufferSubData(VBO2, sizeof(GLfloat)*5, sizeof(GLfloat)*10, data);
    glGetBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6, sizeof(vertices)*3/5, data);
    for(int i = 0; i < 9; i++)
    {
        qDebug()<<data[i];
    }
    */

    /* 删除buffer
    glDeleteBuffers(1, &VBO2);
    if(glIsBuffer(VBO2))
    {
        qDebug()<<"仍然是一个缓冲";
    }
    else
    {
        qDebug()<<"已经删除了";
    }
    */

    /* 映射
    GLfloat vertices2[] =
    {
        5.0f, 1.0f,
        -1.0f, -1.0f,
        1.0f, -1.0f,
        ///位置
        5.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 8.0f
        ///颜色
    };

    void* memPtr = glMapNamedBuffer(VBO2, GL_WRITE_ONLY);
    memcpy(memPtr, vertices2, sizeof(vertices2));
    glUnmapBuffer(GL_ARRAY_BUFFER);

    GLfloat data[9];
    //glGetNamedBufferSubData(VBO2, sizeof(GLfloat)*5, sizeof(GLfloat)*10, data);
    glGetBufferSubData(GL_ARRAY_BUFFER, sizeof(GLfloat)*6, sizeof(vertices)*3/5, data);
    for(int i = 0; i < 9; i++)
    {
        qDebug()<<data[i];
    }
    */
}

Window::~Window()
{

}

void Window::exposeEvent(QExposeEvent *e)
{
    Q_UNUSED(e);
    this->render();
}

void Window::render()
{
    static bool isInitOpenGLFunctions = false;
    if(!isExposed())
    {
        return;
    }
    context->makeCurrent(this);

    if(!isInitOpenGLFunctions)
    {
        initializeOpenGLFunctions();
        initData();
        isInitOpenGLFunctions = true;
    }

    glClearColor(0.1f, 0.5f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    context->swapBuffers(this);
}




/*
    你最喜欢的{
        {
            你最喜欢的水果: [苹果, 桃子, 香蕉]
            你最喜欢的颜色: [红色, 绿色, 蓝色]
            你最喜欢的女人: [你老婆, 隔壁王阿姨, 金星]
        }
        {
            你最喜欢的水果: 苹果
            你最喜欢的颜色: 红色
            你最喜欢的女人: 隔壁王阿姨
            你最喜欢的女人: 金星
            你最喜欢的女人: 隔壁王阿姨
        }
        {
            把你喜欢的都给你();
            //就不给你你喜欢的();
        }
    }
*/































