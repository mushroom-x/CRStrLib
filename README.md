# CRStrLib - CloudRiver C语言字符串数值解析库

## 1。综述
>杭州云江科技(CloudRiver) 出品， 获取更多OpenMV相关教程，加QQ群 凡哥带你玩转OpenMV < 564048763 >


此工程用于C语言解析字符串中的数值。
功能包括帧头帧尾校验，寻找字符串中的数值并将其转换为整数或者浮点数， 字符串无需按照特定格式， 是一个比较通用的字符串解析库。
发送过程中无需将浮点数转换为整数，负值也可以正常解析。

没第三方库（包括标准库）的引用， 可以方便地加入到单片机的工程或者添加到Arduino的库函数中。

写此函数的初衷是为了方便云江科技的用户， 在C语言中将OpenMV串口发送的字符串数据解析出来，提供了若干个范例。



使用样例见单元测试文件`test_crstrlib.c`


## 2. Quick Start
我们首先自定义一串字符串，模拟单片机接受的数据。
其中`HEAD`，`TAIL`是任意指定的帧头帧尾的校验数据。
我们对帧头帧尾进行校验，看数据是否匹配，如果不匹配的话，说明传输过程中出现了错误， 丢弃此帧。

然后我们根据不同数据类型，使用不同函数， 依次读入数据。

如果你想读入一个整数， 调用`CRStrLib_findNextInt`来寻找下面的一个整数类型的数据。

如果想读入一个浮点数值，那就调用`CRStrLib_findNextFloat`函数。


```c
char *data = "HEAD,12,3,62.31,TAIL"; // 模拟单片机的数据
int dataLen = CRStrLib_strLen(data); // 获取字符串长度
int dataIdx = 0; // 记录字符串读取的下标
int x; // x的值 整数
int y; // y的值 整数
float value; // 传感器的模拟值， 小数.

/* 校验帧头帧尾 */
if (CRStrLib_isValidData(data, "HEAD", "TAIL") == FALSE){
    /* 数据丢失无效数据 */
    printf("Invailid data\n");
    return;
}

/* 根据不同数据类型，使用不同函数， 依次读入数据 */
CRStrLib_findNextInt(data, dataLen, &dataIdx, &x);
CRStrLib_findNextInt(data, dataLen, &dataIdx, &y);
CRStrLib_findNextFloat(data, dataLen, &dataIdx, &value);

/* 展示演示效果 */
printf("data read success\n");
printf("x: %d, y:%d, value:%.3f", x, y, value);
```

**输出结果**
```
data read success
x: 12, y:3, value:62.310
```

## 3. 主要API讲解

### 3.1. 帧头校验

```c
Boolean CRStrLib_startWith(char *str, char *head);
```
**参数**

`@Param char *str` 要匹配的字符串。
`@Param char *head` 帧头字符串

**返回值**

整数类型 : Boolean
* TRUE : 等同于整数类型 1
* FALSE :  等同于整数类型 0

**演示样例**

```c
char *str = "HEADA.....";
char *head = "HEADA";
int isLegal = CRStrLib_startWith(str, head);
```
### 3.2. 帧尾校验

```c
Boolean CRStrLib_endWith(char *str, char *tail);
```
**参数**

`@Param char *str` 要匹配的字符串。
`@Param char *tail` 帧尾字符串。

**返回值**

整数类型 : Boolean
* TRUE : 等同于整数类型 1
* FALSE :  等同于整数类型 0

**演示样例**

```c
char *str = ".....TAILA";
char *tail = "TAILA";
int isLegal = CRStrLib_startWith(str, tail);
```

### 3.3. 帧校验

帧校验其实是融合了帧头校验跟帧尾校验两个函数。

```c
Boolean CRStrLib_isValidData(char *str, char *head, char *tail);
```


**参数**

`@Param char *str` 要匹配的字符串。
`@Param char *head` 帧头字符串。
`@Param char *tail` 帧尾字符串。

**返回值**

整数类型 : Boolean
* TRUE : 等同于整数类型 1
* FALSE :  等同于整数类型 0

**演示样例**

```c
char *data = "HEAD,12,3,62.31,TAIL"; // 模拟单片机的数据

/* 校验帧头帧尾 */
if (CRStrLib_isValidData(data, "HEAD", "TAIL") == FALSE){
    /* 数据丢失无效数据 */
    printf("Invailid data\n");
    return;
}
```

### 3.4. 读入一个整数

读出的数值，通过指针的方式， 赋值给result指向的空间。

```c
Status CRStrLib_findNextInt(char *str, int strLen, int *strIdx, int *result);
```

**参数**

`@Param char *str` 要匹配的字符串。
`@Param int strLen` 字符串的长度。
`@Param int *strIdx` 字符串游标，指针类型。
`@Param int *result` 读出的结果， 整数类型

**返回值**

返回值： 状态码（Status） 整数类型

```c
#define STATUS_SUCCESS 0
#define STATUS_FAIL -1
#define STATUS_NOT_FOUND 404
```

**演示样例**
```c
char *data = "dsaserxc122,xaDSAAhg-232,--adaf897";
int strLen = CRStrLib_strLen(data);
int strIdx = 0;
int nextInt;
int status;

printf("data length : %d\n", strLen);

/* 获取所有的整数 */
while(CRStrLib_findNextInt(data, strLen, &strIdx, &nextInt)!=STATUS_NOT_FOUND){
    printf("Next int is %d , strIdx : %d\n", nextInt, strIdx);
}
```

**输出结果**

```
data length : 34
Next int is 122 , strIdx : 11
Next int is -232 , strIdx : 24
Next int is 897 , strIdx : 34
```
### 3.5. 读入一个浮点数

```c
Status CRStrLib_findNextFloat(char *str, int strLen, int *strIdx, float *result);
```

**参数**

`@Param char *str` 要匹配的字符串。
`@Param int strLen` 字符串的长度。
`@Param int *strIdx` 字符串游标，指针类型。
`@Param float *result` 读出的结果， 浮点数类型

**返回值类型**
返回值： 状态码（Status） 整数类型

```c
#define STATUS_SUCCESS 0
#define STATUS_FAIL -1
#define STATUS_NOT_FOUND 404
```

**演示样例**
```python
char *data = "dsaserxc122.21,xaDSAAhg-232.,--adaf897.123asdf asdfa888,asdf-0.423， 0.0";
int strLen = CRStrLib_strLen(data);
int strIdx = 0;
float nextFloat;
int status;

printf("data length : %d\n", strLen);

/* 获取所有的整数 */
while(CRStrLib_findNextFloat(data, strLen, &strIdx, &nextFloat)!=STATUS_NOT_FOUND){
    printf("Next flaot is %.3f , strIdx : %d\n", nextFloat, strIdx);
}
```

**输出结果**

```
data length : 73
Next flaot is 122.210 , strIdx : 14
Next flaot is -232.000 , strIdx : 27
Next flaot is 897.123 , strIdx : 42
Next flaot is 888.000 , strIdx : 55
Next flaot is -0.423 , strIdx : 66
Next flaot is 0.000 , strIdx : 73
```