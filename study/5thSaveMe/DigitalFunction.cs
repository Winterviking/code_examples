using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5thSaveMe
{
    // TODO :: add state bool variables : changed ( means that we generate stuff only for already made x_ and y_ so we gotta erase em if we change function table )
    // TODO :: more constructiors for every possible sources of this digital function
    //              fields to change it for example

    class DigitalFunction : IDigitalFunction<double>
    {
        // creates digital function by table
        public DigitalFunction( double [] x, double [] y )
        { 
            // TODO:: tests:)
            x_ = x;
            y_ = y;
            number_ = x.Length;
            from_ = x[0];
            to_ = x[x.Length - 1];
        }

        // creates digital function from normal one
        public DigitalFunction( IFunction<double> func, double from, double to, int number, IGridGenerator1D<double> externalGridGenerator = null, ISolver<double> externalSolver = null )
        {
            if ( externalGridGenerator == null )
            {
                gg = new StandartGridGenerator(from, to);
            }
            else
            {
                gg = externalGridGenerator;
                gg.From = from;
                gg.To = to;
            }

            if (externalSolver != null)
            {
                default_solver = externalSolver;
            }

            dp = new FunctionDataProcessor(func);

            number_ = number;
            function_ = func.Function;

            generate();
        }

        public double From
        {
            get
            { return from_; }
            set
            { from_ = value; }
        }

        public double To
        {
            get
            { return to_; }
            set
            { to_ = value; }
        }

        public List<double[]> Derivatives
        {
            get
            { return derivatives_; }
        }

        public void Differentiate(int howManyTimes)
        {
            if ( howManyTimes > derivatives_.Count )
            {
                double[] prev_y, next_y;
                if (derivatives_.Count == 0)
                {
                    prev_y = y_;
                }
                else
                {
                    prev_y = derivatives_.Last();
                }

                double step = 1;
                if (gg != null)
                {
                    step = gg.LastStep;
                }
                else
                {
                    // TODO:: if grid is not uniform
                }

                // howmanytimes = 2 calculates 2 consequent derivatives :)
                for ( int k = derivatives_.Count; k < howManyTimes; k++ )
                {
                    next_y = new double[prev_y.Length];

                    // RIGHT SIDED
                    next_y[0] = (prev_y[1] - prev_y[0]) / step;
                    // CENTRAL
                    next_y[1] = (prev_y[2] - prev_y[0]) / (2 * step);
                    // 5 POINT INTERPOLATION
                    for (int i = 2; i < number_ - 2; i++)
                    {
                        next_y[i] = (prev_y[i - 2] - 8 * prev_y[i - 1] + 8 * y_[i + 1] - y_[i + 2]) / (12 * step);
                    }
                    // CENTRAL
                    next_y[number_ - 2] = (prev_y[number_ - 1] - prev_y[number_ - 3]) / (2 * step);
                    // LEFT-SIDED
                    next_y[number_ - 1] = (prev_y[number_ - 1] - prev_y[number_ - 2]) / step;

                    derivatives_.Add(next_y);
                    prev_y = next_y;
                }
            }
        }

        public List<double> FindRoots()
        {
            // if we have no solver
            if (default_solver == null)
            {
                default_solver = new Solver();
            }

            if (derivatives_.Count < 2)
            {
                Differentiate(2);
            }

            int start_period = 0;
            int end_period = 0;
            bool period_state = false;

            for (int i = 1; i < number_ - 1; i++)
            {
                if ( y_[i] == 0.0 )
                {
                    roots.Add(x_[i]);
                }
                else if ( y_[i - 1]*y_[i] < 0 )
                {
                    // Dihotomy
                    roots.Add( default_solver.Solve(function_, x_[i - 1], x_[i], E_DIGITAL_SOLVE_METHOD.DIHOTOMY));
                }
                else if ((System.Math.Abs(derivatives_[0][i]) < 0.0000001) && (System.Math.Abs(derivatives_[1][i]) > 0.00000001))
                {
                    if (System.Math.Abs(y_[i]) < 0.000001 && !period_state)
                    {
                        start_period = i;
                        period_state = true;
                    }
                    else if ( period_state )
                    {
                        end_period = i;
                        period_state = false;
                        roots.Add(x_[start_period] + (x_[start_period] - x_[end_period]) / 2);
                    }
                }
                else if (period_state)
                {
                    if ( System.Math.Abs(y_[i]) > 0.000001)
                    {
                        end_period = i;
                        period_state = false;
                        roots.Add(x_[start_period] + (x_[start_period] - x_[end_period]) / 2);
                    }
                }
            }
            return roots;
        }

        // generating function using delegat ( INTERNAL )
        void generate ()
        {
            x_ = gg.Generate(number_);
            y_ = dp.Process(x_);
        }

        // 2d grid generator [    ] ---> array ---> processed array
        IGridGenerator1D<double> gg;
        IDataProcessor1D<double> dp;

        // keep for data generated on demand
        // array of y', y'', y''' ...
        List<double[]> derivatives_ = new List<double[]>();
        List<double> roots = new List<double>();

        // utility classes
        ISolver<double> default_solver = null;

        // utility data
        double from_;
        double to_;

        double[] x_;
        double[] y_;

        // dlg function probably can be used
        DlgFunction<double> function_ = null;

        int number_;
    }
}
