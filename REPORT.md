# Project Report: get\_next\_line

## 1. Objective

The goal of this project was to implement a function called `get_next_line` that reads from a file descriptor and returns the next line each time it's called. A line is defined as a sequence of characters ending with a newline (`\n`) or the end-of-file (EOF). The function should manage memory and buffering efficiently and return `NULL` when there are no more lines to read.

I can only have three files, `get\_next\_line.c`, `get\_next\_line\_utils.c` and `get\_next\_line.h`. get\_next\_line.c can only have the `char *get_next_line(int fd)` function while utils can have at maximum 5 functions. Every function should have at most 25 lines. Also I wanted to only use one *static* variable in all my code.

This implementation also includes the **bonus part**, which allows handling **multiple file descriptors simultaneously** without mixing up their state. The files are the same with \_bonus appended.

## 2. Implementation Summary

- **Language:** C
- **Key features:**
  - Dynamically reads lines of any length using a buffer.
  - Stores leftover data between calls using *static* variables. In my case a buffer that its size can be set during compiling with the flag -D BUFFER\_SIZE = X.
  - Manages multiple file descriptors in the bonus version using the buffer as a matrix instead of an array.
- **Interesting design decisions:**
  - At first I was just zeroing buffer positions I had already read and then iterating thru `\0`'s until I found a non-zero character, but shifting non-zero positions of the buffer to its start (`ft_process_buffer(char *buff, int i)`) was so much better to work with and less error prone.

## 3. Challenges Faced

- **Buffering logic:**  
  Managing partial reads and leftover data without leaking memory or losing content was tricky.
  - **First verion:** I had a working version that had the result string as the *static* variable. I would copy everything from the buffer and then return everything until \n or EOF. Thing is, if the user opened a file, read only one line and there were more lines in the file and then closed the file, I would have memory leaks since the *static char* \*result would never be freed.
  - **Final version:** I realized that since I could only use one *static* variable in my function it HAD to be the buffer that I was using to store my *read* calls.

- **Multiple file descriptors (bonus):**  
  Initially, I thought it would be as simple as having buffer as a matrix and using the value of the file descriptor as the row. But since I like to be a cool kid and use pointer notation it would be tricky to access the right row.
  - **Fix:** Well, lets say I had to look even cooler by keeping pointer notation and not forget to add fd * BUFFER\_SIZE as you can see here:

```c
while (r <= i)
{
    *(result + k) = *(buff + fd * BUFFER_SIZE + r);
    *(buff + fd * BUFFER_SIZE + r) = '\0';
    r++;
    k++;
}
```

- **Memory leaks and edge cases:**  
  - Off-by-one errors, especially with `\n` and EOF, were a pain.
  - **Solution:** Valgrind + brute force testing with weird files helped iron these out.

## 4. What I Learned

  - Static variables and their uses: It was the first time that I needed that a variable would store its state between function calls.
  - A deeper understanding of memory usage: I thought I knew the difference between heap and stack but it confused me why I would have a memory leak with a *static* malloc'd string but not with a *static* not-malloc'd array. The difference is that the malloc'd memory lives on the heap and must be freed manually, while the static array lives in the **data segment** of the program's memory — not on the stack or the heap — and its lifetime is managed automatically by the system.

## 5. What I’d Do Differently

- Would probably test each function independently. I have this bad habit that is that I write down a rough estimate of how I'm going to implement the solution I came up with and then I just write all the functions in one go, I try to compile everything and then GDB my way into a working program. It worked okay-ish for this really small project but I will feel the pain when the projects start to get bigger.
- Create a structure. It might be overkill but now that everything is done I think it would be more manageble.
- I will die for pointer notation but whenever I know I'll have to use a matrix I think that array notation is actually better. Like, who can remember that you should multiply the size of the rows by the column number you're trying to access? Wait, or is it the other way around ???

## 6. Future Improvements

- Refactor everything. Cleaner code and for the bonus ditch pointer notation and just stick to stinky but more readable and less error prone array notation.

## 7. Resources & References

- [man 2 read](https://man7.org/linux/man-pages/man2/read.2.html)
- [Stack Overflow - Handling leftover buffers](https://stackoverflow.com/)
- My own tears and gdb
- My friends and colleagues at 42school Lisboa.

