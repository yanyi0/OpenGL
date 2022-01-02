//
//  Move.cpp
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

GLBatch squareBatch;
GLShaderManager shaderManager;
GLfloat blockSize = 0.1f;
GLfloat vVerts[] = {
    -blockSize,-blockSize,0.0f,
    blockSize,-blockSize,0.0f,
    blockSize,blockSize,0.0f,
    -blockSize,blockSize,0.0f};

void SpecialKeys(int key,int x,int y){
    GLfloat stepSize = 0.025f;
    GLfloat blockX = vVerts[0];//Upper left X
    GLfloat blockY = vVerts[7];//Upper left Y
    
    if (key == GLUT_KEY_UP) {
        blockY += stepSize;
    }
    
    if (key == GLUT_KEY_DOWN) {
        blockY -= stepSize;
    }
    
    if (key == GLUT_KEY_LEFT) {
        blockX -= stepSize;
    }
    
    if (key == GLUT_KEY_RIGHT) {
        blockX += stepSize;
    }
    
    //Collision detection
    if (blockX < -1.0f) blockX = -1.0f;
    if (blockX > (1.0f - blockSize * 2)) blockX = 1.0f -blockSize * 2;
    if (blockY < -1.0f + blockSize * 2) blockY = -1.0f + blockSize * 2;
    if (blockY > 1.0f) blockY = 1.0f;
    
    //Recalculate vertex positions
    vVerts[0] = blockX;
    vVerts[1] = blockY - blockSize * 2;
    
    vVerts[3] = blockX + blockSize * 2;
    vVerts[4] = blockY - blockSize * 2;
    
    vVerts[6] = blockX + blockSize*2;
    vVerts[7] = blockY;
    
    vVerts[9] = blockX;
    vVerts[10] = blockY;
    
    squareBatch.CopyVertexData3f(vVerts);
    
//    glutPostRedisplay();
}
//Window has changed size, or has just been created. In either case, we need to use the window dimensions to set the viewport and projection matrix.
void ChangeSize(int w,int h){
    printf("视口宽:%d,视口高:%d", w,h);
    glViewport(0, 0, w, h);
}
//This function does any needed initialization on the rendering context.
//This is the first opportunity to do any OpenGL related tasks.
void SetupRC(){
    //Blue background
    glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
    
    shaderManager.InitializeStockShaders();
    //Load up a square
    
    squareBatch.Begin(GL_TRIANGLE_FAN, 4);
    squareBatch.CopyVertexData3f(vVerts);
    squareBatch.End();
}
//Called to draw scene
void RenderScene(void){
    //Clear the window with current clearing color
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
    GLfloat vRed[] = {1.0f,0.0f,0.0f,1.0f};
    shaderManager.UseStockShader(GLT_SHADER_IDENTITY,vRed);
    squareBatch.Draw();
    
    //Perform the buffer swap to display the back buffer
    glutSwapBuffers();
    
    glutPostRedisplay();
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
    glutCreateWindow("Move Block with Arrow Keys");
    //窗口改变大小回调函数，以便能够设置视点
    glutReshapeFunc(ChangeSize);
    //注册函数包含OpenGL渲染代码
    glutDisplayFunc(RenderScene);
    glutSpecialFunc(SpecialKeys);
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
