./UpdateResourcePackage.sh
mkdir AndroidProject/assets/
cp res.pk AndroidProject/assets/res.pk
cd AndroidProject
./../AndroidNDK/ndk-build
if [ $? -ne 0 ];then
	exit 1
fi
ant release
if [ $? -ne 0 ];then
	exit 1
fi
cd ../