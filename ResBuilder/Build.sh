javac *.java    
if [ ! -d "ResBuilder" ]; then
mkdir ResBuilder
fi
cp *.class ResBuilder    
jar cef ResBuilder.ResBuilder ResBuilder.jar ResBuilder
