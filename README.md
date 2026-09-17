# unirtos-quecpython-demos

Minimal UniRTOS application for `unirtos-quecpython` v1.1.0 on EG800ZCN_LA. It contains no QuecPython implementation source: the runtime is pulled through `env_config.json` and started by the component's application-init registration.

The component starts the runtime through its application-init registration; this demo deliberately creates no second task that calls into the MicroPython VM. Continue validation through the UART7 REPL at 115200 baud. `quecpython_exec_string()` must not be called from an arbitrary UniRTOS task until its request has been marshalled to the QuecPython runtime task.

```text
unirtos-cli ls-demos
unirtos-cli new -r unirtos-quecpython-demos -v 1.0.0
cd unirtos-quecpython-demos-1.0.0
unirtos-cli env-setup
unirtos-cli clean
unirtos-cli build
```

Expected output: `qos_build/release/<project-name>/at_command.hbinpkg`.

Hardware acceptance additionally covers `_boot.py`, LittleFS mount/script execution, legacy module imports, and the enabled GPIO/UART/I2C/SPI/Timer/RTC/WDT capabilities.
