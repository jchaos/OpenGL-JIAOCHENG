#ifndef WINDOW_H
#define WINDOW_H

#include <QWindow>
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QOpenGLFunctions_3_3_Core>
#include <QExposeEvent>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

class Window : public QWindow, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    Window(QWindow *parent = 0);
    ~Window();
    void initData();
    void initShader();
    void initTexture();
    void render();

protected:
    void exposeEvent(QExposeEvent*);

private:
    QOpenGLContext* context;
    QOpenGLTexture *texture;
    QOpenGLShaderProgram* program;
    GLuint VBO,VAO, EBO;
};

#endif // WINDOW_H
