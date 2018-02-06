cd AndroidProject
sudo ./../AndroidNDK/ndk-build
if [ $? -ne 0 ];then
	exit 1
fi
ant release
if [ $? -ne 0 ];then
	exit 1
fi
cd ../