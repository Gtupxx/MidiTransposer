#include <iostream>
#include <rtmidi/RtMidi.h>
#include "CMidiTranspose.h"

// MIDI input callback function
void CMidiTranspose::__MidiInputCallback(double timeStamp, std::vector<unsigned char> *message, void *userData)
{
    unsigned char statusByte = (*message)[0];
    unsigned char messageType = statusByte & 0xF0; // 提取消息类型
    unsigned char channel = statusByte & 0x0F;     // 提取通道信息

    switch (messageType)
    {
    case 0x80: // Note Off
    {
        unsigned char noteNumber = (*message)[1];
        unsigned char velocity = (*message)[2];

        std::cout << "Note Off - Channel: " << static_cast<int>(channel)
                  << " Note Number: " << static_cast<int>(noteNumber)
                  << " Velocity: " << static_cast<int>(velocity) << std::endl;
        break;
    }
    case 0x90: // Note On
    {
        unsigned char noteNumber = (*message)[1];
        unsigned char velocity = (*message)[2];

        std::cout << "Note On - Channel: " << static_cast<int>(channel)
                  << " Note Number: " << static_cast<int>(noteNumber)
                  << " Velocity: " << static_cast<int>(velocity) << std::endl;
        break;
    }
    case 0xA0: // Polyphonic Key Pressure
    {
        unsigned char noteNumber = (*message)[1];
        unsigned char pressure = (*message)[2];

        std::cout << "Polyphonic Key Pressure - Channel: " << static_cast<int>(channel)
                  << " Note Number: " << static_cast<int>(noteNumber)
                  << " Pressure: " << static_cast<int>(pressure) << std::endl;
        break;
    }
    case 0xB0: // Control Change
    {
        unsigned char controlNumber = (*message)[1];
        unsigned char controlValue = (*message)[2];

        std::cout << "Control Change - Channel: " << static_cast<int>(channel)
                  << " Control Number: " << static_cast<int>(controlNumber)
                  << " Control Value: " << static_cast<int>(controlValue) << std::endl;
        break;
    }
    case 0xC0: // Program Change
    {
        unsigned char programNumber = (*message)[1];

        std::cout << "Program Change - Channel: " << static_cast<int>(channel)
                  << " Program Number: " << static_cast<int>(programNumber) << std::endl;
        break;
    }
    case 0xD0: // Channel Pressure
    {
        unsigned char pressure = (*message)[1];

        std::cout << "Channel Pressure - Channel: " << static_cast<int>(channel)
                  << " Pressure: " << static_cast<int>(pressure) << std::endl;
        break;
    }
    case 0xE0: // Pitch Bend
    {
        unsigned char lsb = (*message)[1];
        unsigned char msb = (*message)[2];
        int value = (msb << 7) | lsb;

        std::cout << "Pitch Bend - Channel: " << static_cast<int>(channel)
                  << " Value: " << value << std::endl;
        break;
    }
    // 其他类型的消息...
    default:
        std::cout << "Unknown Message - Status Byte: " << static_cast<int>(statusByte) << std::endl;
        break;
    }

    // Cast the user data to RtMidiOut pointer
    std::pair<RtMidiOut *, std::string> usd = *static_cast<std::pair<RtMidiOut *, std::string> *>(userData);
    RtMidiOut *midiOut = usd.first;

    // Check if it's a note-on or note-off message
    if (statusByte == 0x90 || statusByte == 0x80)
    {
        // Extract note number and velocity
        unsigned char noteNumber = (*message)[1];
        unsigned char velocity = (*message)[2];

        // Increment note number
        if (noteNumber < 127)
        {
            noteNumber += m_smapTransposeMap[usd.second];
            noteNumber %= 127;
        }

        // Create and send the modified message
        std::vector<unsigned char> modifiedMessage;
        modifiedMessage.push_back(statusByte);
        modifiedMessage.push_back(noteNumber);
        modifiedMessage.push_back(velocity);
        midiOut->sendMessage(&modifiedMessage);
    }
    else
    {
        // Send the original message as is
        midiOut->sendMessage(message);
    }
}

std::map<std::string, int> CMidiTranspose::m_smapTransposeMap = {
    {"C", 0},
    {"C#", 1},
    {"Db", 1},
    {"D", 2},
    {"D#", 3},
    {"Eb", 3},
    {"E", 4},
    {"F", 5},
    {"F#", 6},
    {"Gb", 6},
    {"G", 7},
    {"G#", 8},
    {"Ab", 8},
    {"A", 9},
    {"A#", 10},
    {"Bb", 10},
    {"B", 11}};

void CMidiTranspose::SelectPort()
{
    try
    {
        // Get available input and output ports
        unsigned int numInputPorts = m_MidiIn.getPortCount();
        unsigned int numOutputPorts = m_MidiOut.getPortCount();

        // Check if there are available input and output ports
        if (numInputPorts == 0 || numOutputPorts == 0)
        {
            std::cout << "No MIDI input or output ports available." << std::endl;
            return;
        }

        // Print the available input ports
        std::cout << "Available MIDI input ports: (Enter the index of your device)" << std::endl;
        for (unsigned int i = 0; i < numInputPorts; ++i)
        {
            std::cout << i << ": " << m_MidiIn.getPortName(i) << std::endl;
        }

        // Open the first available input ports
        unsigned int in = numInputPorts;
        while (in >= numInputPorts)
        {
            std::cin >> in;
        }
        m_MidiIn.openPort(in);

        // Print the available output ports
        std::cout << "Available MIDI output ports: (Enter the index of the virtual output)" << std::endl;
        for (unsigned int i = 0; i < numOutputPorts; ++i)
        {
            std::cout << i << ": " << m_MidiOut.getPortName(i) << std::endl;
        }

        // Open the first available output ports
        unsigned int out = numOutputPorts;
        while (out >= numOutputPorts)
        {
            std::cin >> out;
        }
        m_MidiOut.openPort(out);

        // Print the chosen input and output port names
        std::cout << "Input port: " << m_MidiIn.getPortName(in) << std::endl;
        std::cout << "Virtual input port: " << m_MidiOut.getPortName(out) << std::endl;
    }
    catch (RtMidiError &error)
    {
        std::cerr << "Error: " << error.getMessage() << std::endl;
    }
}

void CMidiTranspose::RUN()
{
    try
    {
        // Set the MIDI input callback function
        std::pair<RtMidiOut *, std::string> userData = {&m_MidiOut, m_sSignature};
        m_MidiIn.setCallback(__MidiInputCallback, &userData);
        std::cout << "Listening to MIDI input. Press Enter to exit." << std::endl;
        std::cin.ignore();
        std::cin.get();

        // Close the MIDI input and output ports
        m_MidiIn.closePort();
        m_MidiOut.closePort();
    }
    catch (RtMidiError &error)
    {
        std::cerr << "Error: " << error.getMessage() << std::endl;
    }

    return;
}

void CMidiTranspose::ChooseSignature()
{
    std::cout << "Please enter the signature you want to transpose:" << std::endl;
    bool flag = true;
    while (flag)
    {
        std::cin >> m_sSignature;
        if (m_smapTransposeMap.find(m_sSignature) != m_smapTransposeMap.end())
        {
            flag = 0;
        }
        else
        {
            std::cout << "Invalid input, retry with another form!" << std::endl;
        }
    }
}