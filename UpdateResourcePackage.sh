if [ ! -f "ResBuilder/ResBuilder.jar" ]; then
	cd ResBuilder
	./Build.sh    
	cd ../
fi
java -jar ResBuilder/ResBuilder.jar Resources res.pk
