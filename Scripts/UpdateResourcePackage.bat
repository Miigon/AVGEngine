@echo off
cd ../
if not exist "ResBuilder/ResBuilder.jar" goto buildResBuilder
:updateRes
java -jar ResBuilder/ResBuilder.jar Resources res.pk
goto end
:buildResBuilder
cd ResBuilder
start /wait Build.bat
cd ../
goto updateRes
:end
cd Scripts
exit
