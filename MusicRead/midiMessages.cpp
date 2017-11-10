//
//  midiMessages.cpp
//  MusicRead
//
//  Created by Christopher Aring on 11/2/17.
//  Copyright © 2017 PianoMatic. All rights reserved.
//

#include "midiMessages.hpp"

MidiMessages::MidiMessages(int type)
{
    
}


/*
 
 
 if (index > 0)
 {
 int dist = (i - 3 - index );
 
 if (dist == 1)
 {
 deltaTime = deltaTime + (int)memblock[i-1];
 }
 else if (dist == 2)
 {
 deltaTime = deltaTime + int((unsigned char)(memblock[i-2]) << 8 |
 (unsigned char)(memblock[i-1]));
 }
 else if (dist == 0)
 {
 deltaTime = deltaTime;
 }
 }
 else
 {
 deltaTime = deltaTime + (int)memblock[i-1];
 }
 
 
 GOOOD!\/
 
 const float kSecondsPerQuarterNote = tempo / 1000000.0f;
 const float kTimeSignatureNumerator = n;
 const float kTimeSignatureDenominator = d;
 
 float kBarLength = (kTimeSignatureNumerator * kSecondsPerQuarterNote * 4.0f ) /  kTimeSignatureDenominator;
 
 
 for(int r = 0; r<notes.size(); r++)
 {
 std::cout << "[note: " << notes[r].getNoteLen() << "] [s: " << notes[r].getNoteOn() << "] [e: " << notes[r].getNoteOff() << "]" << std::endl;
 }
 
 
 std::cout << "BPM: " << bpm << std::endl;
 std::cout << "Format: " << format << std::endl;
 std::cout << "Number of tracks: " << numTracks << std::endl;
 std::cout << "Pulses per quarter note: " << ppqn << std::endl;
 std::cout << "Time signature: " << n << "/" << d << std::endl;
 std::cout << "Clock ticks per quarter note: " << ctpqn << std::endl;
 
 for(int r = 0; r<notes.size(); r++)
 {
 std::cout << "[note: " << notes[r].getNote() << "] [s: " << notes[r].getNoteOn() << "] [e: " << notes[r].getNoteOff() << "]" << std::endl;
 }
 
 
 
 
 
 if (memblock[i+8] > (char)0x80) //fix for all possibilities not just two length
 {
 deltaTime = int((unsigned char)(memblock[i+8]) << 8 |
 (unsigned char)(memblock[i+9]));
 } else {
 deltaTime = memblock[i+8];
 }
 
 
 
 
 const float kSecondsPerQuarterNote = tempo / 1000000.0f;
 const float kTimeSignatureNumerator = n;
 const float kTimeSignatureDenominator = d;
 
 float kBarLength = (kTimeSignatureNumerator * kSecondsPerQuarterNote * 4.0f ) /  kTimeSignatureDenominator;
 
 bpm = 60000000 / tempo;
 MillisecondsPerQuarterNote = tempo / 1000.0f;
 MillisecondsPerTick = MillisecondsPerQuarterNote / ppqn;
 //deltaTimeInMilliseconds = 190 * MillisecondsPerTick;
 float msPerTick = 60000 / (bpm * ppqn);
 */

/*
std::set<char> setOfNotes;




for (int line = 0; line < notes.size(); line ++)
{
    setOfNotes.insert(notes[line].getNote());
}

for (int note = 0; note < setOfNotes.size(); note ++)
{
    for(int line = 0; line < notes.size(); line++)
    {
        for (std::set<char>::iterator it=setOfNotes.begin(); it!=setOfNotes.end(); ++it)
        {
            if (notes[line].getNote() == *it)
            {
                file << "\xE2\xAC\x9B";
                }
                }
                
                }
                }
 
 std::cout << "BPM: " << ticksPerBar << std::endl;
 std::cout << "Format: " << format << std::endl;
 std::cout << "Number of tracks: " << numTracks << std::endl;
 std::cout << "Pulses per quarter note: " << ppqn << std::endl;
 std::cout << "Time signature: " << n << "/" << d << std::endl;
 std::cout << "Clock ticks per quarter note: " << ctpqn << std::endl;
 
 

 std::map<char, std::string> noteLookupTable;
 noteLookupTable['0'] = std::string("C4");
 
 
 
 
 
 
 
 
 for (int mainNote = 0; mainNote<ALL_NOTES.size(); mainNote++)
 {
 for (int note = 0; note<5; note++)
 {
 if (notes[note].getNote() == ALL_NOTES[mainNote])
 {
 for (int j = 0; j < notes[note].getNoteOn(); j++)
 {
 output << "$";
 }
 for(int k = 0; k < notes[note].getNoteLen(); k++)
 {
 output << notes[note].getNote();
 }
 }
 }
 output << + "\n";
 }
 
 
 
 
 
 
 for (int mainNote = 0; mainNote<ALL_NOTES.size(); mainNote++)
 {
 for (int note = 0; note<5; note++)
 {
 if (notes[note].getNote() == ALL_NOTES[mainNote])
 {
 for (int j = 0; j < notes[note].getNoteOn(); j++)
 {
 output.write(" ", 1);
 }
 for(int k = 0; k < notes[note].getNoteLen(); k++)
 {
 output.write("#", 1);
 }
 }
 
 }
 output.write("\n", 1);
 }
 
 output.close();
 }
 
                */
