/*
 * 此文件为crstrlib的单元测试文件， 可以通过测试样例，了解crstrlib库的用法。
 *
 * Copyright (c) 2017/2017 ShunkaiXing@杭州云江科技 <xingshunkai@qq.com>
 * This work is licensed under the MIT license, see the file LICENSE for details.
 *
 * 获取更多OpenMV相关教程，加QQ群 凡哥带你玩转OpenMV < 564048763 >
 **/

#include "crstrlib.h"

int main(){
    // testFindNextInt();
    // testFindNextFloat();
    diyProtocal();
}

/* csv通信协议模拟 x,y为整数，数值为浮点数 */
void diyProtocal(){

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

    printf("data read success\n");
    printf("x: %d, y:%d, value:%.3f", x, y, value);

}

void testFindNextInt(){
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
}
/* 测试寻找下一个浮点数 */
void testFindNextFloat(){
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

}
