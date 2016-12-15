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
        isInitializedOpenGLFunctions = true;
    }

    glClearColor(0.1f, 0.5f, 0.8f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    context->swapBuffers(this);
}
