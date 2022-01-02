//
//  ViewController.m
//  Demo00-Triangle
//
//  Created by Cloud on 2021/12/6.
//

#import "ViewController.h"
//顶点结构体
typedef struct {
    GLKVector3 positionCoords;
} sceneVertex;
//三角形的三个顶点
static const sceneVertex vertices[] = {
    {{-0.5f,-0.5f,0.0}},
    {{0.5f,-0.5f,0.0}},
    {{-0.5f,0.5f,0.0}},
};
@interface ViewController ()
{
    //声明缓存ID属性
    GLint *vertexBufferID;
}
//声明一个GLKBaseEffect属性
@property (nonatomic,strong) GLKBaseEffect *baseEffect;
@end

@implementation ViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    //1.创建OpenGL ES上下文创建一个GLKViewController
    GLKView *view = (GLKView *)self.view;
    NSAssert([view isKindOfClass:[GLKView class]], @"ViewController's View is Not A GLKView");
    //创建OpenGL ES2.0上下文
    view.context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES2];
    //设置当前上下文
    [EAGLContext setCurrentContext:view.context];
    
    self.baseEffect = [[GLKBaseEffect alloc] init];
    //使用静态颜色绘制
    self.baseEffect.useConstantColor = GL_TRUE;
    //设置默认绘制颜色，参数分别是RGBA
    self.baseEffect.constantColor = GLKVector4Make(1.0f, 1.0f, 1.0f, 1.0f);
    //设置背景颜色为黑色
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    
    //生成缓存并绑定缓存数据
    /*
    glGenBuffers申请一个标识符
    glBindBuffer 将标识符绑定到GL_ARRAY_BUFFER
    glBufferData复制顶点数据从CPU到GPU
    */
    glGenBuffers(1, &vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);//绑定指定标识符的缓存为当前缓存
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}
-(void)glkView:(GLKView *)view drawInRect:(CGRect)rect{
    [self.baseEffect prepareToDraw];
    //Clear Frame Buffer
    glClear(GL_COLOR_BUFFER_BIT);
    //开启缓存
    glEnableVertexAttribArray(GLKVertexAttribPosition);
    //设置缓存数据指针
    glVertexAttribPointer(GLKVertexAttribPosition,
                          3,
                          GL_FLOAT,
                          GL_FALSE,//小数点固定数据是否被改变
                          sizeof(sceneVertex),
                          NULL);//从开始位置
    //绘图
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
-(void)dealloc{
    GLKView *view = (GLKView *)self.view;
    [EAGLContext setCurrentContext:view.context];
    if(0!= vertexBufferID){
        glDeleteBuffers(1, &vertexBufferID);
        vertexBufferID = 0;
    }
}
@end
