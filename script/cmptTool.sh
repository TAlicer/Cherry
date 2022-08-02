#!/bin/bash

#脚本运行根目录
PWD=`pwd`
ROOT="$(echo $PWD)"
DATE="$(date "+%Y-%m-%d")"

Generate_README()
{
echo -e \
"## 组件说明
在这里大概描述这个组件的用途，围绕以下几个问题展开描述
- 这个组件的用途
- 这个组件基于哪种语言与框架
- 这个组件适用于哪几种嵌入式平台
- 注意事项

## 目录说明
\`\`\`shell
$COMPNAME
├── Makefile            //打包生成库
├── README.md           //简要说明组件用途
├── demo                //演示组件库接口使用
│   ├── Makefile
│   └── src
├── docs                //存放组件相关文档
│   ├── 使用说明.html
│   ├── 使用说明.md
│   ├── 概要设计.doc
│   └── 详细设计.doc
├── include             //组件需要依赖的头文件
├── lib                 //组件需要依赖的库
├── src                 //组件源代码
├── test                //单元测试代码
├── third_party         //组件需要依赖的第三方源码
├── tools               //组件相关的工具，如脚本
└── output              //组件输出成果物
       └── gcc-arm-none-xxx                //交叉编译链
           └── $COMPNAME
               ├── include                 //对外提供头文件
               │   └── $COMPNAME
               │       └── $COMPNAME.h
               └── lib                     //对外提供封装库
                   └── lib$COMPNAME.a
\`\`\`

## 文档修订记录
| DATA       | ITEM | Brief    | Author    | Version  |
| ---------- | ---- | -------- | --------- | -------- |
| $DATE | NEW  | 文档创建 | \`$AUTHOR\` | \`V1.0.0\` |">> $COMPNAME/README.md
}

Generate_instruction()
{
echo -e \
"# $COMPNAME组件使用说明

[toc]

## 说明

这里描述组件使用方法，可能会用到哪些依赖库以及库的链接顺序，是否有自动化处理脚本以及它的使用方法


## 编译&安装

- make output	#编译生成相应的静态库
- 库文件和头文件会放到当前路径下的output目录
- 编译与安装的其他注意事项

\`\`\`shell
➜  output tree

└── output                              //组件输出成果物
    └── gcc-arm-none-xxx                //交叉编译链
         └── $COMPNAME
              ├── include               //对外提供头文件
              │   └── $COMPNAME
              │       └── $COMPNAME.h
              └── lib                   //对外提供封装库
                  └── lib$COMPNAME.a
\`\`\` 

## 接口说明
- 这里展示对外接口以及使用方法，例如：
\`\`\`cpp

/**
 * @brief 初始化Component adaptor组件
 *
 * @param 无
 *
 * @return 0：成功/-1：失败
 */
int Component_init();

\`\`\`

## 示例

这里描述demo的使用方法

# 版本更新说明

| DATA       | ITEM | Brief    | Author      | Version  |
| ---------- | ---- | -------- | ----------- | -------- |
| $DATE | NEW  | 初版创建 | \`$AUTHOR\` | \`V1.0.0\` |


# 文档修订记录

| DATA       | ITEM | Brief    | Author      | Version  |
| ---------- | ---- | -------- | ----------- | -------- |
| $DATE | NEW  | 文档创建 | \`$AUTHOR\` | \`V1.0.0\` |">> $COMPNAME/docs/使用说明.md
}

Generate_Mikefile_lib()
{
echo -e \
"SHELL=/bin/bash

# 想要生成的组件库名称
TARGET_LIB_A := lib$COMPNAME.a

# 需要打包的头文件
SRC_INC :=	./src/$COMPNAME.h

# 交叉编译链
CROSS_COMPILE=arm-linux-gnueabihf-
CC=\$(CROSS_COMPILE)gcc
CXX=\$(CROSS_COMPILE)g++
AR=\$(CROSS_COMPILE)ar

# 最终存放库文件和头文件的目录
OUTPUT_INC := ./output/\$(CROSS_COMPILE)/include/$COMPNAME
OUTPUT_LIB := ./output/\$(CROSS_COMPILE)/lib
OUTPUT:= ./output/\$(CROSS_COMPILE)/{include/$COMPNAME/,lib/}

# C/C++编译选项
CFLAGS := -Wall -Werror
CXXFLAGS :=

# 需要编译的源代码目录
SRC_DIR:= ./src

# 需要编译的源代码文件格式
SFIX:=  .c .cpp

# 编译时指定的头文件路径
INCLUDES := -I./src

#------------------------以上内容为配置项---------------------------------

# 得到源代码目录下的所有源代码文件
SOURCES := \$(foreach x,\${SRC_DIR},\\
			\$(wildcard \\
			\$(addprefix  \${x}/*,\${SFIX})))

# 去掉扩展名，再追加.o的扩展名，得到依赖文件名集合 (带路径)
OBJS_FILE := \$(addsuffix .o ,\$(basename \${SOURCES}))

# 1、先清理不必要的文件
# 2、生成库文件
all : clean \$(TARGET_LIB_A)
	@mkdir -p \$(OUTPUT)				#创建存放成果物的目录
	mv \$(TARGET_LIB_A) \$(OUTPUT_LIB)		#拷贝生成的库文件
	cp \$(SRC_INC) \$(OUTPUT_INC)			#拷贝头文件
	
\$(TARGET_LIB_A) : \$(OBJS_FILE)
	@\$(AR)  -rcs \$@ \$^
	@echo -e \"AR	\$@\"
	@rm -f \$(OBJS_FILE)

%.o : %.c
	@\$(CC) \$(INCLUDES) -c $< -o \$@ \$(CFLAGS)
	@echo -e \"CC	$<\"
%.o : %.cpp
	@\$(CXX) \$(INCLUDES) -c $< -o \$@ \$(CXXFLAGS)
	@echo -e \"CPP	$<\"

.PHONY: clean
clean:
	@rm -f  \$(OBJS_FILE)
	@rm -rf ./output">> $COMPNAME/Makefile
}

Generate_Mikefile_demo()
{
echo -e \
"SHELL=/bin/bash

# 想要生成的可执行文件名称
DEMO:= demo

# 交叉编译链
CROSS_COMPILE=arm-linux-gnueabihf-
CC=\$(CROSS_COMPILE)gcc
CXX=\$(CROSS_COMPILE)g++

# C/C++编译选项
CFLAGS :=
CXXFLAGS := -Wall -Werror

# 需要编译的源代码目录
SRC_DIR:= ./src 

# 需要编译的源代码文件格式
SFIX:= .c .cpp

# 指定编译时的头文件路径
INCLUDES := -I../include -I../output/\$(CROSS_COMPILE)/include

# 指定需要链接库的路径
LIB := -L../output/\$(CROSS_COMPILE)/lib

#指定需要链接的库
LINK := -l$COMPNAME

#------------------------以上内容为配置项---------------------------------

# 得到源代码目录下的所有源代码文件
SOURCES := \$(foreach x,\${SRC_DIR},\\
			\$(wildcard \\
			\$(addprefix  \${x}/*,\${SFIX})))

#去掉扩展名，再追加.o的扩展名，得到依赖文件名集合 (带路径)
OBJS_FILE := \$(addsuffix .o ,\$(basename \${SOURCES}))

# 1、先清理不必要的文件
# 2、生成库文件
# 3、生成可执行文件
all : clean  mklib \$(DEMO)
	
\$(DEMO) : \$(OBJS_FILE)
	@\$(CXX) \$(INCLUDES) -o \$@ \$^ \$(LIB) \$(LINK) \$(CXXFLAGS)
	@echo -e \"Generate \$(DEMO)\"
	@rm -f \$(OBJS_FILE)

%.o : %.c
	@\$(CC) \$(INCLUDES) -c $< -o \$@ \$(CFLAGS)
	@echo -e \"CC	$<\"
%.o : %.cpp
	@\$(CXX) \$(INCLUDES) -c $< -o \$@ \$(CXXFLAGS)
	@echo -e \"CPP	$<\"

.PHONY: mklib
mklib:
	make -C ../ CROSS_COMPILE=\$(CROSS_COMPILE)
	
.PHONY: clean
clean:
	@rm -f \$(OBJS_FILE)
	@rm -f \${DEMO}">> $COMPNAME/demo/Makefile
}

Generate_config_file()
{
	Generate_README
	Generate_instruction
	Generate_Mikefile_lib
	Generate_Mikefile_demo
}

#-----------------------脚本从这里开始执行--------------------------------

echo -e "Please input Component_name:\c "
read COMPNAME
echo -e "Please input Author_name:\c "
read AUTHOR

rm -rf $COMPNAME && mkdir -p $COMPNAME/{demo/src,docs,include,lib,src,test,third_party,tools}

Generate_config_file

echo -e "Successfully generated $COMPNAME"
