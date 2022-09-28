#/******************************************************************************
# @file:   makefile
# @brief:  makefile基础函数的说明与使用示例
#
# @author: wangtao <TAlicer@163.com>
# @date:   2022/09/28
#
#*****************************************************************************/

#>>>----------------------------------------函数定义---------------------------------

#$(subst <from>,<to>,<text>)
#名称：字符串替换函数——subst。
#功能：把字串<text>中的<from>字符串替换成<to>。
#返回：函数返回被替换过后的字符串。
#test_subst:comma为局部变量，comma只能在test_subst目标中生效
test_subst:comma:= ,
test_subst:empty:=
test_subst:space:= $(empty) $(empty)
test_subst:foo:= a b c
test_subst:bar:= $(subst $(space),$(comma),$(foo))
define test_subst
	@echo "$(bar)"
endef

#$(patsubst <pattern>,<replacement>,<text>)
#名称：模式字符串替换函数——patsubst。
#功能：查找<text>中的单词（单词以“空格”、“Tab”或“回车”“换行”分隔）是否符合模式<pattern>，如果匹配的话，则以<replacement>替换。
#      这里，<pattern>可以包括通配符%，表示任意长度的字串。如果<replacement>中也包含%，那么，中的这个%将是<pattern>中的那个%所代表的字串。
#     （可以用\来转义，以\%来表示真实含义的%字符）
#返回：函数返回被替换过后的字符串。
define test_patsubst
	@echo "$(patsubst %.c,%.o,x.c.c patsubst.c)"
	@echo "$(patsubst \%.c,\%.o,x.c.c %.c patsubst.c)"
endef

#$(strip <string>)
#名称：去空格函数——strip。
#功能：去掉<string>字串中开头和结尾的空字符。
#返回：返回被去掉空格的字符串值。
test_strip:empty:=
test_strip:string:= $(empty) $(empty) a b c    
define test_strip
	@echo "[$(string)]"
	@echo "[$(strip $(string))]"
endef

#$(findstring <find>,<in>)
#名称：查找字符串函数——findstring。
#功能：在字串<in>中查找<find>字串。
#返回：如果找到，那么返回<find>，否则返回空字符串。
define test_findstring
	@echo "$(findstring a,a b c)"
	@echo "$(findstring a,b c)"
endef

#$(filter <pattern...>,<text>)
#名称：过滤函数——filter。
#功能：以<pattern>模式过滤<text>字符串中的单词，保留符合模式<pattern>的单词。可以有多个模式。
#返回：返回符合模式<pattern>的字串。
test_filter:sources:= foo.c dds.o baz.s ugh.h
define test_filter
	@echo "$(filter %.c %.s,$(sources))"
endef

#$(filter-out <pattern...>,<text>)
#名称：反过滤函数——filter-out。
#功能：以<pattern>模式过滤<text>字符串中的单词，去除符合模式<pattern>的单词。可以有多个模式。
#返回：返回不符合模式<pattern>的字串。
test_filter-out:sources:= foo.c dds.o baz.s ugh.h
define test_filter-out
	@echo "$(filter-out %.c %.s,$(sources))"
endef

#$(sort <list>)
#名称：排序函数——sort。
#功能：给字符串<list>中的单词排序（升序）, 单词按首字母排序，数值按第一个数字排序。
#返回：返回排序后的字符串
#备注：sort函数会去掉<list>中相同的单词。
test_sort:sources:= 189 457 231 231 banana apple orange
define test_sort
	@echo "$(sort $(sources))"
endef

#$(word <n>,<text>)
#名称：取单词函数——word。
#功能：取字符串<text>中第<n>个单词。（从一开始）
#返回：返回字符串<text>中第<n>个单词。如果<n>比<text>中的单词数要大，那么返回空字符串。
test_word:sources:= 189 457 231 banana apple orange
define test_word
	@echo "$(word 4,$(sources))"
endef

#$(wordlist <s>,<e>,<text>) 
#名称：取单词串函数——wordlist。
#功能：从字符串<text>中取从<s>开始到<e>的单词串。<s>和<e>是一个数字。
#返回：返回字符串<text>中从<s>到<e>的单词字串。如果<s>比<text>中的单词数要大，那么返回空字符串。
#      如果<e>大于<text>的单词数，那么返回从<s>开始，到<text>结束的单词串。
test_wordlist:sources:= 189 457 231 banana apple orange
define test_wordlist
	@echo "$(wordlist 2,4,$(sources))"
	@echo "$(wordlist 2,8,$(sources))"
endef

#$(words <text>)
#名称：单词个数统计函数——words。
#功能：统计<text>中字符串中的单词个数。
#返回：返回<text>中的单词数。
#备注：如果我们要取<text>中最后的一个单词，我们可以这样：$(word $(words <text>),<text>)。
test_words:sources:= 189 457 231 banana apple orange
define test_words
	@echo "$(words $(sources))"
endef

#$(firstword <text>)
#名称：首单词函数——firstword。
#功能：取字符串<text>中的第一个单词。
#返回：返回字符串<text>的第一个单词。
#备注：这个函数可以用word函数来实现：$(word 1,<text>)。
test_firstword:sources:= 189 457 231 banana apple orange
define test_firstword
	@echo "$(firstword $(sources))"
endef

#$(dir <names...>)
#名称：取目录函数——dir。
#功能：从文件名序列<names>中取出目录部分。目录部分是指最后一个反斜杠（/）之前的部分。如果没有反斜杠，那么返回./。
#返回：返回文件名序列<names>的目录部分
test_dir:sources:= src/foo.c hacks out/lib/libxx.a
define test_dir
	@echo "$(dir $(sources))"
endef

#$(notdir <names...>)
#名称：取文件函数——notdir。
#功能：从文件名序列<names>中取出非目录部分。非目录部分是指最后一个反斜杠（/）之后的部分。
#返回：返回文件名序列<names>的非目录部分。
test_notdir:sources:= src/foo.c hacks out/lib/libxx.a
define test_notdir
	@echo "$(notdir $(sources))"
endef

#$(suffix <names...>)
#名称：取后缀函数——suffix。
#功能：从文件名序列<names>中取出各个文件名的后缀。
#返回：返回文件名序列<names>的后缀序列，如果文件没有后缀，则返回空字串。
test_suffix:sources:= src/foo.c hacks.o out/lib/libxx.a
define test_suffix
	@echo "$(suffix $(sources))"
endef


#$(basename <names...>)
#名称：取前缀函数——basename。
#功能：从文件名序列<names>中取出各个文件名的前缀部分。
#返回：返回文件名序列<names>的前缀序列，如果文件没有前缀，则返回空字串。
test_basename:sources:= src/foo.c hacks.o out/lib/libxx.a
define test_basename
	@echo "$(basename $(sources))"
endef

#$(addsuffix <suffix>,<names...>)
#名称：加后缀函数——addsuffix。
#功能：把后缀<suffix>加到<names>中的每个单词后面。
#返回：返回加过后缀的文件名序列。
test_addsuffix:sources:= src/foo hacks out/lib/libxx
define test_addsuffix
	@echo "$(addsuffix .c,$(sources))"
endef

#$(addprefix <prefix>,<names...>)
#名称：加前缀函数——addprefix。
#功能：把前缀<prefix>加到<names>中的每个单词后面。
#返回：返回加过前缀的文件名序列。
test_addprefix:sources:= src/foo hacks lib/libxx
define test_addprefix
	@echo "$(addprefix out/,$(sources))"
endef

#$(wildcard PATTERN...) 
#名称：
#功能：它被展开为已经存在的、使用空格分开的、匹配此模式的所有文件列表。如果不存在任何符合此模式的文件，函数会忽略模式字符并返回空
#返回：
define test_wildcard
	#获取工作目录下的所有的.c文件列表
	@echo "$(wildcard *.c)"
endef

#$(info text...)
#名称：信息显示函数。
#功能：输出text到屏幕
#返回：
define test_info
	@echo "$(info test ok !!!)"
endef

#$(warning text...)
#名称：警告控制函数。
#功能：输出text到屏幕,并显示目标执行的行数。
#返回：
define test_warning
	@echo "$(warning There is a problem with the test!!!)"
	@echo "next step"
endef

#$(error text...)
#名称：警告控制函数。
#功能：输出text到屏幕,终止执行后续步骤，并显示目标执行的行数。
#返回：
define test_error
	@echo "$(error Fatal error in test!!!)"
	@echo "next step"
endef

#$(join <list1>,<list2>)
#名称：连接函数——join。
#功能：把<list2>中的单词对应地加到<list1>的单词后面。
#      如果<list1>的单词个数要比<list2>的多，那么，<list1>中的多出来的单词将保持原样。
#      如果<list2>的单词个数要比<list1>多，那么，<list2>多出来的单词将被复制到<list2>中。
#返回：返回连接过后的字符串。
test_join:list1:= aaa bbb
test_join:list2:= 111 222 333
define test_join
	@echo "$(join $(list1),$(list2))"
	@echo "$(join $(list2),$(list1))"
endef

#$(foreach <var>,<list>,<text>)
#名称：循环处理函数
#功能：把参数<list>中的单词逐一取出放到参数<var>所指定的变量中，然后再执行<text>所包含的表达式。
#      每一次<text>会返回一个字符串，循环过程中，<text>的所返回的每个字符串会以空格分隔，最后当整个循环结束时，
#      <text>所返回的每个字符串所组成的整个字符串（以空格分隔）将会是foreach函数的返回值。
#返回：循环处理结果字符串合集。
test_foreach:sources:= aaa bbb ddd
define test_foreach
	@echo "$(foreach n,$(sources),$(n).o)"
endef


#$(call function,param,param,...)
#名称：调用函数的函数
#功能：将它的参数“ param”依次赋值给临时变量“ $(1)”、“ $(2)”，$(0)代表变量“ function”本身
#返回：
define test_call
	@echo "function = $(0)"
	@echo "param1 = $(1)"
	@echo "param2 = $(2)"
endef

#$(eval text)
#名称：
#功能：函数“eval”是一个比较特殊的函数。使用它可以在Makefile中构造一个可变的规则结构关系（依赖关系链），
#      其中可以使用其它变量和函数。函数“eval”对它的参数进行展开，展开的结果作为Makefile的一部分，make可以对展开内容进行语法解析。
#      展开的结果可以包含一个新变量、目标、隐含规则或者是明确规则等。也就是说此函数的功能主要是：根据其参数的关系、结构，对它们进行替换展开
#说明：函数说明：“eval”函数执行时会对它的参数进行两次展开。第一次展开过程发是由函数本身完成的，
#      第二次是函数展开后的结果被作为Makefile内容时由make解析时展开的。明确这一过程对于使用“eval”函数非常重要。
#      理解了函数“eval”二次展开的过程后。实际使用时，如果在函数的展开结果中存在引用（格式为：$(x)），那么在函数的参数中应该使用“$$”来代替“$”。
#      因为这一点，所以通常它的参数中会使用函数“value”来取一个变量的文本值。
#返回：
pointer:= pointed_value
define test_eval
	var := 123
	arg := $1
	$$($1) := ooooo
endef

#$(info $(call test_eval,pointer))
$(info $(eval $(call test_eval,pointer)))


#$(if <condition>,<then-part>)
#$(if <condition>,<then-part>,<else-part>)
#名称：条件判断函数
#功能：if 函数的第一个参数 condition表示条件判断，展开后如果非空，则条件为真，执行 then-part部分；
#      否则，如果有else-part部分，则执行else-part部分
#返回：
install_path = $(if $(install__path), $(install__path), /usr/local)
define test_if
	@echo "install_path = $(install_path)"
endef

#$(origin variable)
#名称：
#功能：origin函数并不操作变量的值，它告诉我们一些关于变量的信息，尤其是变量是从哪里来的。
#返回：变量是从哪里来的
test_origin:TEST:= aaa bbb
define test_origin
	@echo $(origin V)
	@echo $(origin USER)
	@echo $(origin CC)
	@echo $(origin TEST)
endef

#$(shell command)
#名称：
#功能：用shell解释执行command
#返回：执行command的结果
define test_shell
	@echo $(shell pwd)
endef

#$(value VARIABLE)
#名称：
#功能：不对变量“VARIBLE”进行任何展开操作，直接返回变量“VARIBALE”的值。
#      这里“VARIABLE”是一个变量名，一般不包含“$” （除非计算的变量名）
#返回：变量“VARIBALE”所定义文本值
#    （如果变量定义为递归展开式，其中包含对其他变量或者函数的引用，那么函数不对这些引用进行展开。函数的返回值是包含有引用值）。 
test_value:sources:= aaa bbb
define test_value
	@echo $(value sources)
endef




#>>>----------------------------------------函数调用---------------------------------
#>>>>>>>>>>>>>>>>字符串处理函数
test_subst:
	$(call test_subst)

test_patsubst:
	$(call test_patsubst)

test_strip:
	$(call test_strip)

test_findstring:
	$(call test_findstring)

test_filter:
	$(call test_filter)

test_filter-out:
	$(call test_filter-out)

test_sort:
	$(call test_sort)

test_word:
	$(call test_word)

test_wordlist:
	$(call test_wordlist)

test_words:
	$(call test_words)

test_firstword:
	$(call test_firstword)

#>>>>>>>>>>>>>>>>文件名操作函数
test_dir:
	$(call test_dir)

test_notdir:
	$(call test_notdir)

test_suffix:
	$(call test_suffix)

test_basename:
	$(call test_basename)

test_addsuffix:
	$(call test_addsuffix)

test_addprefix:
	$(call test_addprefix)

test_wildcard:
	$(call test_wildcard)

#>>>>>>>>>>>>>>>>控制函数
test_info:
	$(call test_info)

test_warning:
	$(call test_warning)

test_error:
	$(call test_error)

#>>>>>>>>>>>>>>>>其他操作函数
test_join:
	$(call test_join)

test_foreach:
	$(call test_foreach)

test_call:
	$(call test_call,value1,value2)

test_eval:
	@echo "---------------------"
	@echo "var : $(var) arg: $(arg)"
	@echo "pointer: $(pointer), pointed_value:$(pointed_value)"
	@echo "---------------------"

test_if:
	$(call test_if)

test_origin:
	$(call test_origin)

test_shell:
	$(call test_shell)

test_value:
	$(call test_value)
