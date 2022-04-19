@REM g++ trainertest.cpp ml.cpp -o builds/trainertest -std=gnu++11 -lquadmath -fext-numeric-literals
@REM g++ exttest.cpp ml.cpp -o builds/exttest -std=gnu++11 -lquadmath -fext-numeric-literals
@REM g++ laptoptest.cpp ml.cpp -o builds/laptoptest -std=gnu++11 -lquadmath -fext-numeric-literals
g++ runner.cpp ml.cpp -o builds/runner -std=gnu++11 -lquadmath -fext-numeric-literals -fPIE
