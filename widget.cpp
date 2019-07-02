#include "widget.h"
#include <QVector3D>
using namespace std;

Widget::Widget(QWidget *parent)
    :QOpenGLWidget(parent), m_texture(0), m_indexBuffer(QOpenGLBuffer :: IndexBuffer)
{

}

Widget::~Widget()
{

}

void Widget::initializeGL()
{
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glEnable(GL_DEPTH_BUFFER_BIT);
    glEnable(GL_CULL_FACE);

    initShaders();
    initCube(1.0f);

}

void Widget::resizeGL(int w, int h)
{
    float aspect = w/ (float)h;
    m_projectionMatrix.setToIdentity();
    m_projectionMatrix.perspective(45,aspect,0.1f,10.0f);

}

void Widget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    QMatrix4x4 modelViewMatrix;
    modelViewMatrix.setToIdentity();
    modelViewMatrix.translate(0.0,0.0,-5.0);
    modelViewMatrix.rotate(30,1.0,0.0,0.0);
    modelViewMatrix.rotate(30,0.0,1.0,0.0);


    m_texture->bind(0);

    int offset=0;

    m_program.bind();
    m_program.setUniformValue("qt_ModelViewProjectionMatrix",m_projectionMatrix * modelViewMatrix);
    m_program.setUniformValue("qt_Texture0",0);

    int vertLoc=m_program.attributeLocation("qt_Vertex");
    m_program.enableAttributeArray(vertLoc);
    m_program.setAttributeBuffer(vertLoc,GL_FLOAT,offset,3,sizeof(VertexData));
    offset +=sizeof(QVector3D);

    int textLoc=m_program.attributeLocation("qt_MultiTexCoord0");
    m_program.enableAttributeArray(textLoc);
    m_program.setAttributeBuffer(vertLoc,GL_FLOAT,offset,3,sizeof(VertexData));
    m_indexBuffer.bind();

    glDrawElements(GL_TRIANGLES,m_indexBuffer.size(),GL_UNSIGNED_INT,0);



}

void Widget::initShaders()
{
   if(!m_program.addShaderFromSourceFile(QOpenGLShader::Vertex,":/vshader.vsh"))
        close();
   if(!m_program.addShaderFromSourceFile(QOpenGLShader::Fragment,":/fshader.fsh"))
        close();
   if(!m_program.link())
       close();
}

void Widget::initCube (float width )
{
    float width_div_2=width/2.0f;
    QVector<VertexData> vertexes;
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2),QVector2D(0.0,1.0),QVector3D(0.0,0.0,1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,-width_div_2, width_div_2),QVector2D(0.0,0.0),QVector3D(0.0,0.0,1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2),QVector2D(1.0,1.0),QVector3D(0.0,0.0,1.0)));
    vertexes.append(VertexData(QVector3D( width_div_2,-width_div_2, width_div_2),QVector2D(1.0,0.0),QVector3D(0.0,0.0,1.0)));

    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2),QVector2D(0.0,1.0),QVector3D(1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D( width_div_2,-width_div_2, width_div_2),QVector2D(0.0,0.0),QVector3D(1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D( width_div_2, width_div_2,-width_div_2),QVector2D(1.0,1.0),QVector3D(1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,-width_div_2,-width_div_2),QVector2D(1.0,0.0),QVector3D(1.0,0.0,0.0)));

    vertexes.append(VertexData(QVector3D( width_div_2, width_div_2,  width_div_2),QVector2D(0.0,1.0),QVector3D(0.0,1.0,0.0)));
    vertexes.append(VertexData(QVector3D( width_div_2, width_div_2, -width_div_2),QVector2D(0.0,0.0),QVector3D(0.0,1.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2,  width_div_2),QVector2D(1.0,1.0),QVector3D(0.0,1.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, -width_div_2),QVector2D(1.0,0.0),QVector3D(0.0,1.0,0.0)));

    vertexes.append(VertexData(QVector3D(width_div_2, width_div_2,- width_div_2),QVector2D(0.0,1.0),QVector3D(0.0,0.0,-1.0)));
    vertexes.append(VertexData(QVector3D(width_div_2,-width_div_2,- width_div_2),QVector2D(0.0,0.0),QVector3D(0.0,0.0,-1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2,- width_div_2),QVector2D(1.0,1.0),QVector3D(0.0,0.0,-1.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,-width_div_2,- width_div_2),QVector2D(1.0,0.0),QVector3D(0.0,0.0,-1.0)));

    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2, width_div_2),QVector2D(0.0,1.0),QVector3D(-1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2, width_div_2,-width_div_2),QVector2D(0.0,0.0),QVector3D(-1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,-width_div_2, width_div_2),QVector2D(1.0,1.0),QVector3D(-1.0,0.0,0.0)));
    vertexes.append(VertexData(QVector3D(-width_div_2,-width_div_2,-width_div_2),QVector2D(1.0,0.0),QVector3D(-1.0,0.0,0.0)));

    vertexes.append(VertexData(QVector3D( -width_div_2, -width_div_2,  width_div_2),QVector2D(0.0,1.0),QVector3D(0.0,-1.0,0.0)));
    vertexes.append(VertexData(QVector3D( -width_div_2, -width_div_2, -width_div_2),QVector2D(0.0,0.0),QVector3D(0.0,-1.0,0.0)));
    vertexes.append(VertexData(QVector3D( width_div_2, -width_div_2,  width_div_2),QVector2D(1.0,1.0),QVector3D(0.0,-1.0,0.0)));
    vertexes.append(VertexData(QVector3D( width_div_2, -width_div_2, -width_div_2),QVector2D(1.0,0.0),QVector3D(0.0,-1.0,0.0)));


    QVector<GLuint> indexes;
    for(int i=0;i<24;i+= 4)
    {

    indexes.append(i + 0);
    indexes.append(i + 1);
    indexes.append(i + 2);
    indexes.append(i + 2);
    indexes.append(i + 1);
    indexes.append(i + 3);

    m_arraybuffer.create();
    m_arraybuffer.bind();
    m_arraybuffer.allocate(vertexes.constData(),vertexes.size() * sizeof(VertexData));
    m_arraybuffer.release();

    m_indexBuffer.create();
    m_indexBuffer.bind();
    m_indexBuffer.allocate(indexes.constData(),indexes.size() * sizeof(GLuint));
    m_indexBuffer.release();

    m_texture = new QOpenGLTexture(QImage(":/cube.png").mirrored());
    m_texture->setMinificationFilter(QOpenGLTexture::Nearest);
    m_texture->setMagnificationFilter(QOpenGLTexture::Linear);
    m_texture->setWrapMode(QOpenGLTexture::Repeat);

  }
}
