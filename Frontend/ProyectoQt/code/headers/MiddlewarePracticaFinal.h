
/**********************************************************************
*Project           : First Practice Middleware
*
*Author : Lucas García
*
*
*Purpose : Connects Backend Tool Engine (.dll) to a QT scene loader called MiddlewarePracticaFinal(.exe)
*
**********************************************************************/
#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_MiddlewarePracticaFinal.h"
class MiddlewarePracticaFinal : public QMainWindow
{
    Q_OBJECT

public:
    MiddlewarePracticaFinal(QWidget *parent = nullptr);
    ~MiddlewarePracticaFinal();

private:
    Ui::MiddlewarePracticaFinalClass ui;
};
