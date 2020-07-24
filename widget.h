#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <Eigen/Dense>

class Widget : public QWidget{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    Eigen::MatrixXd readCsvToMat(QString path);
};
#endif // WIDGET_H
