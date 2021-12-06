using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th_just_prog
{
    // pure analog of UniformGridProvider
    public class FunctionDataProvider : IDataProvider<double>
    {
        public IFunction<double, double> Function
        {
            set
            {
                function = value;
            }
        }
        public double From
        {
            get
            { return from; }
            set
            { from = value; }
        }
        public double To
        {
            get
            { return to; }
            set
            { to = value; }
        }

        protected IFunction<double, double> function = null;
        protected double from = 0;
        protected double to = 0;

        public void SetParameter(object data, int additionalData = 0)
        {
            if (data.GetType() == typeof(double))
            {
                if (additionalData == 1)
                {
                    from = (double)data;
                }
                else if (additionalData == 2)
                {
                    to = (double)data;
                }
            }
            else if (additionalData == 100)
            {
                function = (IFunction<double, double>)data;
            }
        }

        public double[,] getAllPoints(int number)
        {
            double[,] res = null;
            if ( function != null )
            {
                if (number > 0)
                {
                    if (from < to)
                    {
                        res = new double [number,2];

                        double step = (to - from) / (number - 1);

                        // X generation
                        res[0, 0] = from;
                        for (int i = 1; i < number - 1; i++)
                        {
                            res[i, 0] = res[0, 0] + i * step;
                        }
                        res[number - 1, 0] = to;

                        // Y generation
                        for (int i = 0; i < number; i++)
                        {
                            res[i, 1] = function.GetValueOfFunction(res[i, 0]);
                        }
                    }
                    else
                    {
                        SystemIO.Log("Error:: from >= to");
                    }
                }
                else
                {
                    SystemIO.Log("Error:: incorrect number");
                }
            }
            else
            {
                SystemIO.Log("Error:: Function is not set");
            }

            return res;
        }
    }
}
