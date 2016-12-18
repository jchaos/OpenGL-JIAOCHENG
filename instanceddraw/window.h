#ifndef WINDOW_H
#define WINDOW_H

#include <QWindow>
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QOpenGLFunctions_3_3_Core>
#include <QExposeEvent>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <Qt3DCore>
#include <Qt3DRender>

class Window : public QWindow, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    Window(QWindow *parent = 0);
    ~Window();
    void render();
    void initShader();
    void initBuffer();
    void initCamera();
    void initModel();
    void update();
protected:
    void exposeEvent(QExposeEvent *);
    bool event(QEvent *);
private:
    QOpenGLContext* context;
    QOpenGLShaderProgram* program;
    GLuint VBO, VAO, IBO, ISZ;
    Qt3DRender::QCamera camera;
    QMatrix4x4 model;

};

#endif // WINDOW_H
///Qwindow->QSurface{QSurfaceFormat{opengl version, opengl 模式}}
///QOpenGLContext opengl context
///QOpenGLFunctions_3_3_Core
