//
//  notes.hpp
//  MusicRead
//
//  Created by Christopher Aring on 11/1/17.
//  Copyright © 2017 PianoMatic. All rights reserved.
//

#ifndef notes_hpp
#define notes_hpp

#include <stdio.h>
#include <vector>
#include <iostream>

class Notes
{
public:
    Notes() = default;
    Notes(char, float);
    char getNote() { return m_note; };
    float getNoteOn() { return m_noteOn; };
    float getNoteOff () { return m_noteOff; };
    float getNoteLen () { return m_length; };
    void setNoteOff(float);
    
private:
    char m_note;
    float m_noteOn;
    float m_noteOff;
    float m_length;
};

#endif /* notes_hpp */
