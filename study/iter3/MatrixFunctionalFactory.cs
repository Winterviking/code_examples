using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;


// Put all the functions liek trace etc here
namespace _5th_just_prog
{
    namespace Math
    {
        namespace matrix
        {
            public static class MatrixFunctionalFactory<T>
            {
                public static Determinant<T> det = new Determinant<T>();
                public static Trace<T> trace = new Trace<T>();
            }
        }
    }
}
