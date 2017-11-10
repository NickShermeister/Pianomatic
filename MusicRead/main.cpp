//
//  main.cpp
//  MusicRead
//
//  Created by Christopher Aring on 10/31/17.
//  Copyright © 2017 PianoMatic. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include "notes.hpp"
#include <vector>
#include <sstream>
#include <cmath>
#include <map>
#include <set>
#include <bitset>

//CHECK USING ALL BYTES NOT JUST LEAST SIG!!!
//NEED TICKS PER QUARTER NOTE!!!
int main(int argc, const char * argv[]) {
    std::streampos size;
    char * memblock;
    float lengthPrev= 0;
    int tempo = 0;
    int n = 0;
    int d = 0;
    int ctpqn = 0;
    float ppqn = 0;
    int format = 0;
    int numTracks = 0;
    float deltaTime = -1.0f; // FORCED FOR NOW
    int index = 0;
    
    std::vector<Notes> notes;
//    std::map<char, std::string> noteLookupTable = {{,}, {}};
    
    std::ifstream file ("/Users/Chris/Documents/MusicRead/MusicRead/song2.mid", std::ios::in|std::ios::ate);
    
    if (file.is_open())
    {
        size = file.tellg();
        memblock = new char [size];
        file.seekg(0, std::ios::beg);
        file.read(memblock, size);

        //Loop through memory buffer
        for(int i = 0; i < size; i++)
        {
            //Header Chunk
            if (memblock[i] == (char)0x4D && memblock[i+1] == (char)0x54 && memblock[i+2] == (char)0x68 && memblock[i+3] == 0x64)
            {
                format = (memblock[i+8]<<8) + memblock[i+9];
                numTracks = (memblock[i+10]<<8) + memblock[i+11];
                ppqn = (memblock[i+12]<<8) + memblock[i+13];
            }
            
            //Track chunk
            if (memblock[i] == (char)0x4D && memblock[i+1] == (char)0x54 && memblock[i+2] == (char)0x72 && memblock[i+3] == 0x6B)
            {
                int chunkLength;
                
                chunkLength = int((unsigned char)(memblock[i+4]) << 24 |
                                  (unsigned char)(memblock[i+5]) << 16 |
                                  (unsigned char)(memblock[i+6]) << 8 |
                                  (unsigned char)(memblock[i+7]));
            }
            
            //Meta event
            if (memblock[i] == (char)0xFF)
            {
                //Update delta time
                deltaTime = deltaTime + (int)memblock[i-1];
                
                //Time Signature
                if (memblock[i+1] == (char)0x58 && memblock[i+2] == (char)0x04)
                {
                    n = (int)memblock[i+3];
                    d = pow(2, (int)memblock[i+4]);
                    ctpqn = memblock[i+5];
                }
                
                //Tempo
                else if (memblock[i+1] == (char)0x51 && memblock[i+2] == (char)0x03)
                {
                    tempo = int((unsigned char)(memblock[i+3]) << 16 |
                                (unsigned char)(memblock[i+4]) << 8 |
                                (unsigned char)(memblock[i+5]));
                }
            }
            
            //Note on
            if (memblock[i] == (char)0x90)
            {
                //Delta time
                if (index == 0)
                {
                    index = i - 4;
                }
                
                int dist = i - 3 - index;
                
                if (i == 112)
                {
                    dist = 1;
                }
                if (dist == 1)
                {
                    deltaTime = deltaTime + (float)memblock[i-1];
                }
                if (dist == 2)
                {
                    //Remove MSB
                    std::bitset<7> x;
                    x = (unsigned char)memblock[i-1];
                    
                    //Remove MSB
                    std::bitset<7> y;
                    y = (unsigned char)memblock[i-2];
                    
                    //Combine into one number
                    std::bitset<16> z;
                    z[0] = x[0];
                    z[1] = x[1];
                    z[2] = x[2];
                    z[3] = x[3];
                    z[4] = x[4];
                    z[5] = x[5];
                    z[6] = x[6];
                    z[7] = y[0];
                    z[8] = y[1];
                    z[9] = y[2];
                    z[10] = y[3];
                    z[11] = y[4];
                    z[12] = y[5];
                    z[13] = y[6];
                    z[14] = 0;
                    z[15] = 0;
                    
                    //Convert to float
                    float yy = (float)(z.to_ulong());
                    deltaTime = deltaTime + yy;
                }
                Notes note(memblock[i+1], deltaTime);
                notes.push_back(note);
                index = i;
            }
            
            //Note off
            if (memblock[i] == (char)0x80)
            {
                //Delta time
                if (index == 0)
                {
                    index = i - 4;
                }
                
                int dist = i - 3 - index;
                
                if (i == 112)
                {
                    dist = 1;
                }
                if (dist == 1)
                {
                    deltaTime = deltaTime + (float)memblock[i-1];
                }
                if (dist == 2)
                {
                    //Remove MSB
                    std::bitset<7> x;
                    x = (unsigned char)memblock[i-1];
                    
                    //Remove MSB
                    std::bitset<7> y;
                    y = (unsigned char)memblock[i-2];
                    
                    //Combine into one number
                    std::bitset<16> z;
                    z[0] = x[0];
                    z[1] = x[1];
                    z[2] = x[2];
                    z[3] = x[3];
                    z[4] = x[4];
                    z[5] = x[5];
                    z[6] = x[6];
                    z[7] = y[0];
                    z[8] = y[1];
                    z[9] = y[2];
                    z[10] = y[3];
                    z[11] = y[4];
                    z[12] = y[5];
                    z[13] = y[6];
                    z[14] = 0;
                    z[15] = 0;
                    
                    //Convert to float
                    float yy = (float)(z.to_ulong());
                    deltaTime = deltaTime + yy;
                }

                for (int j = 0; j<notes.size(); j++)
                {
                    if (notes[j].getNoteOff() == 0 && notes[j].getNote() == memblock[i+1])
                    {
                        notes[j].setNoteOff(deltaTime);
                    }
                }
                index = i;
            }
        }
        
        delete[] memblock;
        file.close();
        
        //PRINT
        for(int r = 0; r<notes.size(); r++)
        {
            std::cout << "[note: " << notes[r].getNote()<< "] [start: " << notes[r].getNoteOn() << "] [end: " << notes[r].getNoteOff() << "] [length: " << notes[r].getNoteLen() << "]" << std::endl;
        }
    }
    else std::cout << "Unable to open file.";
    
    std::vector<char> ALL_NOTES;
    for (int allNotes = 71; allNotes > 47; allNotes--)
    {
        ALL_NOTES.push_back(allNotes);
    }
    
    
    
    //Create note file
    std::fstream output;
    output.open ("/Users/Chris/Desktop/Notes.txt", std::ios::out|std::ios::in|std::ios_base::trunc);
    
    if (output.is_open())
    {
        for (int mainNote = 0; mainNote<ALL_NOTES.size(); mainNote++)
        {
            for (int note = 0; note<7; note++)
            {
                if (notes[note].getNote() == ALL_NOTES[mainNote])
                {
                    
                    for (int j = 0; j < notes[note].getNoteOn() - lengthPrev; j++)
                    {
                        output.write(" ", 1);
                    }
                    for(int k = 0; k < notes[note].getNoteLen(); k++)
                    {
                        output.write("\xE2\x96\xA0", 3);
                    }
                    lengthPrev = notes[note].getNoteOff();
                }
                
            }
            lengthPrev = 0.0;
            output.write("\n", 1);
        }
        output.close();
    }
    else std::cout << "Unable to open file.";
    return 0;
}
