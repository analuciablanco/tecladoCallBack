#pragma region LIBRERÍAS
// PlantillaOpenGL.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

// Se usan <> para librerías que ya trae el sistema.
// GLEW y GLFW dependen de estas dos librerías, por eso se ponen antes de llamar al GLEW_STATIC.
#include <stdio.h>
#include <stdlib.h>

#define GLEW_STATIC

// Se usan "" para librerías personalizadas.
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include <iostream>

using namespace std;
#pragma endregion

#pragma region VARIABLES
// Declaramos apuntador de ventana.
GLFWwindow *window;

float xTriangulo = 0.0f;
float yTriangulo = 0.0f;

float velocidad = 0.025f;

float angulo = 0.0f;

#pragma endregion

#pragma region FUNCIONES PARA RUTINA DE DIBUJO
void dibujarTriangulo() {
	// Utilizar matriz identidad.
	glPushMatrix();

		glTranslatef(xTriangulo, yTriangulo, 0.0f);
		glRotatef(angulo, 0.7f, 1.0f, 1.0f);

		//Dibujar los vertices
		glBegin(GL_TRIANGLES);

		glColor3f(1.0f, 0.8f, 0.0f);

		glVertex3f(-0.2f, -0.2f, 0);
		glVertex3f(0.2f, -0.2f, 0);
		glVertex3f(0.0f, 0.2f, 0);

		glEnd();

	// Soltar la matriz.
	glPopMatrix();
}

void dibujar() {
	dibujarTriangulo();
}

//Esto es para realizar movimiento por ESTADO
void moverTriangulo() {
	int estadoTeclaDerecha = glfwGetKey(window, GLFW_KEY_RIGHT);
	if (estadoTeclaDerecha == GLFW_PRESS)
	{
		xTriangulo += velocidad;
	}

	int estadoTeclaIzquierda = glfwGetKey(window, GLFW_KEY_LEFT);
	if (estadoTeclaIzquierda == GLFW_PRESS)
	{
		xTriangulo -= velocidad;
	}

	int estadoTeclaArriba = glfwGetKey(window, GLFW_KEY_UP);
	if (estadoTeclaArriba == GLFW_PRESS)
	{
		yTriangulo += velocidad;
	}

	int estadoTeclaAbajo = glfwGetKey(window, GLFW_KEY_DOWN);
	if (estadoTeclaAbajo == GLFW_PRESS)
	{
		yTriangulo -= velocidad;
	}
}

void actualizar() {
	moverTriangulo();
}

// Esto es para realizar movimiento por EVENTO
void teclado_callback(GLFWwindow *window, int key, int scancode, int action, int mods) 
{	
	if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		xTriangulo += velocidad;
	}

	if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		xTriangulo -= velocidad;
	}

	if (key == GLFW_KEY_UP && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		yTriangulo += velocidad;
	}

	if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS || action == GLFW_REPEAT))
	{
		yTriangulo -= velocidad;
	}
}
#pragma endregion

int main()
{
#pragma region CREAR UN CONTEXTO
	// Un contexto es una ventana de un sistema operativo.
	// OpenGL no gestiona el uso de ventanas.

	// Condicionamos en caso de no poder iniciar el GLFW.
	if (!glfwInit()) 
		exit(EXIT_FAILURE);

	// Si GLFW puede iniciar entonces inicia la ventana.
	window = glfwCreateWindow(1024, 768, "Ventana", NULL, NULL);

	// Si puede iniciar GLFW pero no la ventana terminamos la ejecución.
	if (!window) {
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// Establecemos el contexto, donde se mandarán los pixeles generados.
	glfwMakeContextCurrent(window);

	// Una vez establecido el contexto activamos funciones modernas.
	glewExperimental = true;
	GLenum errorGlew = glewInit();

	if (errorGlew != GLEW_OK)
	{
		cout << glewGetErrorString(errorGlew);
	}
#pragma endregion

	const GLubyte *versionGL = glGetString(GL_VERSION);
	cout << "Version OpenGL: " << versionGL;

	//glfwSetKeyCallback(window, teclado_callback);

#pragma region CICLO DE DIBUJO (DRAW LOOP)
	//El while establece que mientras la ventana esté abierta realice lo de su interior.
	while (!glfwWindowShouldClose(window)){
		// Establecemos región de dibujo.
		glViewport(0, 0, 1024, 768);
		// Establecemos color de borrado.
		glClearColor(0.5, 0, 0.5, 1);
		// Borramos.
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Rutina de dibujo.
		dibujar();
		actualizar();

		// Cambiar los buffers.
		glfwSwapBuffers(window);
		// Reconocer si hay entradas.
		glfwPollEvents();
	}

	// Para destruir ventana y borrarlo/liberarlo de la memoria.
	glfwDestroyWindow(window);
	glfwTerminate();
#pragma endregion

    return 0;
}

