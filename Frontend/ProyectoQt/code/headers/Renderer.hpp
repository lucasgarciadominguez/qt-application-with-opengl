
// Este código es de dominio público.
// angel.rodriguez@esne.edu
// 2023.05

#pragma once

namespace esne
{

    /** Esta "interfaz" es la que usa la clase OpenGLWidget (implementada en este proyecto) para
      * delegar el uso de OpenGL. OpenGLWidget llama a los métodos de esta interfaz automáticamente
      * en los momentos que resulte oportuno.
      * Esta interfaz la debe implementar alguna clase que maneje OpenGL pasivamente (cuando se
      * invoquen estos métodos reimplementados).
      * El sentido de esta interfaz es permitir separar el código que gestiona el widget de OpenGL
      * y otros detalles dependientes de Qt del código que hace uso de OpenGL, que puede ser más
      * genérico. Así se puede evitar que tenga dependencias con Qt y reusarlo en otros proyectos.
      * Esta interfaz actúa como puente entre el widget de Qt y el código genérico de OpenGL.
      */
    class Renderer
    {
    public:

        virtual ~Renderer() = default;

        /** Este método se invoca cuando el contexto de OpenGL ya se ha creado y se pueden empezar
          * a realizar llamadas de OpenGL (pero no se puede dibujar), antes de que se invoque a
          * resizeGL() o paintGL().
          */
        virtual void initialize () = 0;

        /** Este método se invoca cuando se debe dibujar el contenido del widget. El resultado del
          * render va a un framebuffer que Qt se encargará de volcar a la ventana.
          */
        virtual void resize (int new_viewport_width, int new_viewport_height) = 0;

        /** Este método se invoca si el framebuffer cambia de tamaño para que se ajuste el tamaño
          * del viewport y la matriz de proyección.
          */
        virtual void render () = 0;

    };

}
