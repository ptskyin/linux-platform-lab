# Linux Kernel Command Line: `ro`

`ro` means the kernel initially mounts the root filesystem `/` as **read-only**.

This is usually **temporary**. During early boot, the kernel needs to mount `/` so it can start userspace, for example `systemd`. But before the system fully trusts the filesystem, it is safer to mount it read-only first.

## Typical boot flow

```text
GRUB passes: root=UUID=... ro
        ↓
Kernel mounts / as read-only
        ↓
initramfs / systemd starts
        ↓
Filesystem checks or recovery steps may happen
        ↓
System remounts / as read-write
        ↓
Normal boot continues
```

## Why use `ro`?

### 1. Safety during filesystem checks

Tools like `fsck` should not normally repair a filesystem while it is mounted read-write. Mounting `/` as read-only first makes it safer to check or repair.

### 2. Avoid writing too early

Early boot is a fragile stage. The kernel may not have fully initialized everything yet. Read-only mounting avoids accidental writes before the system is ready.

### 3. Compatibility with traditional Unix/Linux boot flow

Historically, root was mounted read-only, checked, then remounted read-write. Modern systems still commonly keep this pattern.

## How to check the remount in boot logs

You may see the system remount `/` as read-write in the boot logs:

```bash
journalctl -b | grep -i remount
```

## How to check the current mount state

On a normally running system, `/` is usually already read-write. You can check with:

```bash
findmnt /
```

Example output:

```text
TARGET SOURCE         FSTYPE OPTIONS
/      /dev/nvme0n1p2 ext4   rw,relatime,errors=remount-ro
```

Here `rw` means the root filesystem is currently mounted read-write.

## Summary

In your kernel command line, `ro` does **not** mean your Linux system always runs read-only.

It means:

> Mount the root filesystem read-only first during early boot, then remount it read-write later when the system is ready.
