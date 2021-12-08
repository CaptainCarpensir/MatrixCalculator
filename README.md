# MatrixCalculator
Making a calculator to help me with my linear algebra class

Currently very functional!!!
To-do:
1. Implement fraction class - DONE
2. Implement all powerful Ax=b solver via solvematrix function - DONE
3. Implement operations involving eigenvectors
4. Make user interaction more friendly
5. Make fraction class more efficient, so that large numbers aren't created as quickly

Currently known bug: (Happens most often when finding the inverse)
 - When fraction multiplication gets large, numerators/denominators can overflow very quickly,  so when multiplication and division happen, I want to first simplify the fractions and then do the arithmetic

--- THOUGHTS ---
Alright, so at this point as my linear algebra class is ending, I think I'm done updating this project at least for now. I wanna write down some things that I learned along the way though.

First, this wouldn't be too bad to fix, but when researching eigenvectors, I recognized that there would be no way I could avoid using radicals in the matrix. If I had made the matrix, and probably even the fraction class templated, I may have been able to actually make these adjustments quickly. This makes me recognize how important it is for data structures to be built with general usage in mind, and not with an exact value. I even changed from using floats in the matrix to using the custom made Fraction class half way through. This change would have been seamless had I originally built it using a templated class.

Although I didn't completely neglect documentation, it was certainly lack luster. Most importantly, I didn't have anything documented on the functions themselves, just how they work. This amusingly made it so that at one point when I took a break from updating it, when I came back after a bit, I struggled more in updating it. I personally think I do better than most students in commenting, but I definitely still need to step up my game.

This is something I'm fairly proud of, I'd say I more learned this through my classes than through coding this project though. I'm really happy with how well optimized the class is. To my knowledge it handles pointers well, and uses algorithms as fast as I know. For example, the function to calculate the determinant works by changing the matrix to EF form and finding the determinant by mutiplying by the diagonal entries (and then multiplying by -1 if needed). There may be some other shortcuts, but as a base, the code is very simple and readable, and the number of operations (for an n x n matrix) is roughly (n(n+1)^2)/4 which means that the determinant can be calculated near instantaneously for matrices of even 1000x1000 size. (I'm sure this can still be optimized much further)