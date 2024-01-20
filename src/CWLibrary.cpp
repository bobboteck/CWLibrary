/*
 * Name          : CWLibrary.cpp
 * @author       : Roberto D'Amico (@Bobboteck)
 * Last modified : 20.01.2024
 * Revision      : 1.0.1
 *
 * Modification History:
 * Date         Version     Modified By     Description
 * 2021-09-22   1.0.0       Roberto D'Amico Send CW message at WPM defined
 * 2024-01-20   1.0.1       Roberto D'Amico FIX PARIS dots length
 * 
 * The MIT License (MIT)
 *
 *  This file is part of the CWLibrary Project (https://github.com/bobboteck/CWLibrary).
 *	Copyright (c) 2021 Roberto D'Amico (Bobboteck - https://bobboteck.github.io/).
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
#include "CWLibrary.hpp"

CWLibrary::CWLibrary(uint8_t wpm, CallbackFunction activateTrasmission, CallbackFunction deActivateTrasmission)
{
    _wpm = wpm;
    _activateTrasmission = activateTrasmission;
    _deActivateTrasmission = deActivateTrasmission;

    // Calculate the number of dots for one minute with the Paris method
    uint16_t dotsPerMinute = _wpm * cwParisDotsLength;
    // Calculate the duration of a single Dot
    _cwDot = millisecondPerMinute / dotsPerMinute;
    // Calculate the duration of a single Line as duration of 3 Dots
    _cwLine = _cwDot * 3;
    // Calculate the length of the interval between one character and another, theoretically is 3 Dots time, but 1 Dot is just present at the end of single char, then only 2 Dots are used
    _cwCharSpace = _cwDot * 2;
    // Calculate the length of the interval between one word and another, theoretically is 7 Dots time, but 1 Dot is just present at the end of single char, then only 6 Dots are used
    _cwWordSpace = _cwDot * 6;
}

CWLibrary::~CWLibrary()
{

}

void CWLibrary::sendMessage(char* cwMessage)
{
    int singleCharacter = *cwMessage++;

    while(singleCharacter != '\0')
    {
        // Check if is a SPACE or othe char
        if(singleCharacter == 32)
        {
            // Send a space char, that is wait for 7 Dots
            delay(_cwWordSpace);
        }
        else
        {
            // Get the index of morseCoded array for the current char
            int indexOfChar = singleCharacter-33;
            // Get from the morseCoded array the data to be trasmitted and the length of data
            byte data = morseCoded[indexOfChar][0];
            byte dataLen = morseCoded[indexOfChar][1];

            // Loop for data length
            for(int i=0;i<dataLen;i++)
            {
                // Get a single bit of data 1 is Line 0 is Dot
                boolean bitOfData = ((data << i) & 0b10000000);

                // Check if is Line or Dot
                if(bitOfData)
                {
                    // Send Line
                    _activateTrasmission();
                    delay(_cwLine);
                    _deActivateTrasmission();
                    delay(_cwDot);
                }
                else
                {
                    // Send Dot
                    _activateTrasmission();
                    delay(_cwDot);
                    _deActivateTrasmission();
                    delay(_cwDot);
                }
            }
            // Wait char space
            delay(_cwCharSpace);
        }
        
        // Get next char
        singleCharacter = *cwMessage++;
    }
}
