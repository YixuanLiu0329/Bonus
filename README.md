# 工作说明

## 1. GSL(under Ubuntu)

**Step1 源代码`.c`**
* 从文件`spring_data.csv`中读取数据；
* 将数据存放到数组`x[],y[]`中；
* 利用`gsl`进行拟合，并输出结果；
* 利用`gnuplot`对数据进行可视化。

**Step2 makefile**<br>
通过makefile生成可执行文件。
```makefile
CC=gcc

SRCDIR=./src/
OBJDIR=./obj/

all: maingsl

clean:
	rm -f ./gslspringdata

maingsl: fileobj
	$(CC) -o gslspringdata $(OBJDIR)gslspringdata.o -lgsl -lgslcblas -lm
	rm -f  ./obj/*.o

fileobj:  
	$(CC) -c -o $(OBJDIR)gslspringdata.o $(SRCDIR)gslspringdata.c
```

**Step3 生成可执行文件并执行**<br>
输入命令`make -f makefile.mk`，生成可执行文件，运行后有以下结果<br>
![makefile运行结果](./img/makefile.png)

**Step4 运行可执行文件**<br>
输入命令`./gslspringdata`，有以下结果：<br>
![可执行文件](./img/gslexe.png)<br>
同时获得可视化数据：<br>
![数据可视化](./img/gsl.png)


## 2. Gbuplot(under Ubuntu)
编辑`spring.plt`程序，输入命令`gnuplot -persist ./spring.plt`，即可对数据进行可视化。<br>
![命令运行结果](./img/gnuplot1.png)
![数据可视化](./img/gnuplot2.png)


## 3. Version control with Git,Github(under Windows)

**Step1 配置账户**<br>
![配置账户](./img/connectaccount.PNG)

**Step2 初始化**  <br>
初始化前，现在github中建立与本地文件夹名字相同的仓库。新建时不要包含`README.md`。<br>
![初始化](./img/initialization.PNG)

**Step3 更新仓库**<br>
第一次更新，需要登陆Github账户:<br>
![Github账户登录](./img/githublogin.PNG)<br>
第一次对仓库进行更新：<br>
![更新仓库](./img/firstpush.PNG)<br>
更新后的仓库：<br>
![第一次更新](./img/r1.PNG)

**Step4 再次更新**<br>
编辑好`README.md`文件，再次对仓库进行更新。<br>
![再次更新](./img/r2.PNG)