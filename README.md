# MoonOS

MoonOS 是一个用isolinux引导的tony OS  
大家可以随意改动里面的部分来进行操作系统实验  
尝试控制硬件、管理内存和硬盘  

使用了nasm汇编器，如果没有的话，在linux下请先运行：  
	sudo apt-get install nasm

使用gcc和ld进行编译和链接，有跨平台开发需要的，请自行修改makefile  

目前只打算开发x86架构下的部分  
makefile的配置文件也放置在src/x86/config.make  

目录结构：
```
	MoonOS  
	| -- build  构建目录，用来存放编译时所有的临时文件  
	| -- cdiso  iso光盘映像构建目录  
		| -- isolinux  isolinux工具及配置目录  
		| -- moon  编译好的内核二进制文件  
	| -- src  
		| -- boot  启动脚本  
		| -- kernel  内核文件  
		| -- x86  x86架构下的系统启动程序  
```


