#ifndef PAINTAREA_H
#define PAINTAREA_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
#include <QPainter>
#include <QImage>
#include <QPen>
#include <QFile>
#include <item.h>
#include <item.h>

class PaintArea : public QWidget
{
    Q_OBJECT
public:

    enum ShapeType
    {
        none, eraser, line, rectangle, ellipse
    };

    PaintArea();                            //构造函数

    //图形
    void setShape(ShapeType shape);         //设置图形

    //画笔
    void setPenColor(QColor color);         //设置画笔颜色
    void setPenWidth(int width);            //设置画笔宽度
    void setPenStyle(Qt::PenStyle style);   //设置画笔样式

    //填充
    void setBrushColor(QColor color);       //设置填充颜色
    void setBrushStyle(Qt::BrushStyle style);//设置填充样式

    //查看
    void zoomIn();
    void zoomOut();
    void zoom_l();
    void doRotate();
    void doShear();
    void doClear();

    //文件
    void addFile();
    bool saveFile(QString name, QString format, QString location);
    void openFile(QString filename);
    void saveAsFile();
    void setfile(QString name, QString format,QString location);
    bool isModified() const { return modified; } //判断画布内容是否被更改过 bool saveImage(const QString &fileName, const char *fileFormat); //保存图片
    bool openImage(const QString &fileName); //打开图片
    bool saveImage(const QString &fileName, const char *fileFormat);

protected:

    void paintEvent(QPaintEvent *);         //定义重绘函数
    void paint(QImage &theImage);           //绘图
    void mousePressEvent(QMouseEvent *);    //鼠标点击
    void mouseMoveEvent(QMouseEvent *);     //鼠标移动
    void mouseReleaseEvent(QMouseEvent *);  //鼠标释放

private:

    //文件
    QString fileName;
    QString fileFormat;
    QString fileLocation;
    bool modified;

    //画布
    QImage image;
    QColor backColor;

    //图形
    ShapeType curShape;

    //画笔
    QPen pen;
    int penWidth;               //宽度
    QColor penColor;            //颜色
    Qt::PenStyle penStyle;      //风格

    //填充
    QBrush brush;
    QColor brushColor;          //颜色
    Qt::BrushStyle brushStyle;  //风格

    QPoint lastPoint, endPoint; //定义两个坐标存鼠标前后的两个位置

    qreal scale;
    int angle;
    qreal shear;

    QImage tempImage;
    bool isDrawing;
};

#endif // PAINTAREA_H
