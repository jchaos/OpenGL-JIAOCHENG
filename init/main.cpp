﻿#include "window.h"
#include <QGuiApplication>

int main(int argc, char *argv[])
{
    QGuiApplication a(argc, argv);

    Window w;
    w.show();

    return a.exec();
}
