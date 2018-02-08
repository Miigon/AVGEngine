cd ../
if [ ! -f "ResBuilder/ResBuilder.jar" ]; then
	cd ResBuilder
	sudo bash Build.sh    
	cd ../
fi
java -jar ResBuilder/ResBuilder.jar Resources res.pk
cd Scripts