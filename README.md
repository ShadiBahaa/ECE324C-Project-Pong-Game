# ECE324C Project: Pong Game

## Table of Contents
- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Contributing](#contributing)
- [Acknowledgements](#acknowledgements)

## Introduction
This project is a recreation of the classic Pong game, developed as part of the ECE324C course. The game is implemented in C and Assembly, showcasing a combination of hardware and software interfacing skills. We Utilized the TM4C123GH6PM microcontroller to bring this game to life, integrated Nokia 5110 display for game visuals and configured push buttons and serial communication for player inputs and multiplayer communication.

## Features
- Classic Pong gameplay with two paddles and a ball.
- Supports both single-player and multiplayer modes.
- Implemented non-human opponent for challenging single-player gameplay.
- Leveraged UART communication for connectivity in multiplayer mode.
- Real-time score display.
- Responsive controls.
- Software Drivers Created:  GPIO, GPTM, UART, SSI, NVIC, Nokia 5110

## Installation
To set up the project locally, follow these steps:

1. **Clone the repository:**
    ```bash
    git clone https://github.com/MustafaShokry/ECE324C-Project-Pong-Game.git
    cd ECE324C-Project-Pong-Game
    ```

2. **Build the project:**
    - Ensure you have Keil IDE installed.
    - Create A new project in Keil and add the project files to it.
    - For connections, check the configuartion files of the drivers and application layer.
    - Enjoy!

## Usage:
Please check the PDF guide titled "Pong_Game" to know how to play the game, which software drivers we used, and how we implemented the logic. 

## Contributing:
Contributions are welcome! Please follow these steps to contribute:
- Fork the repository.
- Create a new branch:
    ```bash
    git checkout -b feature-branch
    ```
- Commit your changes:
    ```bash
    git commit -m 'Add new feature'.
    ```
- Push to the branch:
    ```bash
    git push origin feature-branch
    ```
- Open a pull request.

## Acknowledgements:
Thanks for my colleagues: Mostafa Shokry, Mostafa Abdullah, Eman Mohamed, and Marwan Mohamed for their efforts which made this project incredible!

