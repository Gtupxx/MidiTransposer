/*
 * @Author: 柚岩龙蜥
 * @Date: 2024-01-14 21:02:39
 * @LastEditors: 柚岩龙蜥
 * @LastEditTime: 2024-01-14 21:44:27
 * @FilePath: \MidiTransposer\src\CMidiTranspose.h
 * @Description:  
 * 
 */
#pragma once

#include <vector>
#include <iostream>
#include <map>
#include <rtmidi/RtMidi.h>

class CMidiTranspose
{
public:
    CMidiTranspose()
    {
        m_sSignature = "C";
    }

    void RUN();
    void SelectPort();
    void ChooseSignature();

private:
    static void __MidiInputCallback(double, std::vector<unsigned char>*,void*);

private:
    RtMidiIn m_MidiIn;
    RtMidiOut m_MidiOut;
    std::string m_sSignature;

private:
    static std::map<std::string, int> m_smapTransposeMap;
};
