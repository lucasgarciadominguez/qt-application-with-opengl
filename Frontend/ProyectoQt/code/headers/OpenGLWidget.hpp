
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

#include <QOpenGLWidget>
#include "Renderer.hpp"

namespace esne
{

    /** Para poder gestionar lo que se dibuja con OpenGL Qt ofrece varias posibilidades y la más
      * conveniente es especializar mediante herencia la clase QOpenGLWidget. Ello nos permite
      * configurar el contexto de OpenGL (initializeGL), determinar cuándo es conveniente
      * redimensionar el viewport (resizeGl) y coordinar el momento adecuado para realizar el
      * render (paintGL).
      * Esta clase no aparecerá como widget usabe en QtDesigner, por lo que parece que no queda
      * otra que agregarlo manualmente a la ventana donde deba estar.
      * En general es recomendable separar el código en grupos de clases, librerías, etc. cuando
      * sea conveniente y, en este caso, es conveniente separar el código de Qt del código de
      * OpenGL, ya que este se podría usar en otros proyectos sin Qt. Por ello, esta clase delega
      * casi todo el trabajo a una "interfaz" Renderer que no tiene por qué usar Qt.
      */
    class OpenGLWidget : public QOpenGLWidget
    {
    private:

        Renderer & renderer;

    public:

        /** En el constructor se configura el formato requerido para el contexto de OpenGL.
          */
        OpenGLWidget(QWidget * parent, Renderer & renderer);

        /** Este método lo invoca automáticamente Qt cuando el contexto de OpenGL ya se ha creado
          * y se pueden empezar a realizar llamadas de OpenGL (pero no se puede dibujar), antes
          * de que se invoque a resizeGL() o paintGL().
          */
        void initializeGL () override
        {
            renderer.initialize ();
        }

        /** Este método lo invoca automáticamente Qt cuando se debe dibujar el contenido del widget.
          * El resultado del render va a un framebuffer que Qt se encargará de volcar a la ventana.
          */
        void paintGL () override
        {
            renderer.render ();
        }

        /** Si el tamaño del widget cambia Qt invoca a este método automático para que se ajuste
          * el tamaño del viewport y la matriz de proyección.
          */
        void resizeGL (int width, int height) override
        {
            renderer.resize (width, height);
        }

    };

}
