# copyfsync
program by Peter Semiletov

https://github.com/psemiletov/copyfsync

The utility to copy file with synchronize
after each copying iteration.
Good for copy large file to USB stick when copying is slow
or stalled.
Some people are happy with ```/etc/sysctl.conf``` or
```/etc/sysctl.d/99-sysctl.conf``` file:

```
vm.dirty_bytes=50331648
vm.dirty_background_bytes=16777216
```

But it does not work in my case. So I wrote a simple copying program
that call fsync (actually, fflush and fdatasync) after each copying iteration.
copyfsync copies data by portions with the buffer size (2 MB by default) and sync buffer
after earch read/write iteration.

**Usage:**

```console
copyfsync filename destnation_dir
```

or:

```console
copyfsync buffer_size filename destnation_dir
```

**Examples...**

Copy movie.avi to /run/media/username/FLASHDRIVE/:


```console
copyfsync movie.avi /run/media/username/FLASHDRIVE/
```

Copy movie.avi to /run/media/username/FLASHDRIVE with 4 MB buffer (default 2 MB):

```console
copyfsync 4 movie.avi /run/media/username/FLASHDRIVE/
```

Buffer size can be set in kbytes using the "K" suffix. Set the 1000 kbytes buffer:

```console
copyfsync 1000K movie.avi /run/media/username/FLASHDRIVE/
```


**If you like this program you can donate via:**

Paypal: peter.semiletov@gmail.com

BTC: 1PCo2zznEGMFJey4qFKGQ8CoFK2nzNnJJf
