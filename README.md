# BSOD

A Windows application that triggers a Blue Screen of Death (BSOD) by leveraging native Windows APIs

## 📋 Overview

This C program uses undocumented Windows kernel functions to intentionally trigger a system crash. It calls `RtlAdjustPrivilege()` to enable the shutdown privilege and then invokes `NtRaiseHardError()` to raise a fatal system error.

## 📥 Installation

The compiled `x86` executable is available on the [**releases page**](https://github.com/madkarmaa/BSOD/releases/latest).

## ⚠️ Warning

This application will immediately crash your system. **Do not run on production systems or machines with unsaved work**. Data loss may occur.

## 🔨 Building

To compile from source:

1. Use [Visual Studio](https://visualstudio.microsoft.com/vs/community/) with C/C++ development tools
2. Open `BSOD.slnx` and build the project in **Release (x86)** mode
3. The executable will be generated in the `Release` folder

<small><i>Use at your own risk</i></small>