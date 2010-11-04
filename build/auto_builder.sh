for neurons in {1..101..5}; do
   for inner_points in {20..421..50}; do
       for border_points in {10..161..30}; do
           for delta in 1 100 1000; do
               for iter in {1..3}; do
                   cat ../cpp_solutions/neuro/mq/main.cpp | sed -e "s/const int NEURONS = 50;/const int NEURONS = $neurons;/" -e "s/const int POINTS_INNER = 200;/const int POINTS_INNER = $inner_points;/" -e "s/const int POINTS_BORDER = 50;/const int POINTS_BORDER = $border_points;/" -e "s/const double DELTA = 1;/const double DELTA = $delta;/" > ../cpp_solutions/neuro/mq/main_current.cpp;
                   g++ -O3 ../cpp_solutions/neuro/mq/main_current.cpp -o mq;
                   ./mq >> ../reports/result.txt;
               done;
           done;
       done;
   done;
done;

