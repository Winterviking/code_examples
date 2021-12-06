using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th_just_prog
{
    public enum E_GRID_TYPE
    {
        UNIFORM,
        RANDOM,
        CHEBYSHEV
    }

    public class InterpolationGridProvider : FunctionDataProvider
    {
//        private double from = 0;
//        private double to = 0;
//        private IFunction<double, double> function = null;
        public E_GRID_TYPE GridType
        {
            set
            {
                gridtype = value;
            }
        }

        private E_GRID_TYPE gridtype = E_GRID_TYPE.UNIFORM;

        public new void SetParameter(object data, int additionalData = 0)
        {
            base.SetParameter(data, additionalData);
            if (data.GetType() == typeof(E_GRID_TYPE))
            {
                gridtype = (E_GRID_TYPE)data;
            }
        }

        public new double[,] getAllPoints(int number)
        {
            double [,] res = null;
            if (function != null)
            {
                if (number > 2)
                {
                    if (from < to)
                    {
                        res = new double[number, 2];

                        double step = (to - from) / (number - 1);

                        // X GRID
                        switch (gridtype)
                        {
                            case E_GRID_TYPE.UNIFORM: // uniform grid
                                {
                                    res[0, 0] = from;
                                    for (int i = 1; i < number - 1; i++)
                                    {
                                        res[i, 0] = res[0, 0] + i * step;
                                    }
                                    res[number - 1, 0] = to;
                                }
                                break;
                            case E_GRID_TYPE.RANDOM:// trololo random grid
                                {//TODO:::: SORTING PLZ :D
                                    Random rand = new Random();
                                    res[0, 0] = from;
                                    for (int i = 1; i < number - 1; i++)
                                    {
                                        res[i, 0] = rand.NextDouble() * (to - from) + from;
                                    }
                                    res[number - 1, 0] = to;
                                }
                                break;
                            case E_GRID_TYPE.CHEBYSHEV:// chebysheff grid
                                {
                                    res[0, 0] = from;
                                    for (int i = 1; i < number - 1; i++)
                                    {
                                        res[i, 0] = (to + from) / 2 + (to - from) * Math.Cos((2 * (number - 1 - i) + 1) * Math.PI / (2 * (number))) / 2;
                                    }
                                    res[number - 1, 0] = to;
                                }
                                break;
                        }

                        // Y GRID
                        for (int i = 0; i < number; i++)
                        {
                            res[i, 1] = function.GetValueOfFunction(res[i, 0]);
                        }
                    }
                    else
                    {
                        SystemIO.Log("Error:: from >= to ");
                    }
                }
                else
                {
                    SystemIO.Log("Error:: number < 2");
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
