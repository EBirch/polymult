SIZES="32 64 128 256 512 1024 2048 4096 8192 16384"
for i in $SIZES; do
	echo Size $i
	echo -n $i ''>> data
	./polymult -d `echo $i` | grep "Mean time" | echo -n `awk '{print $3}'` ''>> data
	./polymult -4 `echo $i` | grep "Mean time" | echo -n `awk '{print $3}'` ''>> data
	./polymult -3 `echo $i` | grep "Mean time" | echo `awk '{print $3}'` ''>> data
done
