# Bare-Metal C Projects – AVR (Arduino Nano)

This repository contains all the code and supporting files from the **Bare-Metal C programming series** on YouTube. It will be updated continuously to reflect the latest concepts covered in the series.

📺 **Watch the full playlist here:**  
[https://www.youtube.com/watch?v=QiDCewIx4pQ&list=PLfmqEuMw4rP3NMBsl9IYPYWro1N4tYkzB](https://www.youtube.com/watch?v=QiDCewIx4pQ&list=PLfmqEuMw4rP3NMBsl9IYPYWro1N4tYkzB)

🌐 **GitHub Repository:**  
[https://github.com/Cosmic-Aerospace-Technologies/BareMetal-C-Project](https://github.com/Cosmic-Aerospace-Technologies/BareMetal-C-Project)

---

## 🛠 Requirements

- **Microcontroller:** Arduino Nano (ATmega328P)
- **Software:** PlatformIO (VSCode extension)
- **Toolchain:** AVR-GCC (handled automatically by PlatformIO)

---

## 🚀 Getting Started

### 1. Clone the repository:

```bash
git clone https://github.com/Cosmic-Aerospace-Technologies/BareMetal-C-Project.git
cd BareMetal-C-Project
```
### 2. Change to the Old bootloader (If you have the old one that is):
Go to the platformIO.ini file and replace with:
```bash

[env:nanoatmega328]
platform = atmelavr
board = nanoatmega328
framework = arduino

```
