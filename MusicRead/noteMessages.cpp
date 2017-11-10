//
//  noteMessages.cpp
//  MusicRead
//
//  Created by Christopher Aring on 11/2/17.
//  Copyright © 2017 PianoMatic. All rights reserved.
//

#include "noteMessages.hpp"

NoteMessages::NoteMessages(char noteMessage, char note, char velocity)
{
    m_noteMessage = noteMessage;
    m_note = note;
    m_velocity = velocity;
}



//m_ low = noteMessage & 0x0F;
//var high = noteMessage >> 4;
