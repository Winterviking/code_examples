using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th_just_prog
{
    interface IDataProvider<T>
    {
        void SetParameter(object data, int additionalData = 0);
        T[,] getAllPoints( int number );
    }
}
