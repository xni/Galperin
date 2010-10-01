echo "Введите число нейронов"
read n

for i in `ls`; do
	if [ -d $i ]; then
		grep -H "$n neurons" "$i/Report.txt"
	fi
done
