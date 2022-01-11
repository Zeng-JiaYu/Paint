#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //设置窗口大小
    resize(2400,1600);

    //ui界面
    ui->setupUi(this);

    area = new PaintArea;

    //滚动条设置
    scrollArea= new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);//scrollarea背景色设置为黑色
    scrollArea->setWidget(area); //将画布添加到scrollarea中
    scrollArea->widget()->setMinimumSize(800,600);//初始化大小为800*600
    setCentralWidget(scrollArea); //把滚动条加到主窗口

    //添加工具栏选项
    penStyleComboBox(ui->penStyleComboBox);
    brushStyleComboBox(ui->brushPatternComboBox);
    colorComboBox(ui->colorComboBox);

    browser = ui->penColor;
    ui->brushColor->setStyleSheet("background:rgb(255, 255, 255)");

}

//添加线条样式选项
void MainWindow :: penStyleComboBox(QComboBox *comboBox)
{
    comboBox->addItem(tr("实线"));
    comboBox->addItem(tr("虚线"));
    comboBox->addItem(tr("点线"));
}

//添加填充样式选项
void MainWindow :: brushStyleComboBox(QComboBox *comboBox)
{
    comboBox->addItem(tr("单一色填充"));
    comboBox->addItem(tr("横纵线填充"));
    comboBox->addItem(tr("点填充"));
}

//添加颜色选项
void MainWindow :: colorComboBox(QComboBox *comboBox)
{
    QPixmap pix(16,16);
    QPainter painter(&pix);

    painter.fillRect(0,0,16,16,Qt::black);
    comboBox->addItem(QIcon(pix),tr("黑"));
    painter.fillRect(0,0,16,16,Qt::red);
    comboBox->addItem(QIcon(pix),tr("红"));
    painter.fillRect(0,0,16,16,Qt::blue);
    comboBox->addItem(QIcon(pix),tr("蓝"));
    painter.fillRect(0,0,16,16,Qt::white);
    comboBox->addItem(QIcon(pix),tr("白"));
}

//槽函数：设置形状
void MainWindow::on_patternComboBox_currentIndexChanged(const QString &shape)
{
    if (shape == tr("无"))
        area->setShape(PaintArea::none);
    else if (shape == tr("矩形"))
        area->setShape(PaintArea::rectangle);
    else if (shape == tr("直线"))
        area->setShape(PaintArea::line);
    else if (shape == tr("椭圆"))
        area->setShape(PaintArea::ellipse);
    else if (shape == tr("橡皮"))
        area->setShape(PaintArea::eraser);
}

//槽函数：设置画笔样式：实线、虚线、点线
void MainWindow::on_penStyleComboBox_currentIndexChanged(const QString &pattern)
{
    if (pattern == tr("实线"))
        area->setPenStyle(Qt::SolidLine);
    else if  (pattern == tr("虚线"))
        area->setPenStyle(Qt::DashLine);
    else if (pattern == tr("点线"))
        area->setPenStyle(Qt::DotLine);
}

//槽函数：设置画笔宽度
void MainWindow::on_penWidthSpinBox_valueChanged(int width)
{
    area->setPenWidth(width);
}

//槽函数：设置填充样式
void MainWindow::on_brushPatternComboBox_currentIndexChanged(const QString &patern)
{
    if (patern == tr("单一颜色填充"))
        area->setBrushStyle(Qt::SolidPattern);
    else if  (patern == tr("横纵线填充"))
        area->setBrushStyle(Qt::CrossPattern);
    else if (patern == tr("点填充"))
        area->setBrushStyle(Qt::Dense7Pattern);
}

//析构函数
MainWindow :: ~MainWindow()
{
    delete ui;
}

//保存
void MainWindow::save()
{
    saveFileDialog dlg;
    dlg.show();
    if(dlg.exec() == QDialog::Accepted)
    {
        QString name = dlg.getFileName();
        QString format = dlg.getFileFormat();
        QString location = dlg.getFileLocation();
        area->saveFile(name,format,location);
    }
}

//是否保存当前文件
bool MainWindow::saveOrNot()
{
    QMessageBox::StandardButton box;
    box = QMessageBox::information(this,tr("保存文件"),tr("是否保存当前文件"),QMessageBox::Yes|QMessageBox::No|QMessageBox::Cancel, QMessageBox::Yes);
    if (box == QMessageBox::Yes)
        return true;
    else if(box == QMessageBox::No)
        return false;
    else
        return false;
}

//槽函数：保存
void MainWindow::on_actionsave_triggered()
{
    save();
}

//新建
void MainWindow::on_actionADD_triggered()
{
    if(saveOrNot())
    {
        save();
        area->addFile();
    }
}

//打开文件
void MainWindow::on_actionopen_triggered()
{
    if(saveOrNot())
    {
        save();
        QString fileName = QFileDialog::getOpenFileName(this,tr("打开文件"),".","*.jpg;*.bmp;*.png");
        if(!fileName.isEmpty())
            area->openFile(fileName);
    }
}

//另存为
void MainWindow::on_actionsave_as_triggered()
{
    saveFileDialog dlg;
    dlg.show();
    if(dlg.exec() == QDialog::Accepted)
    {
        QString name = dlg.getFileName();
        QString format = dlg.getFileFormat();
        QString location = dlg.getFileLocation();
        area->saveFile(name,format,location);
    }
}

//退出
void MainWindow::on_actionexit_triggered()
{
    if(saveOrNot())
        save();
    qApp->quit();
}

//主颜色选择
void MainWindow::on_colorComboBox_currentIndexChanged(const QString &option)
{
    QString color;
    if(option == tr("黑"))
        color = "black";
    else if (option == tr("蓝"))
        color = "blue";
    else if (option == tr("红"))
        color = "red";
    else if (option == tr("白"))
        color = "white";
    if(browser ==  ui->penColor)
    {
        ui->penColor->setStyleSheet("background:"+color);
        area->setPenColor(color);
    }
    else
    {
        ui->brushColor->setStyleSheet("background:"+color);
        area->setBrushColor(color);
    }
    update();
}

//颜色对话框
void MainWindow::on_ColorSelect_clicked()
{
    QColor color = QColorDialog::getColor(); //从颜色对话框获得颜色
    QString temp = QString("rgba(%1, %2, %3, %4)").arg(color.red()).arg(color.green()).arg(color.blue()).arg(color.alpha());
    if(browser ==  ui->penColor)
    {
        ui->penColor->setStyleSheet("background:"+temp);
        area->setPenColor(color);
    }
    else
    {
        ui->brushColor->setStyleSheet("background:"+temp);
        area->setBrushColor(color);
    }
    update();
}

//选择画笔颜色
void MainWindow::on_penRadioButton_clicked()
{
    browser = ui->penColor;
}

//选择画刷颜色
void MainWindow::on_brushRadioButton_clicked()
{
    browser = ui->brushColor;
}

//放大
void MainWindow::on_actionzoomin_2_triggered()
{
    area->zoomIn();
}

//缩小
void MainWindow::on_actionzoomout_2_triggered()
{
    area->zoomOut();
}

//还原
void MainWindow::on_actionrestore_2_triggered()
{
    area->zoom_l();
}

//旋转
void MainWindow::on_actionspin_triggered()
{
     area->doRotate();
}

//拉伸
void MainWindow::on_actionstretch_triggered()
{
    area->doShear();
}

//清空
void MainWindow::on_actiondelete_all_triggered()
{
    area->doClear();
}
//打开绘图工具
void MainWindow::on_actiondrawing_technique_triggered()
{
    ui->dockWidget->show();
}
