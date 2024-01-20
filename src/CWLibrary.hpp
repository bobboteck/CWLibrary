/*
 * Name          : CWLibrary.hpp
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
#ifndef CWLibrary_H
#define CWLibrary_H

#include "Arduino.h"

class CWLibrary
{
    const uint8_t cwParisDotsLength = 50;
    const uint16_t millisecondPerMinute = 60000;
    const unsigned char morseCoded[58][2] = {
                            // Index> [ASCII Dec] Simbol [Morse]
        { 0b00000000, 0 },  // 0> [33] ! []
        { 0b01001000, 6 },  // 1> [34] " [.-..-.]
        { 0b00000000, 0 },  // 2> [35] # []
        { 0b00000000, 0 },  // 3> [36] $ []
        { 0b00000000, 0 },  // 4> [37] % []
        { 0b00000000, 0 },  // 5> [38] & []
        { 0b01111000, 6 },  // 6> [39] ' [.----.]
        { 0b10110000, 5 },  // 7> [40] ( [-.--.]
        { 0b10110100, 6 },  // 8> [41] ) [-.--.-]
        { 0b00000000, 0 },  // 9> [42] * []
        { 0b00000000, 0 },  //10> [43] + []
        { 0b11001100, 6 },  //11> [44] , [--..--]
        { 0b10000100, 6 },  //12> [45] - [-....-]
        { 0b01010100, 6 },  //13> [46] . [.-.-.-]
        { 0b10010000, 5 },  //14> [47] / [-..-.]

        { 0b11111000, 5 },  //15> [48] 0 [-----]
        { 0b01111000, 5 },  //16> [49] 1 [.----]
        { 0b00111000, 5 },  //17> [50] 2 [..---]
        { 0b00011000, 5 },  //18> [51] 3 [...--]
        { 0b00001000, 5 },  //19> [52] 4 [....-]
        { 0b00000000, 5 },  //20> [53] 5 [.....]
        { 0b10000000, 5 },  //21> [54] 6 [-....]
        { 0b11000000, 5 },  //22> [55] 7 [--...]
        { 0b11100000, 5 },  //23> [56] 8 [---..]
        { 0b11110000, 5 },  //24> [57] 9 [----.]

        { 0b11100000, 6 },  //25> [58] : [---...]
        { 0b00000000, 0 },  //26> [59] ; []
        { 0b00000000, 0 },  //27> [60] < []
        { 0b10001000, 5 },  //28> [61] = [-...-]
        { 0b00000000, 0 },  //29> [62] > []
        { 0b00110000, 6 },  //30> [63] ? [..--..]
        { 0b01101000, 6 },  //31> [64] @ [.--.-.]

        { 0b01000000, 2 },  //32> [65] A [.-]
        { 0b10000000, 4 },  //33> [66] B [-...]
        { 0b10100000, 4 },  //34> [67] C [-.-.]
        { 0b10000000, 3 },  //35> [68] D [-..]
        { 0b00000000, 1 },  //36> [69] E [.]
        { 0b00100000, 4 },  //37> [70] F [..-.]
        { 0b11000000, 3 },  //38> [71] G [--.]
        { 0b00000000, 4 },  //39> [72] H [....]
        { 0b00000000, 2 },  //40> [73] I [..]
        { 0b01110000, 4 },  //41> [74] J [.---]
        { 0b10100000, 3 },  //42> [75] K [-.-]
        { 0b01000000, 4 },  //43> [76] L [.-..]
        { 0b11000000, 2 },  //44> [77] M [--]
        { 0b10000000, 2 },  //45> [78] N [-.]
        { 0b11100000, 3 },  //46> [79] O [---]
        { 0b01100000, 4 },  //47> [80] P [.--.]
        { 0b11010000, 4 },  //48> [81] Q [--.-]
        { 0b01000000, 3 },  //49> [82] R [.-.]
        { 0b00000000, 3 },  //50> [83] S [...]
        { 0b10000000, 1 },  //51> [84] T [-]
        { 0b00100000, 3 },  //52> [85] U [..-]
        { 0b00010000, 4 },  //53> [86] V [...-]
        { 0b01100000, 3 },  //54> [87] W [.--]
        { 0b10010000, 4 },  //55> [88] X [-..-]
        { 0b10110000, 4 },  //56> [89] Y [-.--]
        { 0b11000000, 4 }   //57> [90] Z [--..]
    };

    typedef void (*CallbackFunction)(void);

    private:
        uint8_t _wpm;
        uint16_t _cwDot;
        uint16_t _cwLine;
        uint16_t _cwCharSpace;
        uint16_t _cwWordSpace;
        CallbackFunction _activateTrasmission;
        CallbackFunction _deActivateTrasmission;

    public:
        /**
         * Costructor of CWLibrary
         * 
         * @param wpm Set the speed in word for minute
         * @param activateTrasmission The callback at mothod for the active state of trasmission
         * @param deActivateTrasmission The callback at mothod for the non active state of trasmission
         */
        CWLibrary(uint8_t wpm, CallbackFunction activateTrasmission, CallbackFunction deActivateTrasmission);
        ~CWLibrary();

        /**
         * Send morse message
         * 
         * @param cwMessage The text message you need to send
         */
        void sendMessage(char* cwMessage);
};

#endif
