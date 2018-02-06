# 配置安卓下SDL开发环境
if [ ! -d "AndroidProject" ]; then
	if [ ! -f "SDL2-2.0.7.tar.gz" ]; then
	  wget http://www.libsdl.org/release/SDL2-2.0.7.tar.gz
	fi
	
	echo "unzip sdl2"
	tar -xzvf SDL2-2.0.7.tar.gz > /dev/null 2>&1
	mv SDL2-2.0.7/android-project AndroidProject
	mv SDL2-2.0.7 AndroidProject/jni/SDL2
	
	if [ ! -f "SDL2_image-2.0.2.tar.gz" ]; then
	  wget http://www.libsdl.org/projects/SDL_image/release/SDL2_image-2.0.2.tar.gz
	fi
	
	echo "unzip sdl2_image"
	tar -xzvf SDL2_image-2.0.2.tar.gz > /dev/null 2>&1
	mv SDL2_image-2.0.2 AndroidProject/jni/SDL2_image
	
	if [ ! -f "SDL2_ttf-2.0.14.tar.gz" ]; then
	  wget http://www.libsdl.org/projects/SDL_ttf/release/SDL2_ttf-2.0.14.tar.gz
	fi
	
	echo "unzip sdl2_ttf"
	tar -xzvf SDL2_ttf-2.0.14.tar.gz > /dev/null 2>&1
	mv SDL2_ttf-2.0.14 AndroidProject/jni/SDL2_ttf
fi

# 下载NDK
if [ ! -f "android-ndk-r14b-linux-x86_64.zip" ]; then
	wget https://dl.google.com/android/repository/android-ndk-r14b-linux-x86_64.zip
fi

sudo apt-get install unzip

if [ ! -d "AndroidNDK" ]; then
	unzip android-ndk-r14b-linux-x86_64.zip > /dev/null 2>&1
	mv android-ndk-r14b AndroidNDK
fi

# ant
sudo apt-get install ant

ant deps

#打补丁
for file in AndroidPatch/*
do
    if test -f $file
    then
		echo Patch $file
        patch -p0 < $file
    fi
done
