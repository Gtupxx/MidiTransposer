#include "CMidiTranspose.h"

int main()
{
    CMidiTranspose MidiTransposer;
    MidiTransposer.SelectPort();
    MidiTransposer.ChooseSignature();
    MidiTransposer.RUN();
}