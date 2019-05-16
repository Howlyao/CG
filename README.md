# Visual Studio环境配置
->项目属性->VC++目录
包含目录
增添 ./OpenGL/Includes;
库目录
增添 ./OpenGL/Libs;

->项目属性->链接器->输入
附加依赖项
增添 opengl32.lib;glfw3.lib;assimp.lib;freetype.lib;


运行
Debug x86
