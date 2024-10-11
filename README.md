# SpectraWise-Engine
Welcome to the **Spectrawise Rendering Engine**! This project began in mid-2023 with the aim of exploring OpenGL and Game Engine Architecture. Since then, it has been an exciting learning journey, and the engine is steadily progressing towards that goal.  
Finishing my studies this summer (2024) with a Bachelor's degree in Computer Science, specializing in Game Programming, the primary focus has now shifted to make it as stable and useful as possible. As a personal hobby project, the engine's development will continue periodically.  
Feel free to follow along or contribute to this journey!

## Table of Content
- [Requirements](#table-of-content)
- [Current State](#current-state-of-the-engine)
- [Personal Usage Info](#personal-usage-info)
    - [License](#license)
    - [Getting Started](#getting-started)
- [Bug Reporting](#bug-reporting)
    - [Known Issues](#known-issues)
- [Examples](#examples)
- [External Librarys](#external-librarys)
- [External Help](#external-librarys)
    - [CMAKE](#cmake)
    - [OpenGL](#opengl)
- [Changelog](#changelog)

## Requirements
- Cmake 3.2+
- Compiler that runs C++20

## Current state of the engine
[October 2024]  
The **Spectrawise Rendering Engine** is currently in an unstable state with limited features. While the fundamental components of a rendering engine are in place, it lacks user-friendly tools and interfaces.  
Over the next few months, the engine will undergo significant changes as I aim to implement key features. The goal is to evolve it into a basic, yet functional, rendering engine.  
Stay tuned for updates!

## Personal Usage Info
### License
The **Spectrawise Rendering Engine** is released under the [MIT License](LICENSE), which grants you full permission to use, modify, and distribute the software for personal, educational, or commercial purposes. This includes the ability to create games or other interactive applications using the engine.  
  
By using the engine, you are free to:
- Develop and distribute your own games or software built with the engine.
- Modify the engine's codebase to suit your project's specific needs.
- Contribute improvements or features back to the project (optional, but appreciated!).
  
Please note that while the engine is still in development, it may lack certain features or stability required for larger projects. However, you are welcome to use it as is or adapt it to your needs.
  
If you decide to release a game or product based on the engine, no attribution is required, but it’s always appreciated!
  
For more details, please refer to the [MIT License](LICENSE) included with this repository.

### Getting Started
To make a game or a rendering project you need to add your code in a folder inside of [projects](/projects). This new folder must include its own CMakeList.txt file, which will generate the project and solution. Execute CMake from the root directory, and subsequently open the solution in your intended destination folder.

## Bug Reporting
If you encounter any bugs or issues while using the engine, please report them by creating an issue in the repository.

### Known Issues
 - [] None

## Examples
Right now no Examples are provided as this is an early stage of development!

## External Librarys
Spectrawise uses:
- GLFW
- GLEW
- Dear ImGUI
- NanoVG
- Soloud
- GLM
<!--## Contribution
Maybe add 

-->
## External help
### CMake
[CMAKE Tutorials](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)

### OpenGL
[LearnOpenGL](https://learnopengl.com/)

## Changelog
<details>
  <summary>Click to expand the Changelog</summary>
  
### Version 0.1.0 - (2024-10-11)
- Updated Readme.md
- Updated Todo.md
- Started versioning.

</details>
