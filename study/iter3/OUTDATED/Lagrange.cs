/*

//#define SAD_DEBUG

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

// OUTDATED

namespace _5th_just_prog
{
    class Lagrange : DataSource
    {
        E_GRID_TYPE gridType = E_GRID_TYPE.UNIFORM;
        public int number;

        public double ifrom
        {
            get
            { return from_; }
            set
            { from_ = value; }
        }
        public double ito
        {
            get
            { return to_; }
            set
            { to_ = value; }
        }

        private double from_ = 0;
        private double to_ = 0;

        public Function function
        {
            set
            {
                function_ = value;
            }
        }
        private Function function_;

        public double[] Array_x
        {
            get
            { return array_x; }
        }
        public double[] Array_y
        {
            get
            { return array_y; }
        }
        private double[] array_x = null;
        private double[] array_y = null;

        //private double[] def_interpolation_points_x = null;
        //private double[] def_interpolation_points_y = null;
        public double[] def_interpolation_points_x = null;
        public double[] def_interpolation_points_y = null;

        public void setParam( object data, int additionalData = 0)
        {
            if ( data.GetType() == typeof(int) || additionalData == 1 )
            {
                number = (int)data;
                if ( number >= 2 )
                {
                    generateGrid(gridType);
                }
            }
            else if ( data.GetType() == typeof( E_GRID_TYPE ) )
            {
                gridType = (E_GRID_TYPE)data;
            }
        }


        public void generateGrid( E_GRID_TYPE method_ )
        {
            if ( ( number > 2 ) && ( from_ < to_ ) )
            {
                def_interpolation_points_x = null;
                def_interpolation_points_y = null;
                def_interpolation_points_x = new double[number];
                def_interpolation_points_y = new double[number];

                double step = (to_ - from_) / (number - 1);

                // X GRID
                switch (method_)
                {
                    case E_GRID_TYPE.UNIFORM: // uniform grid
                        {
                            def_interpolation_points_x[0] = from_;
                            for (int i = 1; i < number - 1; i++)
                            {
                                def_interpolation_points_x[i] = def_interpolation_points_x[0] + i * step;
                            }
                            def_interpolation_points_x[number - 1] = to_;
                        }
                        break;
                    case E_GRID_TYPE.RANDOM:// trololo random grid
                        {
                            Random rand = new Random();
                            def_interpolation_points_x[0] = from_;
                            for (int i = 1; i < number - 1; i++)
                            {
                                def_interpolation_points_x[i] = rand.NextDouble() * (to_ - from_) + from_;
                            }
                            def_interpolation_points_x[number - 1] = to_;
                        }
                        break;
                    case E_GRID_TYPE.CHEBYSHEV:// chebysheff grid
                        {
                            def_interpolation_points_x[0] = from_;
                            for (int i = 1; i < number - 1; i++)
                            {
                                def_interpolation_points_x[i] = (to_ + from_) / 2 + (to_ - from_) * Math.Cos((2 * ( number - 1 - i) + 1) * Math.PI / (2 * (number))) / 2;
                            }
                            def_interpolation_points_x[number - 1] = to_;
                        }
                        break;
                    default:
                        return;
                }

                // Y GRID
                for (int i = 0; i < number; i++)
			    {
			        function_.getYbyX(def_interpolation_points_x[i], out def_interpolation_points_y[i]);
			    }
            }

            // DEBUG!!!!!
#if SAD_DEBUG
            for (int i = 0; i < number; i++)
            {
                SystemIO.Log(def_interpolation_points_x[i].ToString() + " " + def_interpolation_points_y[i].ToString());
            }
#endif
        }

        public void generatePoint(double x_, out double y_)
        {
            double buff;
            y_ = 0;
            for (int i = 0; i < number; i++)
            {
                buff = 1.0;
                for (int k = 0; k < number; k++)
                {
                    if (k != i)
                    {
                        buff *= (x_ - def_interpolation_points_x[k]) / (def_interpolation_points_x[i] - def_interpolation_points_x[k]);
                    }
                }
                y_ += buff * def_interpolation_points_y[i];
            }
        }

        public void generateAllPoints(int amount)
        {
            array_x = new double[amount];
            array_y = new double[amount];

            double step = ( to_ - from_ ) / ( amount - 1);

            for (int i = 0; i < amount; i++)
            {
                array_x[i] = from_ + i * step;
                generatePoint(array_x[i], out array_y[i]);
            }
        }
    }
}
*/