# Simple HTTP web server

An HTTP web server for Linux implemented in C

Using pre-fork model and pselect() syscall

Web server supports following files: HTML, CSS, JS, ICO, PNG, JPG, JPEG, GIF, SWF and MP4

## Configure

Change number of child processes by changing WORKERS macro in server.h

Change port by changing PORT macro in server.h

# Test

Run unit tests by executing

```bash
$ make unit
```

and functional tests by executing

```bash
$ make func
```

# Build and run

Build server using makefile and run ./server.out
