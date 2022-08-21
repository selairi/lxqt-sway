# lxqt-sway

This project tries to port LXQt desktop to Sway (Wayland).

A tool to read LXQt settings has be written.

It needs [yatbfw](https://github.com/selairi/yatbfw) toolbar.

## Install

You need install LXQt and [yatbfw](https://github.com/selairi/yatbfw) toolbar. Then run:

```
mkdir build
cd build
cmake ..
make
sudo make install
```

Restart your Display Manager and a new Desktop will be available.
