/*
 * @Author: 柚岩龙蜥
 * @Date: 2024-01-31 02:26:31
 * @LastEditors: 柚岩龙蜥
 * @LastEditTime: 2024-01-31 02:29:37
 * @FilePath: \MidiTransposer\main.cpp
 * @Description:  
 * 
 */
#include "CMidiTranspose.h"

int main()
{
    CMidiTranspose MidiTransposer;
    MidiTransposer.SelectPort();
    MidiTransposer.ChooseSignature();
    MidiTransposer.RUN();
}