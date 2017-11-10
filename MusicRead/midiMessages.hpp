//
//  midiMessages.hpp
//  MusicRead
//
//  Created by Christopher Aring on 11/2/17.
//  Copyright © 2017 PianoMatic. All rights reserved.
//

#ifndef midiMessages_hpp
#define midiMessages_hpp

#include <stdio.h>

class MidiMessages
{
public:
    MidiMessages() = default;
    MidiMessages(int);

private:
    int m_messageType;
    char m_statusByte;
    char m_dataByte;
    
};

#endif /* midiMessages_hpp */
