# MindMerp
This is a very basic mind mapping software that allows you to create a node, type an idea into it, and drag out other nodes for related thoughts/ideas. It's an thought/idea organization tool.
The beauty of this is that it's so basic at this point, so if any dev wants to come by and add to it, there's plenty opportunity. I plan on updating it every so often.
Any code that isn't Qt is entirely free to take and do what you want with it, with Qt code it's of course required to follow whatever guidelines apply, I believe it's GPL, I went with the GPL 3 license
because of that, the Qt code I used is fairly minimal in terms of the library's functionality, the only UI elements I used from it were QWindow, QTextEdit, QColorDialog and the one for selecting files for
opening and saving. I had to use QScreen and the QPainter APIs as well and that's about it, the rest of the code is my own and you can do whatever you want with that, even take it and use it in proprietary 
software if you want I don't really care, licensing was never my avenue of expertise nor concern, I just want to share my software.


::INSTALLING
Installation is quick and easy,
    -------------------------
    just run: bash install.sh
    -------------------------
and it'll handle the rest from there.
If your distro does not have sudo then you'll have to edit install.sh and replace it
with what your distro uses to gain root access.
Once you get it running though it's a quick and easy process.
Installing isn't really necessary however, you can run it right in the directory it came in and create 
your own shortcuts and all that however you prefer to try it first.



::UNINSTALLING
Uninstalling should be doable the usual way.
If your system's uninstaller is unreliable I included an uninstall script that'll get rid of mindmerp and everything that came with it.
    --------------------------------------
    Just run: bash uninstall.sh to use it.
    --------------------------------------
If your distro does not have sudo you will have to edit uninstall.sh in order to replace it with the command which
gives you root access.
You can also choose to uninstall manually if you for whatever reason prefer.
Here are the files to get rid of just so you can know what's on your system, they're listed during installation as well.
    -----------------------------------------------------
    /usr/local/bin/mindmerp
    /home/<username>/.local/share/mindmerp
    /home/<username>/.local/share/mindmerp/guidedtour.mmf
    -----------------------------------------------------
These three files are all that get added to your system during installation.



::COMPILATION
So this is a C++ project using g++ (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0 for the compiler 
and I also used the Qt 6.19.1 library for windowing.
(#1): The [project] directory has everything set up to where you should just be able to type make in the terminal
and it'll handle the rest.
(#2): The [source] directory is just the raw code alone, cause I know the project directory is gonna be messy
with object files and source/header files that qmake adds to allow "make" to work, and maybe you just wanted to
see the original code by itself, that's what this directory is for.



::LICENSE STUFF
It's FOSS of course,
Do whatever you like with the Qt parts of the code so long as it follows GPL3 or whatever license is actually necessary.
I'm new to distributing home made software on Linux so the license issue just isn't something
I've had to think about in the past, I'm not even sure I did it right this time with the licensing
issue but I made an honest attempt either way.
As far as my code apart from the use of Qt-specific code, do what you want with that, it's up for grabs.
You don't even have to credit me for it if you use it in proprietary software, as stated at the beginning of this
document, I don't care.


::INTRO TO CODE OVERVIEW
As far as the code itself goes, I tried to make it as clean as possible, there's a rough edge or two 
here and there but this is probably the cleanest most organized and abstracted code I've ever written.
My aim from the beginning was to really milk C++'s OOP capabilities for the first time, I used to
just code using a more plain C dialect.



::MINIMAL CODE OVERVIEW
The *_events.cpp files are where you'll have the best view of the event system for the few UI elements.
globals.h and globals.cpp have a bunch of classes, and of course a GLOBALS class
with all of the global variables in it, a single instance of this class is declared in main.cpp and 
used extensively throughout the program.
MindMerp basically does everything the main() function would have done, I didn't even need
to make an abstraction here but I really liked how much neater it made the code look imo, more organized.
There's like 20something files full of fairly small functions pieced together in classes among the files.
Because I enjoy making libraries to such an extent, I even made my own Color, Rect, and Point classes.
I don't even really know what posessed me to go that far with it, but my Image and FileIO classes
are neat imo, I'll probably reuse those in other projects. If ya like them feel free to use them.



::OUTRO
This program is primed for functionality additions, as it is pretty much in its most basic form,
very minimalistic.
If I worked for KDE I would have called this program kmindmap, really wanted to name it that but 
I don't work for KDE, I'm just some indie dev trying to put out some free software into the world
that I would find useful, I'd really like it if a fellow tinkerer got ahold of this and felt like
adding to it and making it something awesome.



::CONTACT
You can get ahold of me on discord if ya want, I love talking code and I'll gladly answer questions
about this project if asked.
My discord ID is: shreddykrueger4
