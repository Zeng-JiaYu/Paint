#include "savefiledialog.h"
#include "ui_savefiledialog.h"

saveFileDialog::saveFileDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::saveFileDialog)
{
    ui->setupUi(this);
    //设置文件名的默认值
    ui->fileName->setPlaceholderText(QString("未命名"));
    //新增项目
    ui->fileFormat->addItem(tr("JPG"));
    ui->fileFormat->addItem(tr("PNG"));
    ui->fileFormat->addItem(tr("BMP"));
}

saveFileDialog::~saveFileDialog()
{
    delete ui;
}

//设置文件名
void saveFileDialog::on_fileName_textEdited(const QString &name)
{
    fileName = name;
}

//设置文件地址
void saveFileDialog::on_filelLocation_textEdited(const QString &location)
{
    fileLocation = location;
}

//设置文件后缀名
void saveFileDialog::on_nameSuffix_currentIndexChanged(const QString &name)
{
    if (name == tr("JPG"))
        fileFormat = "jpg";
    else if (name == tr("BMP"))
        fileFormat = "bmp";
    else if (name == tr("PNG"))
        fileFormat = "png";
}

//返回文件名
QString saveFileDialog::getFileName()
{
    return fileName;
}

//返回文件地址
QString saveFileDialog::getFileLocation()
{
    return fileLocation;
}

//返回文件后缀名
QString saveFileDialog::getFileFormat()
{
    return fileFormat;
}

void saveFileDialog::on_toolButton_clicked()
{
    QString fileName = QFileDialog::QFileDialog::getExistingDirectory(NULL,"caption",".");
    if(!fileName.isEmpty())
       fileLocation = fileName;
}
