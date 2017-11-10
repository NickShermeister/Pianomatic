//
//  notes.cpp
//  MusicRead
//
//  Created by Christopher Aring on 11/1/17.
//  Copyright © 2017 PianoMatic. All rights reserved.
//

#include "notes.hpp"
#include <cmath>

Notes::Notes(char note, float ticks)
{
    m_note = note;
    m_noteOn = ticks/256.0f;
    m_noteOn = (floor((m_noteOn*2)+0.5)/2);
    m_noteOn = m_noteOn * 4;
    m_noteOff = 0.0;
}

void Notes::setNoteOff(float ticks)
{
    m_noteOff = ticks/256.0f;
    m_noteOff = (floor((m_noteOff*2)+0.5)/2);
    m_noteOff = m_noteOff * 4;
    m_length = (m_noteOff - m_noteOn);// /10000;
}

