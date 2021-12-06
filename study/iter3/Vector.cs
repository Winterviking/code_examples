using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th_just_prog
{
    namespace Math
    {
        class Vector<T>
        {

            T[] Value
            {
                get 
                {
                    return vector;
                }
                set
                {
                    vector = value;
                }
            }

            T[] vector;
        }
    }
}
