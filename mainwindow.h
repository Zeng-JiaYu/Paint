#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <savefiledialog.h>
#include <paintarea.h>
#include <QMainWindow>
#include <QScrollArea>
#include <QComboBox>
#include <QSpinBox>
#include <QPainter>
#include <QToolBar>
#include <QGroupBox>
#include <QPushButton>
#include <QColorDialog>
#include <QMessageBox>
#include <QFileDialog>
#include <QTextBrowser>
#include <QButtonGroup>
#include <shape.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow(QWidget *parent = nullptr);          //构造函数

    void penStyleComboBox(QComboBox *comboBox);     //画笔样式
    void brushStyleComboBox(QComboBox *comboBox);   //填充样式
    void colorComboBox(QComboBox *comboBox);        //颜色样式
    void save();
    bool saveOrNot();

    ~MainWindow();


private slots:

    //设置画笔样式：实线、虚线、点线
    void on_penStyleComboBox_currentIndexChanged(const QString &pattern);
    //设置画笔宽度
    void on_penWidthSpinBox_valueChanged(int width);
    //设置填充样式
    void on_brushPatternComboBox_currentIndexChanged(const QString &pattern);
    //设置形状
    void on_patternComboBox_currentIndexChanged(const QString &shape);
    //保存文件
    void on_actionsave_triggered();
    void on_actionADD_triggered();
    //打开文件
    void on_actionopen_triggered();
    //另存为
    void on_actionsave_as_triggered();
    //退出
    void on_actionexit_triggered();
    //主颜色选择
    void on_colorComboBox_currentIndexChanged(const QString &option);
    //颜色对话框
    void on_ColorSelect_clicked();
    //选择画笔颜色
    void on_penRadioButton_clicked();
    //选择画刷颜色
    void on_brushRadioButton_clicked();
    //放大
    void on_actionzoomin_2_triggered();
    //缩小
    void on_actionzoomout_2_triggered();
    //还原
    void on_actionrestore_2_triggered();
    //旋转
    void on_actionspin_triggered();
    //拉伸
    void on_actionstretch_triggered();
    //清空
    void on_actiondelete_all_triggered();
    void on_actiondrawing_technique_triggered();

private:
    Ui::MainWindow *ui;                     //UI界面
    PaintArea *area;                        //画图界面
    QScrollArea *scrollArea;                //滚动
    QTextBrowser *browser;
};

#endif // MAINWINDOW_H
