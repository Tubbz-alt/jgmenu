jgmenu
======

Introduction
------------

Jgmenu is a simple X11 menu application.

It is written with the following (original) aims:

  - Be a stand-alone, simple and contemporary-looking menu  
  - Be hackable with a clean, small code base  
  - Minimise features and bloat  
  - Work with linux, openbox and tint2  
  - Have co-ordinate and alignment parameters to avoid xdotool hacks, etc.  
  - Contain similar settings to tint2 (e.g. padding, transparency)  
  - Have few dependencies (perferably just Xlib, cairo and Xinerama)  
  - Be free from toolkits such as GTK and Qt.  
  - Read the menu items from stdin in a similar way to dmenu and dzen2, but  
    with seperate fields for the name and command  

These original "aims" still hold true today, with the exception of a few added  
dependencies:  

  - pango (for font rendering)  
  - librsvg (for SVG icons)  

Some of the `jgmenu_run` commands have further dependencies such as libxml2.  
The build process currently requires these, but it would be easy to #ifdef  
them out if anyone wants that.

It's also worth noting that it has been compiled and runs fine on various  
Linux distributions as well as OpenBSD.

Jgmenu is written with an uppercase "J" when referring to the entire  
application, and lowercase (jgmenu) when referring to the binary file.

Screenshots
-----------

[![foo](http://i.imgur.com/4oprqYZt.png)](http://i.imgur.com/4oprqYZ.png)
[![foo](http://i.imgur.com/QvBqI2Lt.png)](http://i.imgur.com/QvBqI2L.png)  

From the left:  

1. jgmenu and tint2 using Numix-Circle icon theme
2. jgmenu and tint2 using Papirus icon theme

Dependencies
------------

### Build dependencies

  - libx11
  - libxinerama
  - cairo
  - pango
  - librsvg
  - libxml2

For Arch Linux users, there is an AUR package named "jgmenu" which installs  
the correct build dependencies.

On Debian based systems such as Bunsenlabs and Ubuntu, do:

```bash
sudo apt-get install libx11-dev libxinerama-dev libcairo2-dev \
libpango1.0-dev librsvg2-dev libxml2-dev
```

### Run-time dependencies:

  - A *menu* package (for example gnome-menus or lxmenu-data)  
    Required for "`jgmenu_run pmenu`" and "`jgmenu_run xdg`"  

  - python3  
    Required by "`jgmenu_run pmenu`"

To enable menu transparency, you need to have a Composite Manager such as  
`compton`. Most Desktop Environments already have one installed.

### Development dependencies

To build the man pages, you need to have `pandoc` installed. However, as many  
users do not have this package, the man pages are commited in the git repo.  
(i.e. you only need pandoc if you want to contribute to or change the man  
pages.)

Build and Install
-----------------

Although it is possible to run `jgmenu_run` from the source directory (by  
setting `JGMENU_EXEC_PATH`), it is recommended to install it as follows:  

```bash
make
make install
```

By default, `make install` will install Jgmenu in your $HOME-directory, thus  
avoiding the need for root-privilegies. You will need `$HOME/bin` in your  
`$PATH` to run from there.

The build process installs files under:  

  - bin/
  - lib/jgmenu/
  - share/man/

Use `prefix` to specify a different target location. For example,  
if you wish to keep your $HOME top-level directory clean, you could do:  

```bash
make prefix=$HOME/.local install
```

Or, to do a system-wide installation use '/usr' or '/usr/local'.  
For example: 

```bash
sudo make prefix=/usr install
```

In addition to `prefix`, there are a number of build variables which can be  
defined. These are described in the Makefile. Create a config.mk to override  
build settings without making your tree dirty or having to re-type them every  
time. 

There is no "uninstall" target in the Makefile. To tidy up, delete the  
following:

  - $prefix/bin/jgmenu*  
  - $prefix/lib/jgmenu/  
  - $prefix/share/man/man1/jgmenu*  
  - $prefix/share/man/man7/jgmenu*  


Getting started (after installation)
------------------------------------

Create a configuration file using the following command:

```bash
jgmenu_run init
```

Edit the configuration file (`~/.config/jgmenu/jgmenurc`) to suit your setup.  
Typically you will need to review the following as a minimum:  

  - icon theme
  - alignment
  - margins

Read [JGMENU-CONFIG (1)](docs/manual/jgmenu-config.1.md) and the example
[jgmenurc](docs/jgmenurc) for further  
information.  

Create icon-cache:

```bash
jgmenu_run cache
```

There are many ways to run Jgmenu. To get started, try:

```bash
jgmenu_run pmenu
```

For further details, see the man pages:

  - [JGMENUTUTORIAL (7)](docs/manual/jgmenututorial.7.md)
  - [JGMENU_RUN (1)](docs/manual/jgmenu_run.1.md)
  - [JGMENU (1)](docs/manual/jgmenu.1.md)

Desktop File and Panel Integration
----------------------------------

`make install` creates a desktop-file in `~/.local/share/applications` or  
`$prefix/share/applications` if $prefix is specified.

This file can be used in panels such as tint2, plank and unity.

To add this .desktop-file to tint2, add the line below to the launcher  
section in `~/.config/tint2/tint2rc`:

```bash
launcher_item_app = jgmenu.desktop
```

N.B. On some older versions of tint2, the full path to the desktop file  
is required.

If you are using plank, just drag the icon onto the panel. Note that in  
plank, `JGMENU_DESKTOP_ICON` needs to contain the full path to the icon.

The build-script for the .desktop-file reads config.mk and respects the  
following options:

  - `JGMENU_DESKTOP_EXEC`   
  - `JGMENU_DESKTOP_ICON`  
  - `JGMENU_UNITY`  

For example:

```bash
JGMENU_DESKTOP_EXEC="jgmenu_run csv \"--add-pmenu\""
JGMENU_DESKTOP_ICON="distributor-logo-archlinux"
```

If you are using Ubuntu's Unity, prepend the `Exec` command with  
`env JGMENU_UNITY=1`. This prevents the Unity Launcher from flashing  
for 5+ seconds after the menu has been opened. For example:

```bash
JGMENU_DESKTOP_EXEC="env JGMENU_UNITY=1 jgmenu_run csv"
```

See also
--------

### Other files in repo

  - [Road Map](TODO)

### Other man pages

  - `jgmenu_run` [pmenu](docs/manual/jgmenu-pmenu.1.md)
  - `jgmenu_run` [xdg](docs/manual/jgmenu-xdg.1.md)
  - `jgmenu_run` [csv](docs/manual/jgmenu-csv.1.md)
  - `jgmenu_run` [cache](docs/manual/jgmenu-cache.1.md)


