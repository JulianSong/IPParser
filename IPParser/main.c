//
//  main.c
//  IPParser
//
//  Created by SongJunliang on 2017/6/28.
//  Copyright © 2017年 SongJunliang. All rights reserved.
//
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <assert.h>
#define IS_DIGIT(c) ((c) >= '0' && (c) <= '9')
long long convert(const char * ipstr){
    if (ipstr == NULL || strlen(ipstr) == 0) {
        return -1;
    }
    long long r = 0;
    int dotCount = 3;
    char dot = '.';
    char speace = ' ';
    int stackCount = 0;
    int stack[3] = {-1,-1,-1};
    bool isSpace = false;
    
    for (int i = 0; i < strlen(ipstr); i++) {
        char sub = ipstr[i];
        if (sub == dot) {
            if (stackCount == 0) {
                 printf("栈内元素等于0，ip地址无效\n");
                return -1;
            }
            isSpace = false;
            long long stepCount = 0;
            for (int si = 0 ; si < stackCount ; si++ ){
                int cu = stack[si];
                if (cu != -1) {
                   stepCount += pow(10,(stackCount - 1 - si)) * cu;
                }
            }
            if (stepCount > 255) {
                printf("大于255，ip地址无效\n");
                return -1;
            }
            r += stepCount << (dotCount * 8);
            stackCount = 0;
            dotCount--;
        }else if (sub == speace) {
            if (i == 0){
                printf("开头有空格，ip地址无效\n");
                return -1;
            }
            isSpace = true;
        }else if(IS_DIGIT(sub)){
            if(stackCount > 2){
                printf("栈内元素大于3，ip地址无效\n");
                return -1;
            }
            if (isSpace == true && stackCount > 0) {
                printf("数字之间存在空格，ip地址无效\n");
                return -1;
            }
            isSpace = false;
            stack[stackCount] = sub - '0';
            stackCount ++;
        }else{
            printf("无效字符，ip地址无效\n");
            return -1;
        }
    }
    
    if (dotCount != 0) {
        printf("长度错误，ip地址无效\n");
        return -1;
    }
    if (stackCount == 0) {
        printf("栈内元素等于0，ip地址无效\n");
        return -1;
    }
    
    long long stepCount = 0;
    for (int si = 0 ; si < stackCount ; si++ ){
        int cu = stack[si];
        if (cu != -1) {
            stepCount += pow(10,(stackCount - 1 - si)) * cu;
        }
    }
    if (stepCount > 255) {
        printf("大于255，ip地址无效\n");
        return -1;
    }
    
    r += stepCount << (dotCount * 8);
    
    return r;
}

int main(int argc, const char * argv[]) {
    
    
    
    assert(convert("10.68.1.2") == 172228866);
    assert(convert("172.168.5.1") == 2896692481);
    assert(convert("255.255.255.255") == 4294967295);
    assert(convert("172.168.5.255") == 2896692735);
    
    assert(convert("10 . 68 .1  . 2") == 172228866);
    assert(convert("10  .   68  .  1.  2") == 172228866);
    assert(convert("1  .   1.   1.    1") == 16843009);
    
    assert(convert(NULL) == -1);
    assert(convert("") == -1);
    assert(convert("172") == -1);
    assert(convert("172.") == -1);
    assert(convert("172.168") == -1);
    assert(convert("172.168.1") == -1);
    assert(convert("172.168.1.") == -1);
     assert(convert("172.168.1.1.") == -1);
    assert(convert("172.168.1.1.1") == -1);
    
    assert(convert(" 10.68.1.2") == -1);
    assert(convert("1 0.68.1.2") == -1);
    assert(convert("172.168.1.") == -1);
    
    assert(convert("0") == -1);
    assert(convert("256") == -1);
    assert(convert("256.1.1.1") == -1);
    assert(convert("1000.1.1.1") == -1);
    assert(convert("1.1.1.1000") == -1);
    
    assert(convert("256.256.256.256") == -1);
    assert(convert("256.255.255.1") == -1);
    assert(convert("255.256.1.255") == -1);
    assert(convert("1.255.255.256") == -1);
    
    assert(convert("-1.255.255.256") == -1);
    
    return 0;
}

