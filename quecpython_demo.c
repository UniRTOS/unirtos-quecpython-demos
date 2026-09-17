/*
 * This translation unit intentionally has no application-init hook.
 *
 * unirtos-quecpython registers and owns the MicroPython runtime task.  A
 * UniRTOS task must not directly call quecpython_exec_string(), because that
 * would execute against the VM concurrently with the UART REPL task.
 */
void unirtos_quecpython_demo_link_anchor(void)
{
}
