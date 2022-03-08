g++ trainertest.cpp ml.cpp -o builds/trainertest -std=gnu++11 -lquadmath -fext-numeric-literals
g++ exttest.cpp ml.cpp -o builds/exttest -std=gnu++11 -lquadmath -fext-numeric-literals
g++ laptoptest.cpp ml.cpp -o builds/laptoptest -std=gnu++11 -lquadmath -fext-numeric-literals
g++ runner.cpp ml.cpp -o builds/runner -std=gnu++11 -lquadmath -fext-numeric-literals -pthread -fPIE
g++ outter.cpp ml.cpp -o builds/outter -std=gnu++11 -lquadmath -fext-numeric-literals -pthread -fPIE

