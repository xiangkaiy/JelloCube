# JelloCube
Use OpenGL to emulate jel

OpenGL的配置，系统：Windows 10 ; IDE:Visual Studio 2010

1.glut.h复制到x:\Program Files\Microsoft\Visual Studio 10.0\VC\include\gl文件夹中,如果没有gl这个文件夹则可以自己新建一个。（x是你安装VS的盘符号）

2.glut.lib和glut32.lib放到静态函数库所在文件夹（即与include并排的lib文件夹下）

3.glut.dll和glut32.dll放到操作系统目录下面的system32文件夹内。（典型的位置为：C:\Windows\System32）

（注：如在开发应用程序时用到OpenGL辅助库函数，则还需下载相应动态链接库，包含glaux.dll, glaux.lib, glaux.h，相应步骤同上）
