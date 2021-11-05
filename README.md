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

 Eigenvectors:
 Eigenvectors themselves are easy to calculate once you have the eigenvalue, but with some research, eigenvalues are very difficult to implement.
 Need to research more about:
 QR-Factorization of a matrix