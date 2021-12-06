using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5thSaveMe
{
    // Static Wrapper for all the inputs
    namespace IO
    {
        static public class MatrixIO
        {
            static public IIOType<double[,]> Double = new DoubleMatrixIOCode();
        }
    }
}