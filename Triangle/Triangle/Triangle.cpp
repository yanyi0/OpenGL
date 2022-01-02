//
//  Triangle.cpp
//  Triangle
//
//  Created by Cloud on 2022/1/2.
//

#include <stdio.h>
#include <GLTools.h>  //OpenGL toolkit
#include <GLShaderManager.h>//Shader Manager Class
#ifdef __APPLE__
#include <glut/glut.h> //OS X version of GLUT
#else
#define FREEGLUT_STATIC
#include <GL/glut.h> //Windows FreeGlut equivalent
#endif

GLBatch triangleBatch;
GLShaderManager shaderManager;
//Window has changed size, or has just been created. In either case, we need to use the window dimensions to set the viewport and projection matrix.
void ChangeSize(int w,int h){
//    printf("视口宽:%d,视口高:%d", w,h);
    glViewport(0, 0, w/2, h/2);
}
//This function does any needed initialization on the rendering context.
//This is the first opportunity to do any OpenGL related tasks.
void SetupRC(){
    //Blue background
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    
    shaderManager.InitializeStockShaders();
    //Load up a triangle
    
    GLfloat vVerts[] = {
      -0.5f,0.0f,0.0f,
       0.5f,0.0f,0.0f,
       0.0f,0.5f,0.0f,
    };
    
    triangleBatch.Begin(GL_TRIANGLES, 3);
    triangleBatch.CopyVertexData3f(vVerts);
    triangleBatch.End();
}
//Called to draw scene
void RenderScene(void){
    //Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    GLfloat vRed[] = {1.0f,0.0f,0.0f,1.0f};
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY,vRed);
    triangleBatch.Draw();
    
    //Perform the buffer swap to display the back buffer
    glutSwapBuffers();
}
//Main entry point for GLUT based programs
int main(int argc,char* argv[]){
    //设置当前工作目录
    gltSetWorkingDirectory(argv[0]);
    //传输命令行参数并初始化GLUT库
    glutInit(&argc, argv);
    //创建窗口使用哪种类型显示模式，双缓冲串口和RGBA颜色模式
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_STENCIL);
    //窗口大小
    glutInitWindowSize(800, 600);
    //窗口标题
    glutCreateWindow("Triangle");
    //窗口改变大小回调函数，以便能够设置视点
    glutReshapeFunc(ChangeSize);
    //注册函数包含OpenGL渲染代码
    glutDisplayFunc(RenderScene);
    //初始化GLEW库，初始化驱动程序中所有丢失的入口点，确保OpenGL API可用
    GLenum err = glewInit();
    if (GLEW_OK != err) {
        fprintf(stderr, "GLEW Error: %s\n",glewGetErrorString(err));
        return 1;
    }
    //渲染环境，运行中的OpenGL状态机的句柄
    SetupRC();
    //开启主消息循环并结束main函数
    glutMainLoop();
    return 0;
}
