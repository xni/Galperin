for neurons in {1..50}; do
    for equation_no in {1..4}; do
	for iter in {1..100}; do
            echo "Equation ${equation_no}. ${neurons} neurons. Try # ${iter}"
            cat ../cpp_solutions/neuro/mq/main.cpp | sed -e "s/const int NEURONS = 50;/const int NEURONS = $neurons;/" -e "s/..\/..\/equation.h/..\/..\/equation${equation_no}.h/" -e "s/Problem N/Problem $equation_no/" > ../cpp_solutions/neuro/mq/main_current.cpp;
            g++ -O3 ../cpp_solutions/neuro/mq/main_current.cpp -o mq;
            ./mq >> ../reports/result_by_neurons.txt;
	done;
    done;
done;

