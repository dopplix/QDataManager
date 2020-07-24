#include "widget.h"
#include <QtConcurrentMap>
#include <QFuture>
#include <QFutureWatcher>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>
#include <QElapsedTimer>

#include <QFile>
#include <QRegularExpression>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>

Widget::Widget(QWidget *parent) : QWidget(parent){
    QString path=":/csv/kidis5.csv";
    Eigen::MatrixXd mat = readCsvToMat(path);
    QVBoxLayout* layout = new QVBoxLayout;
    QTableWidget* table = new QTableWidget;
    int nRow = mat.rows();
    int nCol = mat.cols();
    table->setRowCount(nRow);
    table->setColumnCount(nCol);
    for(int i=0;i<nRow;i++){
        for(int j=0;j<nCol;j++){
            QString valueStr = QString::number(mat(i,j));
            QTableWidgetItem* item = new QTableWidgetItem(valueStr);
            table->setItem(i,j,item);
        }
    }
    layout->addWidget(table);
    this->setLayout(layout);
}
Widget::~Widget(){

}
Eigen::MatrixXd Widget::readCsvToMat(QString path){
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QString text = file.readAll();
    file.close();
    QStringList lines = text.split(QRegularExpression{R"-((\r\n?|\n))-"});
    lines.removeAll("");
    int nRow = lines.size();
    int nCol = lines.at(0).split(",").size();
    Eigen::MatrixXd mat(nRow,nCol);
    for(int i=0;i<nRow;i++){
        QString line = lines.at(i);
        QStringList values = line.split(",");
        for(int j=0;j<nCol;j++){
            QString value = values.at(j);
            mat(i,j)=value.toDouble();
        }
    }
    return mat;
}

