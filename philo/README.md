# Makefile Utility
- `make` and `make philo` will compile the Philosophers Project, as the executable `philo`.
- `make clean` and `make fclean` will delete the executable `philo` or return an error message if `philo` does not exist.
- `make re` will run the commands, `make clean` then `make`, to delete (if possible) and then compile the executable `philo`.
# Known Bugs / Errors
If the computer / machine doesn't have a enough free CPU, then this code will not run correctly, as it will take longer to execute which leads philosophers to die when they theorectically would not.  
So if the code has incorrect output, it is most likely not a problem with the code.
# Code Execution Format
`./philo [total number of Philosophers] [time for Philosopher to die without eating] [time for Philosopher to eat once] [time taken for Philosopher to sleep] **[amount of meals Philosopher can eat to end their simulation]**`  
- All times are in milliseconds (ms).  
- `**`: The 5th parameter is optional, so the code will run with or without it.
# Test Cases / Examples of How to Run Code
- `./philo 1 200 200 200` should end with philosopher 1 dead.
- `./philo 4 60 300 300` should end with a philosopher dead.
- `./philo 6 200 50 50` should run indefinitely. Stop the executable from running using ctrl+c (kill command) or any equivalent after 5-10 real-life seconds.
- `./philo 8 1000 50 50 6` should end with all philosophers alive after each one has finished eating 6 meals.
 ### A helpful [Tester](https://github.com/newlinuxbot/Philosphers-42Project-Tester) I used for this Project.
