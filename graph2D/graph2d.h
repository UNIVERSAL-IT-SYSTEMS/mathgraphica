#ifndef GRAPH2D_H
#define GRAPH2D_H

#include <QString>
#include <QList>
#include <QOpenGLBuffer>
#include <QVector3D>
#include <QOpenGLShaderProgram>
#include <QColor>
#include "calculator/calculator.h"


class Graph2D
{
public:
    Graph2D();
    ~Graph2D();

    QString getGraph2DExpression()const{return m_graph2DExpression;} // normal and polar graphs

    QString getGraph2DExpression_f1()const{return m_graph2DExpression_f1;} // parametric graphs
    QString getGraph2DExpression_f2()const{return m_graph2DExpression_f2;} // parametric graphs

    QString getIntervalMin()const{return m_xminExpression;}
    QString getIntervalMax()const{return m_xmaxExpression;}
    QString getDelta()const{return m_deltaExpression;}


    // set a graph from a math expression
    void setInterval(const double &min_, const double &max_);
    void setInterval(const QString &minExpression_, const QString &maxExpression_);
    void setDelta(const double delta_);
    void setDelta(const QString deltaExpression_);
    void setGraph2DExpression(const QString &expression_);
    void setGraph2DExpression_f1(const QString &expression_f1_);
    void setGraph2DExpression_f2(const QString &expression_f2_);




    // setupGraph() must be called after setInterval(), setDelta() and setGraph2DExpression()
    // it calculates and setup up the array's xx and yy
    bool setupGraph();
    bool setupGraphParametric();

    // ... or set a graph from an array of values
    void setGraph2DArray(QList<double> &xx_, QList<double> &yy_);

    Graph2D &operator=(const Graph2D &a);

    void setPolarGraph(const bool &bPolarGraph_);
    bool isPolarGraph();
private:
    bool bPolarGraph;

public:
    void setParametric(const bool &bParametricGraph_);
    bool isParametricGraph() const;
private:
    bool bParametricGraph;

public:
    void UpdateGraphTime(double t_, QOpenGLShaderProgram &m_shaderProgram);
    void setTime(const double &t_){ t = t_;}


    bool isTimeGraph(){return timeGraph2D;} // check if is a graph with a variable t (time) in "m_graph2DExpression"
    // timeGraphs can be animated

private:

    bool timeGraph2D;
    QString m_graph2DExpression; //used for normal and polar graphs
    QString m_graph2DExpression_f1; //used for parametric f1(t) graph
    QString m_graph2DExpression_f2; //used for parametric f2(t) graph


    QString m_xminExpression;
    double m_xmin;
    QString m_xmaxExpression;
    double m_xmax;
    QString m_deltaExpression;
    double m_delta;

    QList<double> xx;
    QList<double> yy;
    QList<int> poles_interval;

    double t; // time


    Calculator calc;


    // drawing ---------------------------------------------
    QOpenGLBuffer m_vertexBufferGraph2D;
    //QOpenGLBuffer m_colorBufferGraph2D;
    QVector3D *vertexPosition;
    //QVector3D *vertexColor;
    QColor m_graphColor;
    int bufferSize;

public:
    void prepareBuffers();
    void releaseBuffers();
    void setBufferData(QOpenGLShaderProgram &m_shaderProgram);
    void draw(QOpenGLShaderProgram &m_shaderProgram);
    void setColor(const QColor &color_);
    void setColor(const double &r, const double &g, const double &b);
    QColor getColor(){return m_graphColor;}

};

#endif // GRAPH2D_H
