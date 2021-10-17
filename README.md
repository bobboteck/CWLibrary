# CWLibrary

>Yet another library for generating CW signals?

**Yes**, but it is not limited to turning on a LED, or to controlling a single I/O pin.
**CWLibrary** uses two callbacks to user-defined functions, the two functions represent the state in which a signal is transmitted and the state in which it is not transmitted. In this way, the user can indicate anything in the functions, from simple commands for switching on or off a LED to even more complex commands or for objects other than common Arduino peripherals.

## Thanks For Your Support

If you like this library and want to support the development, please put a star on this project to encourage it.

## What is the CW?

**CW** stands for **Continuos Wave**, in short it is the way that *radio amateurs* use to indicate radio broadcasts in **Morse**. This library is nothing more than a tool to be able to transmit *Morse* signals with the microcontroller.
You can send a message in *Morse*, using: a light, a sound or a radio frequency signal.
Morse is a "binary" communication system, it is based on the **presence** or **absence** of the signal (for example: light on, light off) and on the duration of these.
Signals can be short or long, respectively called dots or lines. Morse code establishes a specific sequence of these for each character, for example we have:

A, that corresponds to: LINE DOT
B, that corresponds to: LINE DOT DOT DOT
C, that corresponds to: LINE DOT LINE DOT
... and so on.

There is a specific time interval between a single element (dot or line), just as there is one between one character and another, and between two words.
> For more information see the [Wiki page](https://en.wikipedia.org/wiki/Continuous_wave).

## Features of this library

This library, allows you to define a function that will be called when the signal must be **present** (for example: light on) and another function that must be called when the signal must be **absent** (for example: light off).

The library **automatically** manages the conversion from character to Morse code, always **automatically** establishes the timing of the signals, by calculating them using the PARIS method.

## How to use

Simply you can install it from the **Arduino Library Manager** in the **Arduino IDE**. After that, you need to add the library reference at the top of your code, as shown below.

```c++
#include "CWLibrary.hpp"
```

Now you can define an array of *char* with the string message you wont to send.

```c++
const char textToSend[] = "CQ CQ DE IU0PHY";
```

You need to declare the function called for the **presence** or **absence** of signal, in top of your code.

```c++
void activeAction(void);
void noactiveAction(void);
```

Now you can define an instance of class CWLibrary.

```c++
CWLibrary cw = CWLibrary(10, activeAction, noactiveAction);
```

The first parameter, numerical, is used to indicate the transmission speed in WPM, as previously mentioned the library automatically calculates the transmission times with the PARIS method, according to the number indicated in this parameter.
The other two parameters are used to indicate which function must be called in the case of **presence** or **absence** of a signal.

The two functions, for example, can be used to control the LED connected to pin 13 on Arduino boards.
The function associated with the **presence** of the signal could be, for example, like the following one where the LED is turned on.

```c++
void activeAction()
{
    digitalWrite(LED_BUILTIN, HIGH);
}
```

While the function associated with the **absence** of the signal could be, for example, like the following one where the LED is turned off.

```c++
void noactiveAction()
{
    digitalWrite(LED_BUILTIN, LOW);
}
```

The last step to perform, to transmit the message, is to call the method that carries out the transmission. This call can be placed anywhere in your code.

```c++
cw.sendMessage(textToSend);
```

The complete code of this [example](https://github.com/bobboteck/CWLibrary/blob/master/examples/CWLed/CWLed.ino) can be found in the examples folder of this repository.

## Supported chars

Alphabetic characters are supported in uppercase only

```txt
A B C D E F G H I J K L M N O P Q R S T U V W X Y Z
```

The numbers from 0 to 9

```txt
0 1 2 3 4 5 6 7 8 9
```

And a set of special characters

```txt
" ' ( ) , - . / : = ? @
```

## Upcoming Features

Below is a list of features designed, but to be implemented:

- Implement a method to set a baud rate other than that defined in the costructor

## How to contribute

You can contribute to the project by putting a Star on it, but also by opening Issues that are to request new features or to report bugs.

### Request a feature

Simple by using a Issue and compiling the template for a *Feature request*.

### Report a bug

Simple by using a Issue and compiling the template for a *Bug report*.
