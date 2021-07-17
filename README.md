GRID ][
=======

The goal of this project is to conceive a full featured 2D game engine in principle using the RayLib base library with some added custom external.

The external will compile as partof RayLib to supply extra features such as more audio functionalities and more control over IO and OpenGL.

The core development is done using mostly C99 syntax and libraries and keep the code as clean and logical as possible.

The features of this engine are as follows:

2D Grid system:
- 2D multi-layer page system that works with textures and OpenGL
- Multiple features such as tileset skew, rotation, shadow, lines system, reverse, color blending and more
- Full featured sprite system
- Priority based display
- Particle system
- Collision system
- Basic physics
- and much more

Audio System:
- Work with WAV, MP3, and XM module files
- Allow jumping in pattrn order on XM module
- Allow multiple XM files to play at once
- Control over; low pass, band pass, high pass filtering
- EQ control
- Basic synthesizer with pure waves and noise

Video System:
- Allow for shader effects
- Palette driven capabilities for color cycling and easy color swapping
- Proper control over the display hardware; resolution, refresh (no hiccups or stuttering)
- Proper application focus management

Game Engine:
- State driven processing for; 2D grid / cells, sprites, permissions, program flow control, video, audio, etc...
- Game scripting
- In-runtime level building
- tileset and sprite editing
- all assets merged into EXE binary and compressed
- Cut down as much as possible on false positives for online tools such as virustotal
- Aimed at best performance and animation smoothness
- Excellent gameflow management
- Full featured command line terminal system
- Extensive debugging abilities

As of mid July 2021 - Grid ][ is roughly 15% done.  Development is going smoothly yet there is a lot of heavy lifting to do before it becomes useful to anyone.

Also I am planning to have it ported to C++ and have multi-threading, in some distant future.

A game engine is a lot of work so I do wish that people following this project to be armed with patience before wanting to work using it.  And of course you may contact me for any type of Game Engien oriented topics.

m4ntr0n1c
