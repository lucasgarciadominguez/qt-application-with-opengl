
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2023.05

#include "OpenGLWidget.hpp"

namespace esne
{

    OpenGLWidget::OpenGLWidget(QWidget * parent, Renderer & renderer)
    :
        QOpenGLWidget(parent  ),
        renderer     (renderer)
    {
        // Se establecen algunos detalles de formato para el contexto de OpenGL:
        // Este código se debe ejecutar antes de que la ventana o el propio widget sean visibles.

        QSurfaceFormat format;

        format.setDepthBufferSize (24);                     // El valor 24 es más compatible con GPUs antiguas que 32
        format.setVersion (3, 3);                           // OpenGL 3.3
        format.setProfile (QSurfaceFormat::CoreProfile);    // Core Profile

        setFormat (format);
    }

}
