<!--
 * @Author: 柚岩龙蜥
 * @Date: 2024-01-14 23:01:29
 * @LastEditors: 柚岩龙蜥
 * @LastEditTime: 2024-01-14 23:40:56
 * @FilePath: \MidiTransposer\README.md
 * @Description:  
 * 
-->
# MidiTransposer
该项目是一个 MIDI 移调器，旨在帮助那些没有移调功能的 MIDI 键盘（例如 Akai MPK mini 3）快速进行移调。

## 功能特点

- 可以通过安装 `loopMidi` 并创建虚拟 MIDI 端口来实现移调功能。
- 用户可以选择要移调的设备。
- 用户可以输入目标调号来移调 MIDI 输入信号。
- 支持的调号有：C, C#, Db, D, D#, Eb, E, F, F#, Gb, G, G#, Ab, A, A#, Bb, B。

## 使用方法

1. 首先，确保已安装 `loopMidi` 并创建了虚拟 MIDI 端口。
2. 启动 MIDI 移调器应用程序。
3. 在应用程序中选择要移调的设备。
4. 输入目标调号，例如 C# 或 Ab（原调为 C 大调）。
5. 现在，你的 MIDI 键盘将按照所选的目标调号进行移调。

## 系统要求

- 操作系统：支持 Windows11，别的没试过。
- 使用了CMake，但是显然我没用明白，编译就靠你了。
- 安装 `loopMidi` 软件。
- MIDI 键盘（例如 Akai MPK mini 3）。

## 安装

1. 克隆或下载本项目的代码到本地计算机。
2. 安装loopMidi。
3. 运行应用程序。

## 示例

**\*注意，运行前请打开loopMidi的虚拟端口**

```bash
Available MIDI input ports: (Enter the index of your device)
0: MPK mini 3 0
1: loopMIDI Port 1
0
Available MIDI output ports: (Enter the index of the virtual output)
0: Microsoft GS Wavetable Synth 0
1: MPK mini 3 1
2: loopMIDI Port 2
2
Input port: MPK mini 3 0
Virtual input port: loopMIDI Port 2
Please enter the signature you want to transpose:
A#
Listening to MIDI input. Press Enter to exit.

...
```
如果出现了下面的情况，请查看设备是否被占用：
```bash
Available MIDI input ports: (Enter the index of your device)
0: MPK mini 3 0
1: loopMIDI Port 1
0

MidiInWinMM::openPort: error creating Windows MM MIDI input port.

Error: MidiInWinMM::openPort: error creating Windows MM MIDI input port.
```

## 贡献

如果你对该项目感兴趣，欢迎贡献代码、报告问题或提出改进建议。请在 GitHub 上提出问题或提交拉取请求。
