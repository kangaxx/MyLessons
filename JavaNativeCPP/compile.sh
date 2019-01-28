g++ -fPIC -shared -o libnative.so native.cpp -I/usr/java/jdk1.8.0_181/include -I /usr/java/jdk1.8.0_181/include/linux
echo "remember rm /usr/local/lib/libnative.so and rm /usr/lib/libnative.so, there is an old so file there!"
cp libnative.so /usr/lib/
javac TestMain.java
