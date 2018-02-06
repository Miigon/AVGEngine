## AVGEngine [![AppVeyor tests](https://img.shields.io/appveyor/tests/GScience/AVGEngine.svg)](https://ci.appveyor.com/project/GScience/avgengine/build/tests)
### 0. 支持的平台
项目开发环境和测试环境君为Window，能保证Window下正常运行，其他平台只能保证可以正常编译。

[![AppVeyor](https://img.shields.io/appveyor/ci/gscience/avgengine.svg?label=Windows)](https://ci.appveyor.com/project/GScience/avgengine)

[![Travis](https://img.shields.io/travis/GScience/AVGEngine.svg?label=Android)](https://www.travis-ci.org/GScience/AVGEngine)
### 1. 安装
#### a. Windows
首先你需要安装好vcpkg，并且安装了Visual Studio 2017，之后我们需要执行以下命令：
>vcpkg install glew sdl2 sdl2-image

如果没有出现就可以正常编译了。
#### b. Android
Android下的开发有些复杂，我只为Linux环境写了一个编译脚本：InitAndroid.sh。运行此脚本，项目中会多出三个.tar.gz文件，一个.zip文件以及两个文件夹：AndroidProject和AndroidNDK。之后运行BuildAndroid.sh即可开始编译。这里需要注意，需要自行安装Android SDK等与安卓开发有关的东西，不然无法正常编译。（安卓开发就是麻烦）
#### c. IOS
IOS下的开发环境暂未架设完成，当前进度：0%。
### 2. 开源协议
本项目遵循GPL许可证！！！！
### 3. 使用的开源库
SDL2 SDL2_image SDL2_ttf以及以上三者所依赖的其他开源Lib