#ifndef WINDOW_H
#define WINDOW_H

#include <QWindow>
#include <QSurfaceFormat>
#include <QOpenGLContext>
#include <QOpenGLFunctions_3_3_Core>
#include <QExposeEvent>

class Window : public QWindow, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT

public:
    Window(QWindow *parent = 0);
    ~Window();
    void render();

protected:
    void exposeEvent(QExposeEvent*);

private:
    QOpenGLContext* context;
};

#endif // WINDOW_H
/// 1. QWindow -> QSurface { QSurfaceFormat { 版本, 模式 } }
/// 2. context QOpenGLContext
/// 3. QOpenGLFunctions_3_3_Core
/// 4. QExposeEvent
