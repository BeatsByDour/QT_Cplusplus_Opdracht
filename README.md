# 🎮 Beasts Battle Game - Build Manual

## 📋 Prerequisites

### 1. **Install Qt and Qt Creator**
Download and install Qt from the official website:

- **Download Link**: [https://www.qt.io/download-open-source](https://www.qt.io/download-open-source)
- **Recommended Version**: Qt 6.5 or newer
- **During installation**:
  - Select "Qt Creator" (IDE)
  - Select at least one Qt version (e.g., Qt 6.5.0 MinGW 64-bit for Windows)
  - On Windows, check "MinGW" compiler
  - On macOS, check "Clang" compiler
  - On Linux, the default system compiler will be used

### 2. **Install Git** (for cloning the repository)
- **Windows**: Download from [https://git-scm.com/download/win](https://git-scm.com/download/win)
- **macOS**: Use Homebrew: `brew install git` or download from [https://git-scm.com/download/mac](https://git-scm.com/download/mac)
- **Linux**: 
  ```bash
  sudo apt update
  sudo apt install git
  ```

### 3. **Verify Installation**
After installation, verify both programs are installed:
```bash
git --version
# Should show something like: git version 2.x.x
```

---

## 🚀 Step-by-Step Setup Guide

### Method 1: Clone from GitHub (Recommended)

#### Step 1: Open Qt Creator
- Launch **Qt Creator** from your applications menu

#### Step 2: Clone the Repository
1. In Qt Creator, go to **File → New Project**
2. Select **Import Project → Git Clone**
3. Enter the repository URL:
   ```
   https://github.com/BeatsByDour/QT_Cplusplus_Opdracht.git
   ```
4. Choose a local directory for the project
5. Click **Clone**

#### Step 3: Configure the Project
1. Qt Creator will ask you to configure the project
2. Select the **Kit** (choose your Qt version with compiler, e.g., "Desktop Qt 6.5.0 MinGW 64-bit")
3. Click **Configure Project**

### Method 2: Download and Open Project

#### Step 1: Download the Project
```bash
# Using Git (recommended)
git clone  https://github.com/BeatsByDour/QT_Cplusplus_Opdracht.git
cd YOUR_REPOSITORY

# OR download as ZIP:
# 1. Go to GitHub repository
# 2. Click "Code" → "Download ZIP"
# 3. Extract the ZIP file
```

#### Step 2: Open in Qt Creator
1. Open **Qt Creator**
2. Go to **File → Open File or Project**
3. Navigate to the project folder
4. Select the **.pro file** (e.g., `CplusPlusTaak.pro`)
5. Click **Open**
6. Select the Kit when prompted
7. Click **Configure Project**

---

## 🛠 Building the Project

### Step 1: Select Build Configuration
1. In Qt Creator's left sidebar, click **Projects** (hammer icon)
2. Under **Build Settings**:
   - **Build directory**: Keep default or customize
   - **Build type**: Select "Debug" for development or "Release" for final build
3. Ensure the correct Kit is selected

### Step 2: Build the Project
1. Click the **Build** button (hammer icon) in the bottom left
2. Or use keyboard shortcut:
   - **Ctrl+B** (Windows/Linux)
   - **Cmd+B** (macOS)

### Step 3: Run the Application
1. Click the **Run** button (green play arrow) in the bottom left
2. Or use keyboard shortcut:
   - **Ctrl+R** (Windows/Linux)
   - **Cmd+R** (macOS)

---

## 🔧 Troubleshooting

### Common Issues and Solutions

#### 1. **"No valid kits found" error**
- **Solution**: Go to **Tools → Options → Kits**. Ensure a Qt version is detected. If not, run the Qt Maintenance Tool to install a kit.

#### 2. **Missing include files or libraries**
- **Solution**: Check the `.pro` file and ensure all dependencies are listed:
  ```qmake
  QT += core gui widgets
  ```

#### 3. **Build fails with CMake errors**
- **Solution**: 
  1. Clean the build: **Build → Clean All**
  2. Delete the build directory manually
  3. Reconfigure the project

#### 4. **Git clone fails on Windows**
- **Solution**: Use the GitHub Desktop app or download ZIP instead

#### 5. **Application crashes on startup**
- **Solution**: 
  - Check console output for error messages
  - Ensure all resource files exist (e.g., `gameStyle.qss`)
  - Run in Debug mode with breakpoints



## 🎯 Quick Test

To verify everything works:

1. **Clone and open the project** in Qt Creator
2. **Click Build** (should complete without errors)
3. **Click Run** (game should launch)
4. **Expected behavior**:
   - Start screen appears
   - Navigation between screens works
   - Battle mechanics function

---

## ⚡ Development Tips

1. **Clean build often**: Delete build folder if you encounter strange issues
2. **Use Git**: Commit frequently to track changes
3. **Debug mode**: Use Qt Creator's debugger to step through code
4. **Designer**: Double-click `.ui` files to open Qt Designer for GUI editing

---

## 🤝 Getting Help

If you encounter issues:

1. **Check Qt Creator's Compile Output** for specific error messages
2. **Verify all prerequisites** are installed correctly
3. **Search Qt documentation**: [https://doc.qt.io/](https://doc.qt.io/)

---

## 📝 Notes for Different Platforms

### Windows
- Use MinGW compiler (included with Qt installer)
- Ensure Visual C++ Redistributables are installed if using MSVC

### macOS
- Xcode command line tools may be required
  ```bash
  xcode-select --install
  ```

### Linux
- Install development packages:
  ```bash
  sudo apt install build-essential libgl1-mesa-dev
  ```

---

**Happy Coding!** 🎮✨

*This README will guide you from a clean PC to a running application in about 15-20 minutes.*