# Function-Plotter

## About the program


The program is given a mathematical expression and plots a graph for this function (if it is valid).
This done by converting the expression into postfix and then calculating the expression at different points.
######Note : the input must have no spaces and flow the mathematical expression rules in order to be valid.

Plotter specifications:

- The plotter Support the following operators **(+, -, \*, /, ^)** only.

- The Entered variable must be in terms of **x** only.

- The user is can specify the minimum, maximum values of x.
- The user can increase graph precesion by increasing the number of points used to draw graph.
- The Enter Button is a shortcut for the plot button.





## Test Cases


> *Valid Expression:* 5+x^2+3*x+1

![Valid Example](https://i.imgur.com/KLJB9DT.png "Valid Expression: 5+x^2+3*x+1")



> *Invalid Expression_1:* 5*i+

![Invalid Example](https://i.imgur.com/ZWMmEIE.png "Invalid Expression_1: 5*i+")


 *Invalid Expression_2:*  7x+3/0

![Invalid Example](https://i.imgur.com/D8oqFh6.png "Invalid Expression_2: 7x+3/0")