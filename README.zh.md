# unirtos-quecpython-demos

这是 `unirtos-quecpython` v1.1.0 的最小验证工程，仅支持 EG800ZCN_LA。工程不复制组件源码，只通过 `env_config.json` 固定依赖组件 `1.1.0`。

组件通过应用初始化注册自动启动 QuecPython；本 Demo 不再创建第二个任务去操作 MicroPython VM。烧录后通过 UART7/115200 REPL 验证 `_boot.py`、LittleFS、旧模块导入和板级外设能力。在请求被投递到 QuecPython 主任务前，`quecpython_exec_string()` 不能从任意 UniRTOS 任务直接调用。

```text
unirtos-cli new -r unirtos-quecpython-demos -v 1.0.0
cd unirtos-quecpython-demos-1.0.0
unirtos-cli env-setup
unirtos-cli clean
unirtos-cli build
```
