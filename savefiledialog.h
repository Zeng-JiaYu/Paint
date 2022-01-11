#ifndef SAVEFILEDIALOG_H
#define SAVEFILEDIALOG_H

#include <QDialog>
#include <QString>
#include <QFileDialog>

using namespace std;

namespace Ui {
class saveFileDialog;
}

class saveFileDialog : public QDialog
{
    Q_OBJECT
private slots:
    //设置文件名
    void on_fileName_textEdited(const QString &name);
    //设置文件地址
    void on_filelLocation_textEdited(const QString &location);
    //设置文件后缀名
    void on_nameSuffix_currentIndexChanged(const QString &name);
    void on_toolButton_clicked();

public:
    explicit saveFileDialog(QWidget *parent = nullptr);
    QString getFileName();
    QString getFileLocation();
    QString getFileFormat();
    ~saveFileDialog();

private:
    Ui::saveFileDialog *ui;
    QString fileName;
    QString fileLocation;
    QString fileFormat;
};

#endif // SAVEFILEDIALOG_H
