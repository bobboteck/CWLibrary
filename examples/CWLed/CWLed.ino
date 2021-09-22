/*
 * Name          : CWLed.ino
 * @author       : Roberto D'Amico (@Bobboteck)
 * Last modified : 22.09.2021
 * Revision      : 1.0.0
 *
 * Modification History:
 * Date         Version     Modified By     Description
 * 2021-09-22   1.0.0       Roberto D'Amico Code Example for CWLibrary that use Arduino Built-in led to send message
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

// Define message to be sended
const char textToSend[] = "CQ CQ DE IU0PHY";

// Declare the function used by the callback
void activeAction(void);
void noactiveAction(void);

// Inizialize the CW Library
CWLibrary cw = CWLibrary(10, activeAction, noactiveAction);

void setup()
{
    // Setup the built-in led
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
    // Send the message
    cw.sendMessage(textToSend);

    delay(500);
}

// Function of callback in active status
void activeAction()
{
    digitalWrite(LED_BUILTIN, HIGH);
}

// Function of callback in no active status
void noactiveAction()
{
    digitalWrite(LED_BUILTIN, LOW);
}
