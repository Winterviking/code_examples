using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5thSaveMe
{
    //public struct interval<T>
    //{
    //    public T from;
    //    public T to;
    //}

    public struct SLAE<T>
    {
        public IMatrix<T> coefficients;
        public IVector<T> rightColumn;
    }
}