cd ../
# 配置安卓下SDL开发环境
if [ ! -d "AndroidProject" ]; then
	if [ ! -f "SDL2-2.0.7.tar.gz" ]; then
	  sudo wget http://www.libsdl.org/release/SDL2-2.0.7.tar.gz 2>/dev/null
	fi
	
	echo "unzip sdl2"
	tar -xzvf SDL2-2.0.7.tar.gz > /dev/null 2>&1
	mv SDL2-2.0.7/android-project AndroidProject
	mv SDL2-2.0.7 AndroidProject/jni/SDL2
	
	if [ ! -f "SDL2_image-2.0.2.tar.gz" ]; then
	  sudo wget http://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.2.tar.gz 2>/dev/null
	fi
	
	echo "unzip sdl2_image"
	tar -xzvf SDL2_image-2.0.2.tar.gz > /dev/null 2>&1
	mv SDL2_image-2.0.2 AndroidProject/jni/SDL2_image
	
	if [ ! -f "SDL2_ttf-2.0.14.tar.gz" ]; then
	  sudo wget http://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.tar.gz 2>/dev/null
	fi
	
	echo "unzip sdl2_ttf"
	tar -xzvf SDL2_ttf-2.0.14.tar.gz > /dev/null 2>&1
	mv SDL2_ttf-2.0.14 AndroidProject/jni/SDL2_ttf
fi

# 下载NDK
if [ ! -f "android-ndk-r16b-linux-x86_64.zip" ]; then
	sudo wget https://dl.google.com/android/repository/android-ndk-r16b-linux-x86_64.zip 2>/dev/null
fi

sudo apt-get install unzip

if [ ! -d "AndroidNDK" ]; then
	unzip android-ndk-r16b-linux-x86_64.zip > /dev/null 2>&1
	mv android-ndk-r16b AndroidNDK
fi

# ant
sudo apt-get install ant

#打补丁
for file in AndroidPatch/*
do
    if test -f $file
    then
		echo Patch $file
        patch -p0 < $file
    fi
done

#复制源码
echo "Copy codes from AVGEngine/src to AndroidProject/jni/src"
cp -r AVGEngine/src AndroidProject/jni/src
cd Scripts