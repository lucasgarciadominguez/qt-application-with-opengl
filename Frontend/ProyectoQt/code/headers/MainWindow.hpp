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
#include "RendererExample.hpp"
#include <memory>
#include <vector>
#include "EntityDLL.hpp" // Asegúrate de incluir la definición de EntityDLL
#include <string>
using namespace toolsDLL;

namespace esne
{

    class OpenGLWidget;
    /** Esta es la ventana principal de la aplicación. Es la que se abre directamente cuando esta
      * se inicia. Cuenta con una barra de menú y un widget central en el que se incrustan otros
      * widgets.
      */
    class MainWindow : public QMainWindow, public Ui::MiddlewarePracticaFinalClass
    {
        Q_OBJECT

    private:

        OpenGLWidget  * openglWidget;
        RendererExample renderer;
        int indexEntity = 0;

    public:

        /** Inicializa todos los widgets creados con QtDesigner e inserta el OpenGLWidget dentro
          * del widget 'placeholder' que ya está puesto. También conecta algunas señales con los
          * slots de la clase.
          */
        MainWindow(std::shared_ptr< std::vector<std::shared_ptr<toolsDLL::EntityDLL>>> entitiesDLL)
        {
            QMainWindow(nullptr);
            setupUi(this);
            setupOpenGLWidget();

            setWindowFlag(Qt::MSWindowsFixedSizeDialogHint, true);

            connect(actionExit, SIGNAL(triggered()), this, SLOT(menuExitTriggered()));
            //connect (xRotationSlider, SIGNAL(valueChanged(int)), this, SLOT(xRotationSliderChanged(int)));
            //connect (yRotationSlider, SIGNAL(valueChanged(int)), this, SLOT(yRotationSliderChanged(int)));
            //connect (zRotationSlider, SIGNAL(valueChanged(int)), this, SLOT(zRotationSliderChanged(int)));

            bool success = true;

            success = connect(xPosition, SIGNAL(valueChanged(double)), this, SLOT(xPositionChanged(double)));
            success = connect(yPosition, SIGNAL(valueChanged(double)), this, SLOT(yPositionChanged(double)));
            success = connect(zPosition, SIGNAL(valueChanged(double)), this, SLOT(zPositionChanged(double)));

            success = connect(xRotation, SIGNAL(valueChanged(double)), this, SLOT(xRotationChanged(double)));
            success = connect(yRotation, SIGNAL(valueChanged(double)), this, SLOT(yRotationChanged(double)));
            success = connect(zRotation, SIGNAL(valueChanged(double)), this, SLOT(zRotationChanged(double)));

            success = connect(xScale, SIGNAL(valueChanged(double)), this, SLOT(xScaleChanged(double)));
            success = connect(yScale, SIGNAL(valueChanged(double)), this, SLOT(yScaleChanged(double)));
            success = connect(zScale, SIGNAL(valueChanged(double)), this, SLOT(zScaleChanged(double)));

            success = connect(zScale, SIGNAL(valueChanged(double)), this, SLOT(zScaleChanged(double)));
            success = connect(zScale, SIGNAL(valueChanged(double)), this, SLOT(zScaleChanged(double)));

            for (const auto & entity : *entitiesDLL) {
                QString qstr = QString::fromStdString(entity->name);
                listObjects->addItem(qstr);
                //entity->
                
                //renderer.entities=emplace("../../assets/stanford-bunny.obj");
                //auto entityPtr = std::make_shared<toolsDLL::EntityDLL>(entity);
                //auto entityPtr = std::make_shared<toolsDLL::EntityDLL>(entity);

                renderer.entities.emplace_back(entity);

            }
            // Pasar los dos primeros elementos del vector entities a renderer.entities
            //if (entitiesDLL->size() > 0) {
            //    auto entityPtr1 = std::make_shared<toolsDLL::EntityDLL>(entitiesDLL->at(0));
            //    renderer.entities.emplace_back(std::make_shared<Entity>(entityPtr1));
            //}

            //if (entitiesDLL->size() > 1) {
            //    auto entityPtr2 = std::make_shared<toolsDLL::EntityDLL>(entitiesDLL->at(1));
            //    renderer.entities.emplace_back(entitiesDLL->at(1));
            //}

            success = connect(listObjects, SIGNAL(itemClicked(QListWidgetItem*)),
                this, SLOT(selectObject(QListWidgetItem*)));


            if (!success) {
                qDebug() << "Failed to connect signals and slots";
            }
            else {
                qDebug() << "Successfully connected signals and slots";
            }
        }
    public slots:

        /** Este método está conectado con la acción Exit del menú. Cierra la aplicación.
          */
        void menuExitTriggered ()
        {
            QApplication::quit ();
        }

        // Estos métodos están conectados con las señales que emiten los sliders:
        void xPositionChanged(double newValue);
        void yPositionChanged(double newValue);
        void zPositionChanged(double newValue);

        void xRotationSliderChanged (int newValue);
        void yRotationSliderChanged (int newValue);
        void zRotationSliderChanged (int newValue);

        void xRotationChanged(double newValue);
        void yRotationChanged(double newValue);
        void zRotationChanged(double newValue);


        void xScaleChanged(double newValue);
        void yScaleChanged(double newValue);
        void zScaleChanged(double newValue);

        void selectObject(QListWidgetItem* item);
        void RefreshUI(int index);

    private:

        /** Instancia el OpenGLWidget y lo inserta dentro del widget preexistente 'placeholder'.
          * El widget 'placeholder' se inserta en la ventana usando QtDesigner como ayuda para
          * poder ver/establecer dónde irá el OpenGLWidget, que no se puede usar en QtDesigner.
          */
        void setupOpenGLWidget ();
     
    };

}
