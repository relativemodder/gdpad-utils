# GDPad Tool

Simple utility for configuring brand new device for playing Geometry Dash.


## Building

To build this tool, you need:

- CMake (3.29.0 or higher)
- C++ compiler (GCC or Clang on Linux, Visual Studio on Windows)
- Git (assuming you're using it for cloning)
- Flatpak and flatpak-builder (if you want to build a Flatpak package) with org.freedesktop.Sdk installed (--user mode recommended)


### Preparing

**Clone the repo**

```bash
git clone https://github.com/relativemodder/gdpad-utils --recursive
```

Why do we need `--recursive`? Because we're using submodules for `vcpkg`.



**Bootstrap vcpkg**

```bash
cd gdpad-utils
cd vcpkg
./bootstrap-vcpkg.sh # or ./bootstrap-vcpkg.bat on Windows
```



**Set up vcpkg integration with CMake**

```bash
cd ..
./vcpkg/vcpkg integrate install --user
```

This will configure CMake to use vcpkg for package management.


### Building


**Run CMake Configuration**

```bash
cmake -Bbuild
```


**Run CMake Build**

```
cmake --build ./build --config Release --target all --
```


Run this program using

```bash
./build/gdpadtool
```

Voila! You should now be able to use the gdpadtool program built from source.


### Flatpak part (optional)

**Installing dependencies**

According to the Flatpak documentation, you need to install the following repo userwide:

```bash
flatpak remote-add --if-not-exists --user flathub https://dl.flathub.org/repo/flathub.flatpakrepo
```


**Building**


```bash
cmake -Bbuild -DFLATPAK_PATH=/home/your/path/to/flatpak
```

```
cmake --build ./build --config Release --target all --
```


**Build this if flatpak runtime was installed in user mode (RECOMMENDED):**

```bash
flatpak-builder --force-clean --user --install-deps-from=flathub --repo=repo --install flatpak org.gdpad.tool.yml
```

Run this flatpak using

```bash
flatpak run org.gdpad.tool
```

Voila! You have now successfully built and run the tool using Flatpak.