echo "g++ -fPIC -shared -o libtestData.so *"
echo "create program with main function : g++ *.cc -o run -lprotoc"
g++ -fPIC -shared -o libprotoUnzip.so *.cc -I/usr/java/jdk1.8.0_181/include -I /usr/java/jdk1.8.0_181/include/linux -lprotoc
cp libprotoUnzip.so /usr/lib/
