# Simple Kernel Module

- `module_init`: Called when `insmod`
- `module_exit`: Called when `rmmod`

## insmod vs modprobe

Although insmod works, Linux users more commonly use modprobe.

| `insmod`                             | `modprobe`                                                                    |
| ------------------------------------ | ----------------------------------------------------------------------------- |
| Loads a specific `.ko` file.         | Loads a module by name.                                                       |
| Does **not** resolve dependencies.   | Automatically loads dependent modules.                                        |
| Requires the path to the `.ko` file. | Searches the module directories (typically `/lib/modules/<kernel-version>/`). |
| Often used during development.       | Commonly used on installed systems.                                           |

## Module Param

Kernel Address Space

```graph
+---------------------------------------------------+
| Linux Kernel                                      |
|                                                   |
|  Core kernel                                      |
|                                                   |
|  Loaded module: hello_platform                    |
|  +-------------------------------+                |
|  | code (.text)                  |                |
|  | data (.data/.bss)             |                |
|  |                               |                |
|  | static char *name ----------+ |                |
|  +-----------------------------|-+                |
|                                |                  |
|                                v                  |
|                        "Alice" (kernel memory)    |
+---------------------------------------------------+
```

/sys/module/hello_platform/parameters/name

## printk

<https://docs.kernel.org/core-api/printk-basics.html>
