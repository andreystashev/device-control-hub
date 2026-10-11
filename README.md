# Device Control Hub

A **C++/Qt desktop prototype** for receiving device telemetry, plotting measurements, showing positions on a map, and reviewing recorded data and images. It brings network and serial communication into one control panel.

The application uses custom binary packet layouts and device-specific commands. It is an integration project rather than a generic device-management product.

## Preview

<img width="1071" alt="Device Control Hub desktop interface" src="https://github.com/andreystashev/device-control-hub/assets/70208784/8bb6d534-e4c2-42ba-ad30-3b286721e88b" />

<details>
<summary>More screenshots</summary>

<img width="1072" alt="Device Control Hub interface view" src="https://github.com/andreystashev/device-control-hub/assets/70208784/8e7cb9e7-eb5a-4ff4-86af-ba39b2f79ed0" />

<img width="1079" alt="Device Control Hub interface view" src="https://github.com/andreystashev/device-control-hub/assets/70208784/7aa016d3-96a0-42c9-9516-ea0c7e4b9da3" />

<img width="1076" alt="Device Control Hub interface view" src="https://github.com/andreystashev/device-control-hub/assets/70208784/0acd8aae-629d-4862-960d-b23349f0eb92" />

</details>

## Features

- TCP and UDP telemetry paths and a Qt Serial Port terminal.
- Device selection and command controls.
- Live and recorded telemetry plots using bundled QCustomPlot.
- Map views and device trajectories built on Qt's Slippy Maps example.
- Local telemetry recording and subsequent review.
- Image reception and chronological playback of saved images.

The repository contains no implemented SSH client. Network transport should not be interpreted as encrypted or authenticated.

## Build

Use a **Qt 5 desktop kit**, a C++11-capable compiler, and qmake. The project declares these Qt modules:

`Core`, `Gui`, `Widgets`, `Network`, `SerialPort`, `OpenGL`, `Xml`, and `PrintSupport`.

Qt 6 compatibility has not been established. Qt Creator is the simplest way to configure the compiler and module paths:

1. Clone the repository.
2. Open [controlpanel.pro](controlpanel.pro) in Qt Creator.
3. Select a Qt 5 desktop kit with the required modules.
4. Build and run the application.

With the selected Qt kit's `qmake` and compiler tools in your PATH, a command-line build on macOS/Linux follows the same project definition:

```bash
git clone https://github.com/andreystashev/device-control-hub.git
cd device-control-hub
mkdir -p build
cd build
qmake ../controlpanel.pro
make -j2
```

This repository does not provide prebuilt releases or an automated build matrix. A clean build with a current Qt 5 kit still needs verification.

## Device integration

To connect a real device or a simulator, inspect these files before sending data:

| File | Purpose |
| --- | --- |
| [messages.h](messages.h) | Packed packet structures, telemetry labels, and device count |
| [networkcreator.cpp](networkcreator.cpp) | TCP/UDP connections and incoming-data handlers |
| [guicreator.cpp](guicreator.cpp) | GUI wiring, command handlers, and telemetry servers |
| [terminalCreator.cpp](terminalCreator.cpp) | Serial-port communication |
| [terminalSettings.cpp](terminalSettings.cpp) | Port selection and serial configuration |

The current configuration has three device slots. The GUI telemetry servers use TCP ports `18002`, `18004`, and `18006`; other network paths have their own hardcoded endpoints. These are code-level defaults, not a configurable discovery service. Match the packet layout, endpoint, and command format to your device.

The application opens full-screen. Recordings and images use relative paths under `flights/`, and other file operations use `files/`. Set the working directory deliberately when running from Qt Creator. A compatible device or simulator is required for live data; none is bundled here.

## Project layout

| Component | Responsibility |
| --- | --- |
| `guicreator.*`, `guicreator.ui` | Main desktop interface |
| `networkcreator.*` | Network communication |
| `terminalCreator.*`, `terminalSettings.*`, `terminalConsole.*` | Serial terminal |
| `graphcreator.*`, `qcustomplot.*` | Telemetry charts |
| `mapcreator.*`, `mapzoom.*`, `maplight.*` | Map rendering and interaction |
| `filecreator.*`, `playercreator.*` | Recording and playback |
| `messages.h` | Packet definitions |
| `pics/`, `resources.qrc` | Bundled interface assets |

## Project status

This prototype demonstrates Qt GUI composition and device-data integration. The next engineering steps are a verified clean build, configurable endpoints, a packet simulator, and automated protocol tests. It has no automated test suite, and its behavior with arbitrary or malformed device traffic has not been validated.

Bundled QCustomPlot 2.0.0 retains its original copyright and GPL notices in `qcustomplot.h` and `qcustomplot.cpp`. No separate project-wide `LICENSE` file is present.



