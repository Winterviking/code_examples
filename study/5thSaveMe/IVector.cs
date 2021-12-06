using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5thSaveMe
{
    public interface IVector<T>
    {
        T[] Value
        {
            get;
            set;
        }

        IVector<T> Clone();

        T this[int x]
        {
            get;
            set;
        }

        T norm();

        void minus(ref IVector<T> operand2, ref IVector<T> res);
    }
}
