#ifndef WINDOW_H
#define WINDOW_H

#include <QWindow>
#include <QOpenGLContext>
#include <QOpenGLFunctions_4_5_Core>
#include <QExposeEvent>

class Window : public QWindow, protected QOpenGLFunctions_4_5_Core
{
    Q_OBJECT

public:
    Window(QWindow *parent = 0);
    ~Window();
    void render();
    void initData();

protected:
    void exposeEvent(QExposeEvent*);

private:
    QOpenGLContext* context;
    GLuint VBO1, VBO2;
};

#endif // WINDOW_H
/// 1. QWindow -> QSurface { QSurfaceFormat {版本, 模式} }
/// 2. context QOpenGLContext
/// 3. void render()
/// 4. QOpenGLFunctions
/// 5. QExposeEvent
