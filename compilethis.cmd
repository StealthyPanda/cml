REM g++ f128ting.cpp -o f128ting -std=gnu++11 -lquadmath -fext-numeric-literals
REM g++ tester.cpp ml.cpp -o builds\tester -std=gnu++11 -lquadmath -fext-numeric-literals
g++ runner.cpp ml.cpp -o builds/runner -std=gnu++11 -lquadmath -fext-numeric-literals
REM g++ trainertest.cpp ml.cpp -o builds/trainertest -std=gnu++11 -lquadmath -fext-numeric-literals
