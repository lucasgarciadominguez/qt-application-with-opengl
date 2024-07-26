/**********************************************************************
*Project           : First Practice Middleware
*
*Author : Lucas García
*
*
*Purpose : Connects Backend Tool Engine (.dll) to a QT scene loader called MiddlewarePracticaFinal(.exe)
*
**********************************************************************/

#include "MiddlewarePracticaFinal.h"
#include <QtWidgets/QApplication>
#include "MainWindow.hpp"
#include "Controller.hpp"
#include "Scene.hpp"
#include "EntityDLL.hpp"
using namespace toolsDLL;
using namespace esne;

int main(int argc, char *argv[])
{
    std::shared_ptr<Scene> scene=std::make_shared<Scene>();
    Controller controller(*scene);
    QApplication a(argc, argv);
    std::shared_ptr<esne::MainWindow> window=std::make_shared<esne::MainWindow>(scene->getEntities());
    window->show();
    return a.exec();
}
