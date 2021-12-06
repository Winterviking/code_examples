using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5thSaveMe
{
    public enum E_GRID_GENERATION_ALGORYTHM
    {
        RANDOM,
        UNIFORM,
        CHEBYSHEV
    }

    public class StandartGridGenerator : IGridGenerator1D<double>
    {
        public StandartGridGenerator(double from_, double to_)
        {
            from = from_;
            to = to_;
        }
        // TODO add from - to state control
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

        public double LastStep
        {
            get
            { return laststep; }
        }

        double laststep;
        double from, to;

        public double[] Generate(int number, E_GRID_GENERATION_ALGORYTHM algorythm = E_GRID_GENERATION_ALGORYTHM.UNIFORM)
        {
            double[] res = null;
            //if (function != null)
            //{
            if (number > 2)
            {
                if (from < to)
                {
                    res = new double[number];

                    double step = (to - from) / (number - 1);
                    laststep = step;
                    
                    // X GRID 
                    switch (algorythm)
                    {
                        case E_GRID_GENERATION_ALGORYTHM.UNIFORM: // uniform grid
                            {
                                res[0] = from;
                                for (int i = 1; i < number - 1; i++)
                                {
                                    res[i] = res[0] + i * step;
                                }
                                res[number - 1] = to;
                            }
                            break;
                        case E_GRID_GENERATION_ALGORYTHM.RANDOM:// trololo random grid
                            {//TODO:::: SORTING PLZ :D
                                Random rand = new Random();
                                res[0] = from;
                                for (int i = 1; i < number - 1; i++)
                                {
                                    res[i] = rand.NextDouble() * (to - from) + from;
                                }
                                res[number - 1] = to;
                            }
                            break;
                        case E_GRID_GENERATION_ALGORYTHM.CHEBYSHEV:// chebysheff grid
                            {
                                res[0] = from;
                                for (int i = 1; i < number - 1; i++)
                                {
                                    res[i] = (to + from) / 2 + (to - from) * System.Math.Cos((2 * (number - 1 - i) + 1) * System.Math.PI / (2 * (number))) / 2;
                                }
                                res[number - 1] = to;
                            }
                            break;
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
            return res;
        }

    }
}
