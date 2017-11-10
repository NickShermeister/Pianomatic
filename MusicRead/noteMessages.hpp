//
//  noteMessages.hpp
//  MusicRead
//
//  Created by Christopher Aring on 11/2/17.
//  Copyright © 2017 PianoMatic. All rights reserved.
//

#ifndef noteMessages_hpp
#define noteMessages_hpp

#include <stdio.h>

class NoteMessages
{
public:
    NoteMessages() = default;
    NoteMessages(char, char, char);

private:
    char m_noteMessage;
    char m_note;
    char m_velocity;
};
#endif /* noteMessages_hpp */
