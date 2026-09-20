# unirtos-quecpython-demos

[中文](README.zh.md) | English

This repository is recommended to be used through the `unirtos-cli` demo workflow so project creation, environment setup, and compilation use the same versions of the SDK and QuecPython library.

## Feature Description

This is the minimal integration and hardware-validation demo for `unirtos-quecpython` on `EG800ZCN_LA`.

- Pulls `unirtos-quecpython` `1.1.0` through `env_config.json`; it does not copy QuecPython implementation source into the demo
- Starts the runtime through the component's `.unirtos_app_init` registration
- Provides UART7 REPL validation at 115200 baud after firmware download
- Leaves Python applications, peripheral samples, and production application logic to the user project

The demo deliberately does not create a second task or call into the MicroPython VM. A request to `quecpython_exec_string()` must be marshalled to the QuecPython runtime task before it is made; it is not a general-purpose cross-task execution API.

## Hardware and Software Requirements

- EG800ZCN_LA module
- UniRTOS SDK `1.0.5`
- `unirtos-cli` `1.0.20`
- A compatible `gccout.7z` base archive declaring OpenCPU `0x90000`, CUST `0x48000`, and LFS `0x79000`
- UART7 connected to a serial terminal for REPL validation

## Quick Start

### 1. Install the UniRTOS toolchain

- [Development Preparation](https://www.quectel.com.cn/unirtos/docs?docs_page=快速上手/开发准备/开发准备.html)
- [Install the Cross-Compilation Toolchain](https://www.quectel.com.cn/unirtos/docs?docs_page=快速上手/环境搭建/环境搭建.html)
- Install Python 3, Git, and `unirtos-cli`

```bash
python --version
git --version
unirtos-cli version
```

### 2. Pull the demo using unirtos-cli

List available demos and versions:

```bash
unirtos-cli ls-demos
```

Create this demo project:

```bash
unirtos-cli new -r unirtos-quecpython-demos -v 1.0.0
```

### 3. Enter the project and build

```bash
cd unirtos-quecpython-demos-1.0.0
unirtos-cli env-setup
unirtos-cli build
```

`env-setup` obtains UniRTOS SDK `1.0.5` and `unirtos-quecpython` `1.1.0` as declared in `env_config.json`. The runtime is compiled and linked only for applications that declare the library.

To set the release firmware version explicitly, use:

```bash
unirtos-cli build -m EG800ZCN_LA -v <firmware-version>
```

The output is located at:

```text
qos_build/release/<firmware-version>/
```

The directory contains `at_command.hbinpkg`, `ap_application.bin`, `customer_app2.bin`, and FlashTool download configuration files.

## REPL Validation

Download the release package with the generated FlashTool configuration, then open UART7 at 115200 baud. Confirm that the prompt is interactive and run a small check such as:

```python
import uos
print(uos.listdir('/'))
```

The first hardware-validation pass should also cover `_boot.py`, LittleFS mount and script execution, legacy module imports, and the enabled GPIO/UART/I2C/SPI/Timer/RTC/WDT capabilities.

## Configuration Notes

- `env_config.json` is the single source of the board, SDK, and library dependency used by this demo.
- Replacing `gccout.7z` requires `unirtos-cli clean` before the next build so the old `qos_build/gccout` extraction is not reused.
- `customer_app2.bin` is supplied by the library and is packaged as the CUST image; do not manually copy it into `qos_tools`.

## Common Commands

```bash
# Refresh SDK and library dependencies
unirtos-cli env-setup

# Clean build output and extracted gccout cache
unirtos-cli clean

# Open the SDK menu configuration
unirtos-cli menuconfig
```

## Technical Community

Technical Community: https://forumschinese.quectel.com/c/66-category/66

## Contribution Guidelines

- Run `env-setup`, `build`, and `clean` before submitting a change.
- Keep the demo's library version, SDK version, and board selection aligned with `env_config.json`.
- Do not copy QuecPython runtime sources or build output into this repository.
- Record the board and REPL validation result when changing runtime startup, flash layout, or firmware packaging.
