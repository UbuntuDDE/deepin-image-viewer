### Deepin Image Viewer

Deepin Image Viewer is an image viewing tool with fashion interface and smooth performance  developed by Deepin Technology.

### Dependencies

### Build dependencies

* [deepin-tool-kit](https://github.com/linuxdeepin/deepin-tool-kit) (developer package)

### Runtime dependencies

* [deepin-tool-kit](https://github.com/linuxdeepin/deepin-tool-kit)
* [deepin-shortcut-viewer](https://github.com/linuxdeepin/deepin-shortcut-viewer)
* [deepin-manual](https://github.com/linuxdeepin/deepin-manual)
* libexif
* freeimage
* libraw
* Qt5 (>= 5.6)
  * Qt5-DBus
  * Qt5-Svg
  * Qt5-X11extras

## Installation

### Build from source code

1. Make sure you have installed all dependencies.

2. Build:
```
$ cd deepin-viewer
$ mkdir Build
$ cd Build
$ qmake ..
$ make
```

3. Install:
```
$ sudo make install
```
## Usage

Execute `deepin-image-viewer`

## Documentations

 - [Development Documentation](https://linuxdeepin.github.io/deepin-image-viewer/)
 - [User Documentation](https://wiki.deepin.org/wiki/Deepin_Image_Viewer) | [用户文档](https://wikidev.uniontech.com/index.php?title=%E7%9C%8B%E5%9B%BE)
When install complete, the executable binary file is placed into `/usr/bin/deepin-viewer`.

## Getting help

Any usage issues can ask for help via
* [Gitter](https://gitter.im/orgs/linuxdeepin/rooms)
* [IRC Channel](https://webchat.freenode.net/?channels=deepin)
* [Official Forum](https://bbs.deepin.org/)
* [Wiki](https://wiki.deepin.org/)

## Getting involved

We encourage you to report issues and contribute changes

* [Contribution guide for developers](https://github.com/linuxdeepin/developer-center/wiki/Contribution-Guidelines-for-Developers-en). (English)
* [开发者代码贡献指南](https://github.com/linuxdeepin/developer-center/wiki/Contribution-Guidelines-for-Developers) (中文)

## License

Deepin Image Viewer is licensed under [GPLv3](LICENSE).
