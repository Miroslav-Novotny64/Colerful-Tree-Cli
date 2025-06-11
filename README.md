# 🌳 Colorful Tree Utility

A visually enhanced directory tree viewer written in C, featuring colorful icons and syntax highlighting for different file types. This cross-platform CLI tool brings modern visual appeal to traditional directory listing, perfect for developers who appreciate both functionality and aesthetics.

## Example

IMG

## ✨ Features

- **🎨 Colorful Output**: Rich ANSI color coding for different file types and directories
- **📁 Smart Folder Recognition**: Special icons for common development folders (`src`, `node_modules`, `dist`, etc.)
- **🔧 Extensive File Type Support**: Icons for 50+ file extensions including:
    - Programming languages (C, C++, Python, JavaScript, TypeScript, Rust, Go, etc.)
    - Web development files (HTML, CSS, SCSS, Vue, React)
    - Database files (SQL, SQLite)
    - Configuration files (JSON, YAML, TOML, ENV)
    - Build system files (Makefile, CMake, Ninja, Docker)
    - Package managers (npm, yarn, cargo)
- **🚀 Lightweight**: Fast C implementation with minimal dependencies
- **🖥️ Cross-Platform**

## 📋 Requirements

- **GCC Compiler**
- **POSIX-compliant system** (Linux, macOS, WSL on Windows)
- **Terminal with Unicode support** for proper icon display

## 🚀 Installation

### Download and Build

1. **Clone or download** the source files:
2. **Build the executable**:
```bash
    gcc main.c -o tree
```
3. **Make executable**
```bash
    chmod +x tree
```
4. **Run the compiled binary**: `./tree`
5. **Optional: Install system-wide**:
```bash
    sudo cp tree /usr/local/bin/
```


## 📝 Usage
Just run the executable in the desired directory.
```bash
    ./tree
```


## 🤝 Contributing

Feel free to submit issues and enhancement requests! This utility is designed to be easily extensible for new file types and folder patterns commonly used in development environments.

## 📝 License

This project is open source. Feel free to use, modify, and distribute according to your needs.
