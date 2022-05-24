@page SystemOfEquations System Of Equations
@tableofcontents

----

This page is dedicated to the methods to solve the systems of equations

----
# System of equations

The main problem to solve is a system of equations in form:
\f{equation}{
\left[ \begin{matrix}
   {{a}_{1,1}} & {{a}_{1,2}} & {{a}_{1,3}} & \cdots  & {{a}_{1,n-1}} & {{a}_{1,n}}  \\
   {{a}_{2,1}} & {{a}_{2,2}} & {{a}_{2,3}} & \cdots  & {{a}_{2,n-1}} & {{a}_{2,n}}  \\
   {{a}_{3,1}} & {{a}_{3,2}} & {{a}_{3,3}} & \cdots  & {{a}_{3,n-1}} & {{a}_{3,n}}  \\
   \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots   \\
   {{a}_{i,1}} & {{a}_{i,2}} & {{a}_{i,3}} & \cdots  & {{a}_{i,n-1}} & {{a}_{i,n}}  \\
   \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots   \\
   {{a}_{n-1,1}} & {{a}_{n-1,2}} & {{a}_{n-1,3}} & \cdots  & {{a}_{n-1,n-1}} & {{a}_{n-1,n}}  \\
   {{a}_{n,1}} & {{a}_{n,2}} & {{a}_{n,3}} & \cdots  & {{a}_{n,n-1}} & {{a}_{n,n}}  \\
\end{matrix} \right]\left\{ \begin{matrix}
   {{x}_{1}}  \\
   {{x}_{2}}  \\
   {{x}_{3}}  \\
   \cdots   \\
   {{x}_{i}}  \\
   \cdots   \\
   {{x}_{n-1}}  \\
   {{x}_{n}}  \\
\end{matrix} \right\}=\left\{ \begin{matrix}
   {{b}_{1}}  \\
   {{b}_{2}}  \\
   {{b}_{3}}  \\
   \cdots   \\
   {{b}_{i}}  \\
   \cdots   \\
   {{b}_{n-1}}  \\
   {{b}_{n}}  \\
\end{matrix} \right\}

\f}

Three methods were implemented to solve the system of equations: Jacobi, Gauss Siedel and Sucessive Over Relaxations (SOR)

## Jacobi

Following the Jacobi algorithm at each iteration the system unknowns are updated as follows:

\f{equation}{
\begin{matrix}
   x_{1}^{{}} & = & \begin{matrix}
   \frac{1}{{{a}_{1,1}}}  \\
\end{matrix} & ({{b}_{1}} & +0 & -{{a}_{1,2}}x_{2}^{0} & -{{a}_{1,3}}x_{3}^{0} & \cdots  & -{{a}_{1,i-1}}x_{i-1}^{0} & \cdots  & -{{a}_{1,i+1}}x_{i+1}^{0} & \cdots  & -{{a}_{1,n-1}}x_{n-1}^{0} & -{{a}_{1,n}}x_{n}^{0})  \\
   x_{2}^{{}} & = & \frac{1}{{{a}_{2,2}}} & ({{b}_{2}} & -{{a}_{2,1}}x_{1}^{0} & +0 & -{{a}_{2,3}}x_{3}^{0} & \cdots  & -{{a}_{2,i-1}}x_{i-1}^{0} & \cdots  & -{{a}_{2,i+1}}x_{i+1}^{0} & \cdots  & -{{a}_{2,n-1}}x_{n-1}^{0} & -{{a}_{2,n}}x_{n}^{0})  \\
   x_{3}^{{}} & = & \frac{1}{{{a}_{3,3}}} & ({{b}_{3}} & -{{a}_{3,1}}x_{1}^{0} & -{{a}_{3,2}}x_{2}^{0} & +0 & \cdots  & -{{a}_{3,i-1}}x_{i-1}^{0} & \cdots  & -{{a}_{3,i+1}}x_{i+1}^{0} & \cdots  & -{{a}_{3,n-1}}x_{n-1}^{0} & -{{a}_{3,n}}x_{n}^{0})  \\
   {} & {} & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots   \\
   x_{i}^{{}} & = & \frac{1}{{{a}_{i,i}}} & ({{b}_{i}} & -{{a}_{i,1}}x_{1}^{0} & -{{a}_{i,2}}x_{2}^{0} & -{{a}_{i,3}}x_{3}^{0} & \cdots  & -{{a}_{i,i-1}}x_{i-1}^{0} & +0 & -{{a}_{i,i+1}}x_{i+1}^{0} & \cdots  & -{{a}_{i,n-1}}x_{n-1}^{0} & -{{a}_{i,n}}x_{n}^{0})  \\
   {} & {} & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots   \\
   x_{n-1}^{{}} & = & \frac{1}{{{a}_{n-1,n-1}}} & ({{b}_{n-1}} & -{{a}_{n-1,1}}x_{1}^{0} & -{{a}_{n-1,2}}x_{2}^{0} & -{{a}_{n-1,3}}x_{3}^{0} & \cdots  & -{{a}_{n-1,i-1}}x_{i-1}^{0} & \cdots  & -{{a}_{n-1,i+1}}x_{i+1}^{0} & \cdots  & +0 & -{{a}_{n-1,n}}x_{n}^{0})  \\
   x_{n}^{{}} & = & \frac{1}{{{a}_{n,n}}} & ({{b}_{n}} & -{{a}_{n,1}}x_{1}^{0} & -{{a}_{n,2}}x_{2}^{0} & -{{a}_{n,3}}x_{3}^{0} & \cdots  & -{{a}_{n,i-1}}x_{i-1}^{0} & \cdots  & -{{a}_{n,i+1}}x_{i+1}^{0} & \cdots  & -{{a}_{n,n-1}}x_{n-1}^{0} & +0)  \\
\end{matrix}

\f}

## Gauss Siedel

Following the Gauss Siedel algorithm at each iteration the system unknowns are updated as follows:

\f{equation}{
\begin{matrix}
   x_{1}^{{}} & = & \begin{matrix}
   \frac{1}{{{a}_{1,1}}}  \\
\end{matrix} & ({{b}_{1}} & +0 & -{{a}_{1,2}}x_{2}^{0} & -{{a}_{1,3}}x_{3}^{0} & \cdots  & -{{a}_{1,i-1}}x_{i-1}^{0} & \cdots  & -{{a}_{1,i+1}}x_{i+1}^{0} & \cdots  & -{{a}_{1,n-1}}x_{n-1}^{0} & -{{a}_{1,n}}x_{n}^{0})  \\
   x_{2}^{{}} & = & \frac{1}{{{a}_{2,2}}} & ({{b}_{2}} & -{{a}_{2,1}}x_{1}^{{}} & +0 & -{{a}_{2,3}}x_{3}^{0} & \cdots  & -{{a}_{2,i-1}}x_{i-1}^{0} & \cdots  & -{{a}_{2,i+1}}x_{i+1}^{0} & \cdots  & -{{a}_{2,n-1}}x_{n-1}^{0} & -{{a}_{2,n}}x_{n}^{0})  \\
   x_{3}^{{}} & = & \frac{1}{{{a}_{3,3}}} & ({{b}_{3}} & -{{a}_{3,1}}x_{1}^{{}} & -{{a}_{3,2}}x_{2}^{{}} & +0 & \cdots  & -{{a}_{3,i-1}}x_{i-1}^{0} & \cdots  & -{{a}_{3,i+1}}x_{i+1}^{0} & \cdots  & -{{a}_{3,n-1}}x_{n-1}^{0} & -{{a}_{3,n}}x_{n}^{0})  \\
   {} & {} & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots   \\
   x_{i}^{{}} & = & \frac{1}{{{a}_{i,i}}} & ({{b}_{i}} & -{{a}_{i,1}}x_{1}^{{}} & -{{a}_{i,2}}x_{2}^{{}} & -{{a}_{i,3}}x_{3}^{{}} & \cdots  & -{{a}_{i,i-1}}x_{i-1}^{{}} & +0 & -{{a}_{i,i+1}}x_{i+1}^{0} & \cdots  & -{{a}_{i,n-1}}x_{n-1}^{0} & -{{a}_{i,n}}x_{n}^{0})  \\
   {} & {} & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots   \\
   x_{n-1}^{{}} & = & \frac{1}{{{a}_{n-1,n-1}}} & ({{b}_{n-1}} & -{{a}_{n-1,1}}x_{1}^{{}} & -{{a}_{n-1,2}}x_{2}^{{}} & -{{a}_{n-1,3}}x_{3}^{{}} & \cdots  & -{{a}_{n-1,i-1}}x_{i-1}^{{}} & \cdots  & -{{a}_{n-1,i+1}}x_{i+1}^{{}} & \cdots  & +0 & -{{a}_{n-1,n}}x_{n}^{0})  \\
   x_{n}^{{}} & = & \frac{1}{{{a}_{n,n}}} & ({{b}_{n}} & -{{a}_{n,1}}x_{1}^{{}} & -{{a}_{n,2}}x_{2}^{{}} & -{{a}_{n,3}}x_{3}^{{}} & \cdots  & -{{a}_{n,i-1}}x_{i-1}^{{}} & \cdots  & -{{a}_{n,i+1}}x_{i+1}^{{}} & \cdots  & -{{a}_{n,n-1}}x_{n-1}^{{}} & +0)  \\
\end{matrix}
\f}

## SOR

Following the SOR algorithm at each iteration the system unknowns are updated as follows:

\f{equation}{

\begin{matrix}
   x_{1}^{{}} & = & \begin{matrix}
   \frac{1}{{{a}_{1,1}}}  \\
\end{matrix} & ({{b}_{1}} & +0 & -{{a}_{1,2}}x_{2}^{0} & -{{a}_{1,3}}x_{3}^{0} & \cdots  & -{{a}_{1,i-1}}x_{i-1}^{0} & \cdots  & -{{a}_{1,i+1}}x_{i+1}^{0} & \cdots  & -{{a}_{1,n-1}}x_{n-1}^{0} & -{{a}_{1,n}}x_{n}^{0})  \\
   x_{2}^{{}} & = & \frac{1}{{{a}_{2,2}}} & ({{b}_{2}} & -{{a}_{2,1}}x_{1}^{{}} & +0 & -{{a}_{2,3}}x_{3}^{0} & \cdots  & -{{a}_{2,i-1}}x_{i-1}^{0} & \cdots  & -{{a}_{2,i+1}}x_{i+1}^{0} & \cdots  & -{{a}_{2,n-1}}x_{n-1}^{0} & -{{a}_{2,n}}x_{n}^{0})  \\
   x_{3}^{{}} & = & \frac{1}{{{a}_{3,3}}} & ({{b}_{3}} & -{{a}_{3,1}}x_{1}^{{}} & -{{a}_{3,2}}x_{2}^{{}} & +0 & \cdots  & -{{a}_{3,i-1}}x_{i-1}^{0} & \cdots  & -{{a}_{3,i+1}}x_{i+1}^{0} & \cdots  & -{{a}_{3,n-1}}x_{n-1}^{0} & -{{a}_{3,n}}x_{n}^{0})  \\
   {} & {} & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots   \\
   x_{i}^{{}} & = & \frac{1}{{{a}_{i,i}}} & ({{b}_{i}} & -{{a}_{i,1}}x_{1}^{{}} & -{{a}_{i,2}}x_{2}^{{}} & -{{a}_{i,3}}x_{3}^{{}} & \cdots  & -{{a}_{i,i-1}}x_{i-1}^{{}} & +0 & -{{a}_{i,i+1}}x_{i+1}^{0} & \cdots  & -{{a}_{i,n-1}}x_{n-1}^{0} & -{{a}_{i,n}}x_{n}^{0})  \\
   {} & {} & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots  & \cdots   \\
   x_{n-1}^{{}} & = & \frac{1}{{{a}_{n-1,n-1}}} & ({{b}_{n-1}} & -{{a}_{n-1,1}}x_{1}^{{}} & -{{a}_{n-1,2}}x_{2}^{{}} & -{{a}_{n-1,3}}x_{3}^{{}} & \cdots  & -{{a}_{n-1,i-1}}x_{i-1}^{{}} & \cdots  & -{{a}_{n-1,i+1}}x_{i+1}^{{}} & \cdots  & +0 & -{{a}_{n-1,n}}x_{n}^{0})  \\
   x_{n}^{{}} & = & \frac{1}{{{a}_{n,n}}} & ({{b}_{n}} & -{{a}_{n,1}}x_{1}^{{}} & -{{a}_{n,2}}x_{2}^{{}} & -{{a}_{n,3}}x_{3}^{{}} & \cdots  & -{{a}_{n,i-1}}x_{i-1}^{{}} & \cdots  & -{{a}_{n,i+1}}x_{i+1}^{{}} & \cdots  & -{{a}_{n,n-1}}x_{n-1}^{{}} & +0)  \\
\end{matrix}

\f}

This page is dedicated to the system of equations.

\image html SyssOfEq.svg "Figure 1: Problem solving Algorithm" width=350px

### General
General system of equations with a sparse matrix

\f{equation}{
    \left[ A \right]\left\{ x \right\} = \left\{ b \right\}
\f}

\f{equation}{
\label{Eq:1}   
        \left[ {\begin{array}{*{20}{c}}
        {{a_{1,1}}}&{{a_{1,2}}}&{{a_{1,3}}}& \cdots &{{a_{1,n - 1}}}&{{a_{1,n}}}\\
        {{a_{2,1}}}&{{a_{2,2}}}&{{a_{2,3}}}& \cdots &{{a_{2,n - 1}}}&{{a_{2,n}}}\\
        {{a_{3,1}}}&{{a_{3,2}}}&{{a_{3,3}}}& \cdots &{{a_{3,n - 1}}}&{{a_{3,n}}}\\
        \cdots & \cdots & \cdots & \cdots & \cdots & \cdots \\
        {{a_{i,1}}}&{{a_{i,2}}}&{{a_{i,3}}}& \cdots &{{a_{i,n - 1}}}&{{a_{i,n}}}\\
        \cdots & \cdots & \cdots & \cdots & \cdots & \cdots \\
        {{a_{n - 1,1}}}&{{a_{n - 1,2}}}&{{a_{n - 1,3}}}& \cdots &{{a_{n - 1,n - 1}}}&{{a_{n - 1,n}}}\\
        {{a_{n,1}}}&{{a_{n,2}}}&{{a_{n,3}}}& \cdots &{{a_{n,n - 1}}}&{{a_{n,n}}}
        \end{array}} \right]\left\{ {\begin{array}{*{20}{c}}
        {{x_1}}\\
        {{x_2}}\\
        {{x_3}}\\
        \cdots \\
        {{x_i}}\\
        \cdots \\
        {{x_{n - 1}}}\\
        {{x_n}}
        \end{array}} \right\} = \left\{ {\begin{array}{*{20}{c}}
        {{b_1}}\\
        {{b_2}}\\
        {{b_3}}\\
        \cdots \\
        {{b_i}}\\
        \cdots \\
        {{b_{n - 1}}}\\
        {{b_n}}
        \end{array}} \right\}
    
\f}


----

### Jacobi
Resolve a system of equations using Jacobi method

In numerical linear algebra, the Jacobi method is an iterative algorithm for determining the solutions of a strictly diagonally dominant system of linear equations. 
Each diagonal element is solved for, and an approximate value is plugged in. 
The process is then iterated until it converges. 
The method is named after Carl Gustav Jacob Jacobi.

\f{equation}{

    \begin{array}{*{20}{c}}
    {x_1^{}}& = &{\begin{array}{*{20}{c}}
    {\frac{1}{{{a_{1,1}}}}}
    \end{array}}&{({b_1}}&{ + 0}&{ - {a_{1,2}}x_2^0}&{ - {a_{1,3}}x_3^0}& \cdots &{ - {a_{1,i - 1}}x_{i - 1}^0}& \cdots &{ - {a_{1,i + 1}}x_{i + 1}^0}& \cdots &{ - {a_{1,n - 1}}x_{n - 1}^0}&{ - {a_{1,n}}x_n^0)}\\
    {x_2^{}}& = &{\frac{1}{{{a_{2,2}}}}}&{({b_2}}&{ - {a_{2,1}}x_1^0}&{ + 0}&{ - {a_{2,3}}x_3^0}& \cdots &{ - {a_{2,i - 1}}x_{i - 1}^0}& \cdots &{ - {a_{2,i + 1}}x_{i + 1}^0}& \cdots &{ - {a_{2,n - 1}}x_{n - 1}^0}&{ - {a_{2,n}}x_n^0)}\\
    {x_3^{}}& = &{\frac{1}{{{a_{3,3}}}}}&{({b_3}}&{ - {a_{3,1}}x_1^0}&{ - {a_{3,2}}x_2^0}&{ + 0}& \cdots &{ - {a_{3,i - 1}}x_{i - 1}^0}& \cdots &{ - {a_{3,i + 1}}x_{i + 1}^0}& \cdots &{ - {a_{3,n - 1}}x_{n - 1}^0}&{ - {a_{3,n}}x_n^0)}\\
    {}&{}& \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots \\
    {x_i^{}}& = &{\frac{1}{{{a_{i,i}}}}}&{({b_i}}&{ - {a_{i,1}}x_1^0}&{ - {a_{i,2}}x_2^0}&{ - {a_{i,3}}x_3^0}& \cdots &{ - {a_{i,i - 1}}x_{i - 1}^0}&{ + 0}&{ - {a_{i,i + 1}}x_{i + 1}^0}& \cdots &{ - {a_{i,n - 1}}x_{n - 1}^0}&{ - {a_{i,n}}x_n^0)}\\
    {}&{}& \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots \\
    {x_{n - 1}^{}}& = &{\frac{1}{{{a_{n - 1,n - 1}}}}}&{({b_{n - 1}}}&{ - {a_{n - 1,1}}x_1^0}&{ - {a_{n - 1,2}}x_2^0}&{ - {a_{n - 1,3}}x_3^0}& \cdots &{ - {a_{n - 1,i - 1}}x_{i - 1}^0}& \cdots &{ - {a_{n - 1,i + 1}}x_{i + 1}^0}& \cdots &{ + 0}&{ - {a_{n - 1,n}}x_n^0)}\\
    {x_n^{}}& = &{\frac{1}{{{a_{n,n}}}}}&{({b_n}}&{ - {a_{n,1}}x_1^0}&{ - {a_{n,2}}x_2^0}&{ - {a_{n,3}}x_3^0}& \cdots &{ - {a_{n,i - 1}}x_{i - 1}^0}& \cdots &{ - {a_{n,i + 1}}x_{i + 1}^0}& \cdots &{ - {a_{n,n - 1}}x_{n - 1}^0}&{ + 0)}
    \end{array}


\f}


\f{equation}{
    \left\{ {\begin{array}{*{20}{c}}
    {{x_1}}\\
    {{x_2}}\\
    {{x_3}}\\
    \cdots \\
    {{x_i}}\\
    \cdots \\
    {{x_{n - 1}}}\\
    {{x_n}}
    \end{array}} \right\} = \left\{ {\begin{array}{*{20}{c}}
    {{b_1}}\\
    {{b_2}}\\
    {{b_3}}\\
    \cdots \\
    {{b_i}}\\
    \cdots \\
    {{b_{n - 1}}}\\
    {{b_n}}
    \end{array}} \right\} - \left[ {\begin{array}{*{20}{c}}
    0&{{a_{1,2}}}&{{a_{1,3}}}& \cdots &{{a_{1,n - 1}}}&{{a_{1,n}}}\\
    {{a_{2,1}}}&0&{{a_{2,3}}}& \cdots &{{a_{2,n - 1}}}&{{a_{2,n}}}\\
    {{a_{3,1}}}&{{a_{3,2}}}&0& \cdots &{{a_{3,n - 1}}}&{{a_{3,n}}}\\
    \cdots & \cdots & \cdots & \cdots & \cdots & \cdots \\
    {{a_{i,1}}}&{{a_{i,2}}}&{{a_{i,3}}}& \cdots &{{a_{i,n - 1}}}&{{a_{i,n}}}\\
    \cdots & \cdots & \cdots & \cdots & \cdots & \cdots \\
    {{a_{n - 1,1}}}&{{a_{n - 1,2}}}&{{a_{n - 1,3}}}& \cdots &0&{{a_{n - 1,n}}}\\
    {{a_{n,1}}}&{{a_{n,2}}}&{{a_{n,3}}}& \cdots &{{a_{n,n - 1}}}&0
    \end{array}} \right]\left\{ {\begin{array}{*{20}{c}}
    {x_1^0}\\
    {x_2^0}\\
    {x_3^0}\\
    \cdots \\
    {x_i^0}\\
    \cdots \\
    {x_{n - 1}^0}\\
    {x_n^0}
    \end{array}} \right\}\begin{array}{*{20}{l}}
    {}\\
    {}\\
    {}\\
    {}\\
    {}\\
    {}\\
    {}\\
    {}
    \end{array}\left| {\begin{array}{*{20}{l}}
    {}\\
    {}\\
    {}\\
    {}\\
    {}\\
    {}\\
    {}\\
    {}
    \end{array}} \right.\left\{ {\begin{array}{*{20}{c}}
    {{x_1}}\\
    {{x_2}}\\
    {{x_3}}\\
    \cdots \\
    {{x_i}}\\
    \cdots \\
    {{x_{n - 1}}}\\
    {{x_n}}
    \end{array}} \right\} = \left\{ {\begin{array}{*{20}{l}}
    {{{{x_1}} \mathord{\left/
    {\vphantom {{{x_1}} {{a_{1,1}}}}} \right.
    } {{a_{1,1}}}}}\\
    {{{{x_2}} \mathord{\left/
    {\vphantom {{{x_2}} {{a_{2,2}}}}} \right.
    } {{a_{2,2}}}}}\\
    {{{{x_3}} \mathord{\left/
    {\vphantom {{{x_3}} {{a_{3,3}}}}} \right.
    } {{a_{3,3}}}}}\\
    \cdots \\
    {{{{x_i}} \mathord{\left/
    {\vphantom {{{x_i}} {{a_{i,i}}}}} \right.
    } {{a_{i,i}}}}}\\
    \cdots \\
    {{{{x_{n - 1}}} \mathord{\left/
    {\vphantom {{{x_{n - 1}}} {{a_{n - 1,n - 1}}}}} \right.
    } {{a_{n - 1,n - 1}}}}}\\
    {{{{x_n}} \mathord{\left/
    {\vphantom {{{x_n}} {{a_{n,n}}}}} \right.
    } {{a_{n,n}}}}}
    \end{array}} \right\}\

\f}


----

### Gauss-Seidel
In numerical linear algebra, the Gauss–Seidel method, also known as the Liebmann method or the method of successive displacement, is an iterative method used to solve a system of linear equations. 
It is named after the German mathematicians Carl Friedrich Gauss and Philipp Ludwig von Seidel, and is similar to the Jacobi method. 
Though it can be applied to any matrix with non-zero elements on the diagonals, convergence is only guaranteed if the matrix is either strictly diagonally dominant, or symmetric and positive definite. 
It was only mentioned in a private letter from Gauss to his student Gerling in 1823.
A publication was not delivered before 1874 by Seidel.

\f{equation}{

    \begin{array}{*{20}{c}}
    {x_1^{}}& = &{\begin{array}{*{20}{c}}
    {\frac{1}{{{a_{1,1}}}}}
    \end{array}}&{({b_1}}&{ + 0}&{ - {a_{1,2}}x_2^0}&{ - {a_{1,3}}x_3^0}& \cdots &{ - {a_{1,i - 1}}x_{i - 1}^0}& \cdots &{ - {a_{1,i + 1}}x_{i + 1}^0}& \cdots &{ - {a_{1,n - 1}}x_{n - 1}^0}&{ - {a_{1,n}}x_n^0)}\\
    {x_2^{}}& = &{\frac{1}{{{a_{2,2}}}}}&{({b_2}}&{ - {a_{2,1}}x_1^{}}&{ + 0}&{ - {a_{2,3}}x_3^0}& \cdots &{ - {a_{2,i - 1}}x_{i - 1}^0}& \cdots &{ - {a_{2,i + 1}}x_{i + 1}^0}& \cdots &{ - {a_{2,n - 1}}x_{n - 1}^0}&{ - {a_{2,n}}x_n^0)}\\
    {x_3^{}}& = &{\frac{1}{{{a_{3,3}}}}}&{({b_3}}&{ - {a_{3,1}}x_1^{}}&{ - {a_{3,2}}x_2^{}}&{ + 0}& \cdots &{ - {a_{3,i - 1}}x_{i - 1}^0}& \cdots &{ - {a_{3,i + 1}}x_{i + 1}^0}& \cdots &{ - {a_{3,n - 1}}x_{n - 1}^0}&{ - {a_{3,n}}x_n^0)}\\
    {}&{}& \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots \\
    {x_i^{}}& = &{\frac{1}{{{a_{i,i}}}}}&{({b_i}}&{ - {a_{i,1}}x_1^{}}&{ - {a_{i,2}}x_2^{}}&{ - {a_{i,3}}x_3^{}}& \cdots &{ - {a_{i,i - 1}}x_{i - 1}^{}}&{ + 0}&{ - {a_{i,i + 1}}x_{i + 1}^0}& \cdots &{ - {a_{i,n - 1}}x_{n - 1}^0}&{ - {a_{i,n}}x_n^0)}\\
    {}&{}& \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots & \cdots \\
    {x_{n - 1}^{}}& = &{\frac{1}{{{a_{n - 1,n - 1}}}}}&{({b_{n - 1}}}&{ - {a_{n - 1,1}}x_1^{}}&{ - {a_{n - 1,2}}x_2^{}}&{ - {a_{n - 1,3}}x_3^{}}& \cdots &{ - {a_{n - 1,i - 1}}x_{i - 1}^{}}& \cdots &{ - {a_{n - 1,i + 1}}x_{i + 1}^{}}& \cdots &{ + 0}&{ - {a_{n - 1,n}}x_n^0)}\\
    {x_n^{}}& = &{\frac{1}{{{a_{n,n}}}}}&{({b_n}}&{ - {a_{n,1}}x_1^{}}&{ - {a_{n,2}}x_2^{}}&{ - {a_{n,3}}x_3^{}}& \cdots &{ - {a_{n,i - 1}}x_{i - 1}^{}}& \cdots &{ - {a_{n,i + 1}}x_{i + 1}^{}}& \cdots &{ - {a_{n,n - 1}}x_{n - 1}^{}}&{ + 0)}
    \end{array}


\f}

\f{equation}{
    \left\{ {\begin{array}{*{20}{c}}
    {{x_1}}\\
    {{x_2}}\\
    {{x_3}}\\
    \cdots \\
    {{x_i}}\\
    \cdots \\
    {{x_{n - 1}}}\\
    {{x_n}}
    \end{array}} \right\} = \left\{ {\begin{array}{*{20}{c}}
    {{b_1}}\\
    {{b_2}}\\
    {{b_3}}\\
    \cdots \\
    {{b_i}}\\
    \cdots \\
    {{b_{n - 1}}}\\
    {{b_n}}
    \end{array}} \right\} - \left[ {\begin{array}{*{20}{c}}
    0&{{a_{1,2}}}&{{a_{1,3}}}& \cdots &{{a_{1,n - 1}}}&{{a_{1,n}}}\\
    {{a_{2,1}}}&0&{{a_{2,3}}}& \cdots &{{a_{2,n - 1}}}&{{a_{2,n}}}\\
    {{a_{3,1}}}&{{a_{3,2}}}&0& \cdots &{{a_{3,n - 1}}}&{{a_{3,n}}}\\
    \cdots & \cdots & \cdots & \cdots & \cdots & \cdots \\
    {{a_{i,1}}}&{{a_{i,2}}}&{{a_{i,3}}}& \cdots &{{a_{i,n - 1}}}&{{a_{i,n}}}\\
    \cdots & \cdots & \cdots & \cdots & \cdots & \cdots \\
    {{a_{n - 1,1}}}&{{a_{n - 1,2}}}&{{a_{n - 1,3}}}& \cdots &0&{{a_{n - 1,n}}}\\
    {{a_{n,1}}}&{{a_{n,2}}}&{{a_{n,3}}}& \cdots &{{a_{n,n - 1}}}&0
    \end{array}} \right]\left\{ {\begin{array}{*{20}{c}}
    {x_1^*}\\
    {x_2^*}\\
    {x_3^*}\\
    \cdots \\
    {x_i^*}\\
    \cdots \\
    {x_{n - 1}^*}\\
    {x_n^*}
    \end{array}} \right\}\begin{array}{*{20}{l}}
    {}\\
    {}\\
    {}\\
    {}\\
    {}\\
    {}\\
    {}\\
    {}
    \end{array}\left| {\begin{array}{*{20}{l}}
    {}\\
    {}\\
    {}\\
    {}\\
    {}\\
    {}\\
    {}\\
    {}
    \end{array}} \right.\left\{ {\begin{array}{*{20}{c}}
    {{x_1}}\\
    {{x_2}}\\
    {{x_3}}\\
    \cdots \\
    {{x_i}}\\
    \cdots \\
    {{x_{n - 1}}}\\
    {{x_n}}
    \end{array}} \right\} = \left\{ {\begin{array}{*{20}{l}}
    {{{{x_1}} \mathord{\left/
    {\vphantom {{{x_1}} {{a_{1,1}}}}} \right.
    } {{a_{1,1}}}}}\\
    {{{{x_2}} \mathord{\left/
    {\vphantom {{{x_2}} {{a_{2,2}}}}} \right.
    } {{a_{2,2}}}}}\\
    {{{{x_3}} \mathord{\left/
    {\vphantom {{{x_3}} {{a_{3,3}}}}} \right.
    } {{a_{3,3}}}}}\\
    \cdots \\
    {{{{x_i}} \mathord{\left/
    {\vphantom {{{x_i}} {{a_{i,i}}}}} \right.
    } {{a_{i,i}}}}}\\
    \cdots \\
    {{{{x_{n - 1}}} \mathord{\left/
    {\vphantom {{{x_{n - 1}}} {{a_{n - 1,n - 1}}}}} \right.
    } {{a_{n - 1,n - 1}}}}}\\
    {{{{x_n}} \mathord{\left/
    {\vphantom {{{x_n}} {{a_{n,n}}}}} \right.
    } {{a_{n,n}}}}}
    \end{array}} \right\}

\f}

----

### SOR (Successive over-relaxation)
In numerical linear algebra, the method of successive over-relaxation (SOR) is a variant of the Gauss–Seidel method for solving a linear system of equations, resulting in faster convergence. 
A similar method can be used for any slowly converging iterative process.

It was devised simultaneously by David M. Young Jr. and by Stanley P. Frankel in 1950 for the purpose of automatically solving linear systems on digital computers.
Over-relaxation methods had been used before the work of Young and Frankel. 
An example is the method of Lewis Fry Richardson, and the methods developed by R. V. Southwell. 
However, these methods were designed for computation by human calculators, requiring some expertise to ensure convergence to the solution which made them inapplicable for programming on digital computers. 
These aspects are discussed in the thesis of David M. Young Jr.

\f{equation}{
    x_i^{k + 1} = \left( {1 - \omega } \right)x_i^k + \frac{\omega }{{{a_{i,i}}}}\left( {{b_i} - \mathop \sum \limits_{j < i} {a_{i,j}}x_j^{k + 1} - \mathop \sum \limits_{j > i} {a_{i,j}}x_j^k} \right) 
\f}


\f{equation}{
    {x_1} = \left( {1 - \omega } \right)x_1^0 + \frac{\omega }{{{a_{1,1}}}}\left( {{b_1} + 0 - {a_{1,2}}x_2^0\; - {a_{1,3}}x_3^0\;... - {a_{1,i - 1}}x_{i - 1}^0\;... - {a_{1,i + 1}}x_{i + 1}^0... - {a_{1,n - 1}}x_{n - 1}^0 - {a_{1,n}}x_n^0} \right)\\
    
    {x_2} = \left( {1 - \omega } \right)x_2^0 + \frac{\omega }{{{a_{2,2}}}}\left( {{b_2} - {a_{2,1}}{x_1} + 0 - {a_{2,3}}x_3^0\;... - {a_{2,i - 1}}x_{i - 1}^0... - {a_{2,i + 1}}x_{i + 1}^0\;... - {a_{2,n - 1}}x_{n - 1}^0 - {a_{2,n}}x_n^0} \right)\\

    {x_3} = \left( {1 - \omega } \right)x_3^0 + \frac{\omega }{{{a_{3,3}}}}\left( {{b_3} - {a_{3,1}}{x_1} - {a_{3,2}}{x_2} + 0\;... - {a_{3,i - 1}}x_{i - 1}^0... - {a_{3,i + 1}}x_{i + 1}^0\;... - {a_{3,n - 1}}x_{n - 1}^0 - {a_{3,n}}x_n^0} \right)\\

    {x_i} = \left( {1 - \omega } \right)x_i^0 + \frac{\omega }{{{a_{i,i}}}}\left( {{b_i} - {a_{i,1}}{x_1} - {a_{i,2}}{x_2} - {a_{i,3}}{x_3}... - {a_{i,i - 1}}{x_{i - 1}} + 0 - {a_{i,i + 1}}x_{i + 1}^0\;... - {a_{i,n - 1}}x_{n - 1}^0 - {a_{i,n}}x_n^0} \right)\\

    {x_{n - 1}} = \left( {1 - \omega } \right)x_{n - 1}^0 + \frac{\omega }{{{a_{n - 1,n - 1}}}}\left( {{b_{n - 1}} - {a_{n - 1,1}}{x_1} - {a_{n - 1,2}}{x_2} - {a_{n - 1,3}}{x_3}... - {a_{n - 1,i - 1}}{x_{i - 1}}... - {a_{n - 1,i + 1}}{x_{i + 1}}\;... + 0 - {a_{n - 1,n}}x_n^0} \right)\\

    {x_n} = \left( {1 - \omega } \right)x_n^0 + \frac{\omega }{{{a_{n,n}}}}\left( {{b_n} - {a_{n,1}}{x_1} - {a_{n,2}}{x_2} - {a_{n,3}}{x_3}... - {a_{n,i - 1}}{x_{i - 1}}... - {a_{n,i + 1}}{x_{i + 1}}\;... - {a_{n,n - 1}}{x_{n - 1}} + 0} \right)
\f}


















----

### Residual calculation

The residual vector (\f$R\f$) is calculated as 

\begin{equation}
\begin{pmatrix}
R
\end{pmatrix} = \begin{bmatrix}
A
\end{bmatrix}\begin{pmatrix}
X
\end{pmatrix} - \begin{pmatrix}
B
\end{pmatrix}
\end{equation}



\begin{equation}
\begin{pmatrix}
r_1\\
\newline 
r_2\\ 
\newline
r_3\\ 
\newline
...\\ 
\newline
...\\ 
\newline
r_{i-1}\\ 
\newline
r_i\\ 
\newline
r_{i+1}\\ 
\newline
...\\ 
\newline
...\\
\newline 
r_{n-1}\\ 
\newline
r_n
\end{pmatrix}=\begin{pmatrix}
 a_{1,1}& a_{1,2} & a_{1,3} & ... & ... & a_{1,i-1} & a_{1,i} & a_{1,i+1} & ... & ... & a_{1,n-1} &a_{1,n} \\ 
 \newline
 a_{2,1}& a_{2,2} & a_{2,3} & ... & ... & a_{2,i-1} & a_{2,i} & a_{2,i+1} & ... & ... & a_{2,n-1} & a_{2,n}\\ 
 \newline
 a_{3,1}& a_{3,2} & a_{3,3} &...  & ... & a_{3,i-1} & a_{3,i} & a_{3,i+1} & ... & ... & a_{3,n-1} & a_{3,n}\\ 
 \newline
 ...& ... &...  &...  & ... &...  & ... & ... & ... & ... & ... & ...\\ 
 \newline
 ...& ... & ... & ... & ... & ... & ... & ... & ... & ... & ... & ...\\ 
 \newline
 a_{i-1,1}&a_{i-1,2}  & a_{i-1,3} & ... & ... & a_{i-1,i-1} & a_{i-1,i} & a_{i-1,i+1} & ... & ... &  a_{i-1,n-1}& a_{i-1,n}\\ 
 \newline
a_{i,1} & a_{i,2} & a_{i,3} & ... & ... & a_{i,i-1} & a_{i,i} & a_{i,i+1} & ... & ... & a_{i,n-1} & a_{i,n}\\ 
\newline
 a_{i+1,1}& a_{i+1,2} & a_{i+1,3} & ... & ... & a_{i+1,i-1} & a_{i+1,i} & a_{i+1,i+1} & ... & ... &  a_{i+1,n-1}& a_{i+1,n}\\
 \newline 
 ...& ... & ... & ... &...  & ... & ... & ... & ... & ... & ... &... \\
 \newline 
... & ... & ... & ... & ... & ... & ... & ... & ... & ... & ... & ...\\ 
\newline
 a_{n-1,1}& a_{n-1,2} & a_{n-1,3} & ... &  ...& a_{n-1,i-1} & a_{n-1,i} & a_{n-1,i+1} & ... & ... &  a_{n-1,n-1}&a_{n-1,n} \\ 
 \newline
a_{n,1} & a_{n,2} & a_{n,3} & ... & ... & a_{n,i-1} & a_{n,i} & a_{n,i+1} & ... & ... & a_{n,n-1} & 
a_{n,n}\end{pmatrix} \begin{pmatrix}
x_1\\
\newline 
x_2\\ 
\newline
x_3\\ 
\newline
...\\ 
\newline
...\\ 
\newline
x_{i-1}\\ 
\newline
x_i\\ 
\newline
x_{i+1}\\ 
\newline
...\\ 
\newline
...\\
\newline 
x_{n-1}\\ 
\newline
x_n
\end{pmatrix}-\begin{pmatrix}
b_1\\
\newline 
b_2\\ 
\newline
b_3\\ 
\newline
...\\ 
\newline
...\\ 
\newline
b_{i-1}\\ 
\newline
b_i\\ 
\newline
b_{i+1}\\ 
\newline
...\\ 
\newline
...\\
\newline 
b_{n-1}\\ 
\newline
b_n
\end{pmatrix}
\end{equation}


The residual scalling factor (\f$n\f$) is calculated as

\begin{equation}
n=\sum_{i=1}^{N}
(\begin{vmatrix}
AX-A\overline{X}
\end{vmatrix}) +
\begin{vmatrix}
B-A\overline{X}
\end{vmatrix})
\end{equation}

\f$\overline{X}\f$ is the average of the solution vector {\f$X\f$}







The scalled residual \f$\left \| R \right \| \f$ is calculated as
\begin{equation}
\left \|\left \| R \right \|\right \|=\frac{1}{n} \sum_{i=1}^{N}\begin{vmatrix}
r_i
\end{vmatrix}
\end{equation}

The initial residual \f$\left \| R \right \|_0 \f$ is equal to the scalled residual at the first iteration

The relative residual \f$\left \| R \right \|_l \f$ is calculated as

\begin{equation}
\left \|\left \| R \right \|\right \|_l=\frac{\left \|\left \| R \right \|\right \|}{\left \|\left \| R \right \|\right \|_0}
\end{equation}

----



