# lxqt-sway

This project tries to port LXQt desktop to Sway (Wayland).

It needs [yatbfw](https://github.com/selairi/yatbfw) toolbar.

![](/images/layouts.gif)

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

Other tools could be installed for a better experience:
- [gammastep](https://gitlab.com/chinstrap/gammastep)
- wl-copy, grim and slurp for screenshots
- brightnessctl for control brightness
- Papirus-Dark icon theme

## lxqt-sway settings

Settings will be saved at "~/.config/lxqt/lxqt-sway" folder.

## lxqt-settings

A tool called lxqt-settings has be written. lxqt-settings is a command line tool that can read LXQt settings.

These settings usually are in ~/.config/lxqt or ~/.config/pcmanfm-qt.

Examples:

Get cursor size:
```lxqt-settings session --get Mouse/cursor_size```

Get cursor theme:
```lxqt-settings session --get Mouse/cursor_theme```

Get wallpaper:
```lxqt-settings pcmanfm-qt lxqt/settings --get Desktop/Wallpaper```
                                                                                     
Get list of pcmanfm-qt settings:                                                     
```lxqt-settings pcmanfm-qt lxqt/settings --list```
