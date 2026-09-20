# unirtos-quecpython-demos

中文 | [English](README.md)

建议通过 `unirtos-cli` 的 Demo 流程使用本仓库，使工程创建、环境配置和编译始终使用一致的 SDK 与 QuecPython 组件版本。

## 功能说明

本仓库是 `EG800ZCN_LA` 上 `unirtos-quecpython` 的最小集成与硬件验证 Demo。

- 通过 `env_config.json` 拉取 `unirtos-quecpython` `1.1.0`，不复制 QuecPython 实现源码
- 通过组件的 `.unirtos_app_init` 注册自动启动运行时
- 固件下载后可通过 UART7/115200 进行 REPL 验证
- Python 业务应用、外设样例和产品逻辑由使用方工程实现

本 Demo 不会创建第二个任务，也不会直接操作 MicroPython VM。使用 `quecpython_exec_string()` 时必须先将请求投递到 QuecPython 运行时任务；它不是可从任意任务直接调用的跨任务执行接口。

## 硬件与软件要求

- EG800ZCN_LA 模组
- UniRTOS SDK `1.0.5`
- `unirtos-cli` `1.0.20`
- 符合 OpenCPU `0x90000`、CUST `0x48000`、LFS `0x79000` 分区布局的基础 `gccout.7z`
- 用于 REPL 验证的 UART7 串口终端

## 快速开始

### 1. 安装 UniRTOS 工具链

- [开发准备](https://www.quectel.com.cn/unirtos/docs?docs_page=快速上手/开发准备/开发准备.html)
- [交叉编译工具链安装](https://www.quectel.com.cn/unirtos/docs?docs_page=快速上手/环境搭建/环境搭建.html)
- 安装 Python 3、Git 和 `unirtos-cli`

```bash
python --version
git --version
unirtos-cli version
```

### 2. 使用 unirtos-cli 拉取 Demo

查看可用 Demo 和版本：

```bash
unirtos-cli ls-demos
```

创建本 Demo 工程：

```bash
unirtos-cli new -r unirtos-quecpython-demos -v 1.0.0
```

### 3. 进入工程并编译

```bash
cd unirtos-quecpython-demos-1.0.0
unirtos-cli env-setup
unirtos-cli build
```

`env-setup` 会按 `env_config.json` 拉取 UniRTOS SDK `1.0.5` 和 `unirtos-quecpython` `1.1.0`。只有声明该组件的应用才会编译并链接 QuecPython 运行时。

需要显式设置本次发布固件版本时，执行：

```bash
unirtos-cli build -m EG800ZCN_LA -v <firmware-version>
```

构建产物目录为：

```text
qos_build/release/<firmware-version>/
```

目录中包含 `at_command.hbinpkg`、`ap_application.bin`、`customer_app2.bin` 和 FlashTool 下载配置文件。

## REPL 验证

使用生成的 FlashTool 下载配置烧录发布包后，以 115200 波特率打开 UART7。确认交互提示符正常，并执行例如：

```python
import uos
print(uos.listdir('/'))
```

首轮硬件验证还应覆盖 `_boot.py`、LittleFS 挂载和脚本执行、旧模块导入，以及已启用的 GPIO/UART/I2C/SPI/Timer/RTC/WDT 能力。

## 配置说明

- `env_config.json` 是本 Demo 的板型、SDK 和组件依赖的唯一来源。
- 替换 `gccout.7z` 后，必须先执行 `unirtos-cli clean`，避免复用旧的 `qos_build/gccout` 解压缓存。
- `customer_app2.bin` 由组件提供并作为 CUST 镜像打包，不要手工复制到 `qos_tools`。

## 常用命令

```bash
# 刷新 SDK 和组件依赖
unirtos-cli env-setup

# 清除构建产物和已解压的 gccout 缓存
unirtos-cli clean

# 打开 SDK menuconfig
unirtos-cli menuconfig
```

## 技术社区

技术社区：https://forumschinese.quectel.com/c/66-category/66

## 贡献说明

- 提交前运行 `env-setup`、`build` 和 `clean`。
- Demo 的组件版本、SDK 版本和板型选择必须与 `env_config.json` 保持一致。
- 不要向本仓库复制 QuecPython 运行时源码或构建产物。
- 修改运行时启动、分区布局或固件打包时，记录板级和 REPL 验证结果。
