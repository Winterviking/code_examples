using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5thSaveMe
{
    public class FunctionDataProcessor : IDataProcessor1D<double>
    {
        public FunctionDataProcessor(IFunction<double> function)
        {
            Processor = function;
        }

        public double[] Process(double[] data)
        { 
            double [] res = new double[data.Length];
            for ( int i = 0; i < data.Length; i++ )
            {
                res[i] = func(data[i]);
            }
            return res;
        }

        public IFunction<double> Processor
        {
            set
            {
                func = value.Function;
            }
        }

        DlgFunction<double> func;
    }
}

