if [ -f "test.txt" ]; then
	echo "123" > test.txt
else
	touch test.txt
	echo "123" > test.txt
fi
