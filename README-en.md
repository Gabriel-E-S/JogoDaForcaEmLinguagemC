# Hangman Game in C

<div align="right">
  <a href="./README.md">🇧🇷 Português</a> | 🇺🇸 English
</div>
<br>

<div align="center">
  <img src="https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white" alt="C" />
  <img src="https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white" alt="Windows" />
  <img src="https://img.shields.io/badge/Code::Blocks-414141?style=for-the-badge&logo=codeblocks&logoColor=white" alt="CodeBlocks" />
</div>
<br>

Welcome! This repository holds a very special project: my first major practical development, built during my first year of college in 2023.

## 🎯 About the Project

The main focus of this application was to integrate different programming fundamentals into a functional, fun, and interactive game. At the time, it was a great challenge to move away from the classic "black console screen" and bring to life an application with a rich interface, persistent data, and native audio effects.

## ✨ Main Features

* **Graphical User Interface (GUI):** Screens, interactive menus, and the visual rendering of the hangman at each mistake, facilitating navigation and the player's experience.
* **File Handling (I/O):** Text file data reading and writing system. Used to manage the game's word bank (allowing new words to be added without changing the code) and/or saving the score history.
* **Sound System:** Natively integrated sound effects to provide audio feedback during correct guesses, mistakes, and at the end of the match (victory or defeat).

## ⚠️ Requirements and Important Notices

Due to the libraries used at the time of development to handle graphics and audio in pure C, this project has specific environment restrictions:

* **Operating System:** Works **exclusively on Windows**. The code uses native libraries and system calls (such as Windows sound and console manipulation) that are not compatible with Linux or macOS.
* **Recommended IDE:** The project was originally written and configured using **Code::Blocks**. To avoid library linking issues, it is highly recommended to open and compile it there.

## 💻 How to Run

1. Clone the repository to your local machine:
   ```bash
   git clone https://github.com/Gabriel-E-S/JogoDaForcaEmLinguagemC.git
   ```