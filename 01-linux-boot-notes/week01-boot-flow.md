# Week 1 — Linux Boot Flow and Platform Startup

## Lab

### cmdline

```sh
cat /proc/cmdline
> BOOT_IMAGE=/boot/vmlinuz-6.17.0-20-generic root=UUID=1e8991aa-f189-4501-afc5-d6bf529d1d3c ro quiet splash vt.handoff=7

# BOOT_IMAGE=/boot/vmlinuz-6.17.0-20-generic
file /boot/vmlinuz-6.17.0-20-generic 
> /boot/vmlinuz-6.17.0-20-generic: Linux kernel x86 boot executable bzImage, version 6.17.0-20-generic (buildd@lcy02-amd64-120) #20~24.04.1-Ubuntu SMP PREEMPT_DYNAMIC Thu Mar 19 01:28:37 UTC 2, RO-rootFS, swap_dev 0XF, Normal VGA

# root=UUID=1e8991aa-f189-4501-afc5-d6bf529d1d3c
lsblk -f /dev/sda5
> NAME FSTYPE FSVER LABEL UUID                                 FSAVAIL FSUSE% MOUNTPOINTS
  sda5 ext4   1.0         1e8991aa-f189-4501-afc5-d6bf529d1d3c  128.3G    13% /
```

- `ro`: [Why ro is used here](linux_kernel_cmdline_ro_explanation.md)

### dmesg -T

[dmesg.log](dmesg.log)

### journalctl -b

[journalctl.log](journalctl.log)

### system-analyze

```sh
systemd-analyze
> Startup finished in 20.459s (firmware) + 11.292s (loader) + 1.872s (kernel) + 23.659s (userspace) = 57.284s

systemd-analyze critical-chain
> The time when unit became active or started is printed after the "@" character.
  The time the unit took to start is printed after the "+" character.
  
  graphical.target @23.600s
  └─multi-user.target @23.600s
    └─plymouth-quit-wait.service @17.033s +6.563s
      └─systemd-user-sessions.service @16.903s +101ms
        └─network.target @16.853s
          └─NetworkManager.service @14.795s +2.055s
            └─dbus.service @14.064s +386ms
              └─basic.target @14.050s
                └─sockets.target @14.050s
                  └─snapd.socket @13.849s +196ms
                    └─sysinit.target @13.843s
                      └─systemd-backlight@backlight:intel_backlight.service @15.026s +1.308s
                        └─system-systemd\x2dbacklight.slice @13.219s
                          └─system.slice @423ms
                            └─-.slice @423ms
```

[systemd-analyze-blame.log](systemd-analyze-blame.log)

[systemd-analyze-plot.svg](systemd-analyze-plot.svg)

## Questions

- What is initramfs and why is it needed?
  - initramfs is needed because kernel may need extra drivers to load the real rootfs, like encryption, LVM, RAID drivers.

- What is PID 1?

```sh
ps -ef | head
> UID          PID    PPID  C STIME TTY          TIME CMD
  root           1       0  0 16:08 ?        00:00:11 /sbin/init splash

ll /sbin/init
> lrwxrwxrwx 1 root root 22 Mar 14 00:48 /sbin/init -> ../lib/systemd/systemd*
```

- How would you debug a slow boot?
