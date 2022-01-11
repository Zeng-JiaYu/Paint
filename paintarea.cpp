#include "paintarea.h"

//构造函数
PaintArea::PaintArea()//(QWidget *parent) : QWidget(parent)
{
    image = QImage(1800,1200,QImage::Format_RGB32);//设置背景画布的大小和颜色
    backColor = Qt::white;
    image.fill(backColor);

    curShape = none;
    penColor = Qt::black;
    penWidth = 3;
    penStyle = Qt::SolidLine;
    brushColor = Qt::white;
    brushStyle = Qt::SolidPattern;

    scale=1;
    angle=0;
    shear=0;

    isDrawing=false;
}

//设置图形
void PaintArea::setShape(ShapeType shape)
{
    curShape = shape;
}

//设置画笔颜色
void PaintArea::setPenColor(QColor color)
{
    penColor = color;
}

//设置画笔宽度
void PaintArea::setPenWidth(int width)
{
    penWidth = width;
}

//设置画笔样式
void PaintArea::setPenStyle(Qt::PenStyle style)
{
    penStyle = style;
}

//设置填充颜色
void PaintArea::setBrushColor(QColor color)
{
    brushColor = color;
}

//设置填充样式
void PaintArea::setBrushStyle(Qt::BrushStyle style)
{
    brushStyle = style;
}

//定义重绘函数
void PaintArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
        //添加编辑菜单的功能
    //   painter.scale(scale,scale);
        if(isDrawing)
        {
            painter.drawImage(0,0,tempImage);
        }
        else
        if(angle)
        {
            QImage copyImage=image;
            QPainter pp(&copyImage);
            QPointF center(copyImage.width()/2.0, copyImage.height()/2.0);
            pp.translate(center);
            pp.rotate(angle);
            pp.translate(-center);
            pp.drawImage(0,0,image);
            image=copyImage;
            angle=0;
        }
        if(shear)
        {
           QImage copyImage=image;
           QPainter pp(&copyImage);
           pp.shear(shear,shear);
           pp.drawImage(0,0,image);
           image=copyImage;
           shear=0;
        }
        painter.drawImage(0,0,image);
}

//绘图
void PaintArea::paint(QImage &theImage)
{
    QPainter pp(&theImage);

    pen.setColor(penColor);
    pen.setStyle(penStyle);
    pen.setWidth(penWidth);

    brush.setColor(brushColor);
    brush.setStyle(brushStyle);

    pp.setPen(pen);
    pp.setBrush(brush);

    int x,y,w,h;
    x = lastPoint.x();
    y = lastPoint.y();
    w = endPoint.x()-x;
    h = endPoint.y()-y;

   // Item *item = nullptr;

    switch (curShape)
    {
        case eraser:
        {
            pen.setColor(backColor);
            pp.setPen(pen);
            pp.drawLine(lastPoint,endPoint);
            lastPoint = endPoint;//终止坐标变为起始坐标，方便继续画图
            break;
        }
        case none:
        {
            pp.drawLine(lastPoint,endPoint);
            lastPoint = endPoint;//终止坐标变为起始坐标，方便继续画图
            break;
        }
        case line:
        {
            pp.drawLine(lastPoint,endPoint);
            break;
        }
        case rectangle:
        {
            pp.drawRect(x,y,w,h);
            break;
        }
        case ellipse:
        {
            pp.drawEllipse(x,y,w,h);
            break;
        }
    }
    update(); //进行更新界面显示，可引起窗口重绘
}

//鼠标点击
void PaintArea::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        lastPoint=event->pos();
        isDrawing=true;
    }
}

//鼠标移动
void PaintArea::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        endPoint=event->pos();
        if(curShape==none || curShape == eraser)
        {
            isDrawing=false;
            paint(image);
        }
        else  //吐过绘制特殊图形，则在临时绘图区tempImage上绘制
        {
            tempImage = image;  //每次绘制tempimage前用上一次image中的图片进行填充
            paint(tempImage);
        }
    }
}

//鼠标点击结束
void PaintArea::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton)
    {
        endPoint=event->pos();
        isDrawing=false;
        paint(image);
    }
}

//设置文件信息
void PaintArea::setfile(QString name, QString format, QString location)
{
    fileName = name;
    fileFormat = format;
    fileLocation = location;
}

//保存
bool PaintArea::saveFile(QString name, QString format, QString location)
{
    setfile(name,format,location);
    QByteArray temp = fileFormat.toLatin1();
    const char *charMat = temp.data();
    if(image.save(fileLocation+"\\"+fileName,charMat))
        return true;
    else
        return false;
}

void PaintArea::addFile()
{
    image = QImage(1800,1200,QImage::Format_RGB32);//设置背景画布的大小和颜色
    backColor = qRgb(255,255,255);
    image.fill(backColor);
}
//打开
void PaintArea::openFile(QString filename)
{
    image.load(filename);
}

void PaintArea::zoomIn()
{
    scale*=1.2;
    update();
}

void PaintArea::zoomOut()
{
    scale/=1.2;
    update();
}
void PaintArea::zoom_l()
{
    scale = 1;
    update();
}

void PaintArea::doRotate()
{
    angle += 90;
    update();
}

void PaintArea::doShear()
{
    shear = 0.2;
    update();
}

void PaintArea::doClear()
{
    image.fill(backColor);
    update();
}
