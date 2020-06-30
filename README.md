# Object-Oriented-Numerical-Modeling

The point of this program is to be able to solve linear algebra equations speficially with cholesky's method.

If you want to run it yourself make sure you're using `python3`.

Clone the repo. `git clone git@github.com:Uhuh/Object-Oriented-Numerical-Modeling.git`

Inside the folder you should be able to do `make && python(3) time_it.py`. This should result in 20 outputs incrementing by 5's.

What this shows is how fast these matrices at size (N-1)^2 can be solved by our program using cholesky's method.

The main point of the assignment was to get familiar with abstraction, function pointers and generic typing for C++ to create some pretty neat fast code. 

On an i5 6th gen I got 100 to run at about ~25 seconds.
