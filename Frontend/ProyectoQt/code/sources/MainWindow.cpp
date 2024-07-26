/**********************************************************************
*Project           : First Practice Middleware
*
*Author : Lucas García
*
*
*Purpose : Connects Backend Tool Engine (.dll) to a QT scene loader called MiddlewarePracticaFinal(.exe)
*
**********************************************************************/

#include "MainWindow.hpp"
#include "OpenGLWidget.hpp"
#include "EntityDLL.hpp"
#include <vector>
#include <memory>

using namespace std;
using namespace toolsDLL;
namespace esne
{

    void MainWindow::xRotationSliderChanged (int newValue)
    {
        renderer.setRotationX (6.2831853f * newValue / 100.f,indexEntity);

        openglWidget->update ();
    }

    void MainWindow::yRotationSliderChanged (int newValue)
    {
        renderer.setRotationY (6.2831853f * newValue / 100.f, indexEntity);

        openglWidget->update ();
    }

    void MainWindow::zRotationSliderChanged (int newValue)
    {
        renderer.setRotationZ (6.2831853f * newValue / 100.f, indexEntity);

        openglWidget->update ();
    }
    void MainWindow::xRotationChanged(double newValue)
    {
        renderer.setRotationX(newValue, indexEntity);

        openglWidget->update();
    }

    void MainWindow::yRotationChanged(double newValue)
    {
        renderer.setRotationY(newValue, indexEntity);

        openglWidget->update();
    }

    void MainWindow::zRotationChanged(double newValue)
    {
        renderer.setRotationZ(newValue, indexEntity);

        openglWidget->update();
    }
    void MainWindow::setupOpenGLWidget ()
    {
        openglWidget = new OpenGLWidget(placeholder, renderer);

        openglWidget->setFixedSize (placeholder->size ());
    }


    void MainWindow::xPositionChanged(double newValue)
    {
        renderer.setPositionX(newValue, indexEntity);

        openglWidget->update();
    }
    void MainWindow::yPositionChanged(double newValue)
    {
        renderer.setPositionY(newValue, indexEntity);

        openglWidget->update();
    }
    void MainWindow::zPositionChanged(double newValue)
    {
        renderer.setPositionZ(newValue, indexEntity);

        openglWidget->update();
    }

    void MainWindow::xScaleChanged(double newValue)
    {
        renderer.setScaleX(newValue, indexEntity);

        openglWidget->update();
    }
    void MainWindow::yScaleChanged(double newValue)
    {
        renderer.setScaleY(newValue, indexEntity);

        openglWidget->update();
    }
    void MainWindow::zScaleChanged(double newValue)
    {
        renderer.setScaleZ(newValue, indexEntity);

        openglWidget->update();
    }

    void MainWindow::selectObject(QListWidgetItem* item)
    {
        indexEntity=listObjects->row(item); 
        RefreshUI(indexEntity);

    }
    void MainWindow::RefreshUI(int index)
    {
        xPosition->setValue(renderer.entities.at(index).entityBackEnd->getTransform().position.x);
        yPosition->setValue(renderer.entities.at(index).entityBackEnd->getTransform().position.y);
        zPosition->setValue(renderer.entities.at(index).entityBackEnd->getTransform().position.z);

        xRotation->setValue(renderer.entities.at(index).entityBackEnd->getTransform().rotation.x);
        yRotation->setValue(renderer.entities.at(index).entityBackEnd->getTransform().rotation.y);
        zRotation->setValue(renderer.entities.at(index).entityBackEnd->getTransform().rotation.z);

        xScale->setValue(renderer.entities.at(index).entityBackEnd->getTransform().scale.x);
        yScale->setValue(renderer.entities.at(index).entityBackEnd->getTransform().scale.y);
        zScale->setValue(renderer.entities.at(index).entityBackEnd->getTransform().scale.z);
    }

}
