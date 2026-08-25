# powkiddy-js

A tiny JavaScript interpreter for the PowKiddy V90 handheld, written in C and powered by [Duktape](https://duktape.org/).

It embeds Duktape and exposes simple native bindings (`print`, `sleep`) plus a file reader, so you can run `.js` scripts from `test.js` on the device.

## Build & run

```bash
make
./powkiddy-js
```
