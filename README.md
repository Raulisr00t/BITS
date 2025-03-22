# Windows Service -> BITS File Downloader 

This is a simple **Windows C++ program** that downloads a file using **Background Intelligent Transfer Service (BITS)**.  
It downloads a file from a given URL and saves it to the user's **Temp** directory.

## 📌 Features
- Uses **BITS API** for efficient background file downloads.
- Saves the file to `C:\Users\<username>\AppData\Local\Temp\15mb.bin`.
- Displays download progress and handles errors gracefully.

## 🛠️ Requirements
- Windows OS (BITS is a Windows service).
- Microsoft C++ Compiler (MSVC) or MinGW.
- Windows SDK (for `Bits.h` and `atlcomcli.h`).

## 🚀 How to Build & Run
### **1️⃣ Compile the Code**
Using **MSVC (Visual Studio Developer Command Prompt)**:
```powershell
cl /EHsc /D_CRT_SECURE_NO_WARNINGS BITS_Downloader.cpp
```
Run the Executable
```powershell
.\BITS.exe
```

### How It Works
1.Retrieves the User's Temp Path (USERPROFILE environment variable).
2.Creates a BITS Job to download the file from the URL.
3.Monitors Download Progress (dots ...... show ongoing transfer).
4.Completes the Job when download finishes successfully.
5.Handles Errors and displays a detailed error message if the download fails.

### References
Pavel Yosifovich – Windows Internals Expert & Author
🔗 Official Website
🔗 Windows Internals Book

## License
This project is open-source. Feel free to modify and use it as needed.
