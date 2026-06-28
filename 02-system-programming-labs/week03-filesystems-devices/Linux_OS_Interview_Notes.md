# Linux OS Interview Notes

## 1. What is VFS?

### Short Answer

VFS (Virtual File System) is a Linux kernel abstraction layer that provides a common interface for different filesystem types.

Applications use the same system calls:

```c
open()
read()
write()
close()
stat()
```

regardless of whether the file resides on ext4, xfs, btrfs, tmpfs, procfs, sysfs, or NFS.

The application does not need to know the underlying filesystem implementation.

## 2. What is the Difference Between `/proc` and `/sys`?

### Short Answer

| `/proc` | `/sys` |
|----------|---------|
| Process and kernel runtime information | Device model and hardware hierarchy |
| Backed by procfs | Backed by sysfs |
| Process-centric | Device-centric |

### `/proc`

Examples:

- `/proc/cpuinfo`
- `/proc/meminfo`
- `/proc/mounts`
- `/proc/cmdline`
- `/proc/<pid>/status`
- `/proc/<pid>/fd`

### `/sys`

Examples:

- `/sys/class/net/`
- `/sys/block/`
- `/sys/bus/pci/`
- `/sys/devices/`
- `/sys/module/`

Sysfs exposes kernel objects such as devices, drivers, buses, classes, modules, and firmware.

## 3. What is a Device Node?

A device node is a special file under `/dev` that provides access to a kernel device driver.

Examples:

- `/dev/sda`
- `/dev/nvme0n1`
- `/dev/null`
- `/dev/tty`

### Character vs Block Devices

- Character devices: `/dev/null`, `/dev/random`, `/dev/tty`
- Block devices: `/dev/sda`, `/dev/nvme0n1`

Device nodes contain major and minor numbers used by the kernel to route operations to the correct driver.

## 4. What Does udev Do?

`udev` is the Linux userspace device manager.

Typical flow:

1. Hardware is detected by the kernel.
2. A driver binds to the device.
3. The kernel emits a uevent.
4. udev receives the event.
5. udev creates or removes device nodes in `/dev`.
6. udev may create stable symlinks such as:
   - `/dev/disk/by-uuid/`
   - `/dev/disk/by-id/`
   - `/dev/disk/by-label/`

udev relies heavily on information exported through sysfs (`/sys`).

## 5. What is a File Descriptor?

A file descriptor (FD) is a small integer used by a process to reference an open file-like object.

Standard descriptors:

- 0 = stdin
- 1 = stdout
- 2 = stderr

Example:

```c
int fd = open("/etc/passwd", O_RDONLY);
read(fd, buf, size);
close(fd);
```

File descriptors can refer to:

- Regular files
- Directories
- Sockets
- Pipes
- Terminals
- Device nodes
- eventfd
- timerfd
- epoll instances

## Big Picture

```text
Application
    |
open()
    |
File Descriptor
    |
VFS
    |
+----------------------+
|                      |
Regular Files      Device Nodes
(ext4/xfs)         (/dev/sda)
|                      |
Filesystem Driver  Device Driver
```

Device management path:

```text
Kernel detects hardware
        |
      /sys
        |
      udev
        |
      /dev
```
