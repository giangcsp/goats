# Assignment 4
## Giang Doan - gdd33@drexel.edu / 14279443

1. How to run the program:
   - make: make the binary file located at bin/goats
   - make clean: clean all the object files and the binary file
   - make run: run bin/goats with 12 goats on the west and 21 goats on the east
   - usage: ./bin/goats \<number of goats on the west> \<number of goats on east>

2. What locks, semaphores and/or conditional variables did you use and why?
   - I used the bridge semaphore for signaling the goats from both side to either cross the bridge or wait
   - The bridge semaphore works like a reverse lecture 4's semaphore since it only allows goats to cross when the counter reaches 0

3. How did you allow multiple goats on the rope at once?
   - The currentSide function is my sign to signal the goats to stop entering the bridge.
   - First goat that reaches the other side checks if there's any goat waiting in the other side and flip the currentSide sign to stop goats from its original side to stop entering the bridge.
   - While the first goat has not reached the other side, other goats can still join the bridge and even jump ahead and become the first goat to reach the other side.

4. How did you keep the rope fair?
   - The first goat that reaches the other side would check if there's any goat waiting (on the other side) and flip the sign so that goats from its original side'd stop entering the bridge, thus allows goats on the other side to enter the bridge.

5. Why are you <bold>certain</bold> the problem can never let any thread starve?
   - While waiting in the queue, conditional_variable::wait() would sleep the thread so that it does not consume any resource.
   - Also I did not use any lock that locks the mutex for too long. Actually I only used a thread for IO and for the bridge to perform very few operations then releases the lock imediately.

6. What was the most challenging part of this assignment?
   - Coming up with a clever, and easy solution for the bridge that is both fair and simple.