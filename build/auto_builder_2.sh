for iter in {1..100}; do
   for equation_no in {5..10}; do
       for neurons in {1..30}; do
            echo "Equation ${equation_no}. ${neurons} neurons. Try # ${iter}"
            cat ../cpp_solutions/neuro/mq/main.cpp | sed -e "s/const int NEURONS = 50;/const int NEURONS = $neurons;/" -e "s/..\/..\/equation.h/..\/..\/equation${equation_no}.h/" -e "s/Problem N/Problem $equation_no/" > ../cpp_solutions/neuro/mq/main_current_2.cpp;
            g++ -O3 ../cpp_solutions/neuro/mq/main_current_2.cpp -o mq_2;
            ./mq_2 >> ../reports/result_by_neurons_2.txt;
	done;
    done;
done;

