# MatrixCalculator
Making a calculator to help me with my linear algebra class

Currently very functional!!!
To-do:
1. Clean up main function
2. Make user interaction more friendly
3. Implement operations involving eigenvectors
4. Setup try catch blocks and exception handling to catch overflow errors
5. Work on a potential GUI?!?!

Currently known bug: (Happens most often when finding the inverse)
 - When fraction multiplication gets large, numerators/denominators can overflow very quickly, causing the function to return incorrect results. Ideally, I'd like to reduce this from happening, but I think I've done the most I can. More importantly, I need to establish exception handling for this.

--- THOUGHTS ---
First, this wouldn't be too bad to fix (Is now fixed :P), but when researching eigenvectors, I recognized that there would be no way I could avoid using radicals in the matrix. If I had made the matrix, and probably even the fraction class templated, I may have been able to actually make these adjustments quickly. This makes me recognize how important it is for data structures to be built with general usage in mind, and not with an exact value. I even changed from using floats in the matrix to using the custom made Fraction class half way through. This change would have been seamless had I originally built it using a templated class.

Although I didn't completely neglect documentation, it was certainly lack luster. Most importantly, I didn't have anything documented on the functions themselves, just how they work internally. This amusingly made it so that at one point when I took a break from updating it, when I came back after a bit, I struggled more in updating it. I personally think I do better than most students in commenting, but I definitely still need to step up my game.

One thing I couldn't figure out, but would still like to learn, is how code in C++ developed on Linux can be used in an executable file on Windows. On this note though, I'm looking into potentially turning the matrix and fraction object into a library that I can then code in python to create a GUI for