#ifndef CLSOPENGL_H
#define CLSOPENGL_H

#include "QGLWidget"
#include "GL/glu.h"

class clsOpenGL:public QGLWidget
{
    Q_OBJECT
public:
    explicit clsOpenGL(QWidget * parent = 0);
protected:
    void initializeGL();
    void paintGL();
    void resizeGL(int width=80,int height=60);

public slots:
    void ChangeSides(int NewSidesNum);
    void ChangeRadius(double NewRadiusNum);
private:
    int g_iSides;
    double g_dRadius;
};

#endif // CLSOPENGL_H

