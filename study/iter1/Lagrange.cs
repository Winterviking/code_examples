using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th
{
namespace interpolation
{
    class Lagrange
    {
        register reg;
        //        public int number;
        public void init(ref register reg_)
        {
            reg = reg_;
            //            number = number_;
        }
        //        double[] array_x;
        //        double[] array_y;
        //      services ser;

        //        public Lagrange()
        //        {
        //            ser = new services();
        //        }


        /*        public void generateNetwork(int method_, int number_)
                {
                    array_x = null;
                    array_y = null;
                    number = number_;
                    array_x = new double[number];
                    array_y = new double[number];

                    double step = (services.x_max - services.x_min)/(number - 1);

                    switch (method_)
                    {
                        case 1: // uniform grid
                        {
                            array_x[0] = services.x_min;
                            for (int i = 1; i < number - 1; i++)
                            {
                                array_x[i] = array_x[0] + i * step;
                            }
                            array_x[number - 1] = services.x_max;
                        }
                        break;
                        case 2:// trololo random grid
                        {
                            Random rand = new Random();
                            array_x[0] = services.x_min;
                            for (int i = 1; i < number - 1; i++)
                            {
                                array_x[i] = rand.NextDouble()*(services.x_max-services.x_min) + services.x_min;
                            }
                            array_x[number - 1] = services.x_max;
                        }
                        break;
                        case 3:// chebysheff grid
                        {
                            array_x[0] = services.x_min;
                            for (int i = 1; i < number - 1; i++)
                            {
                                array_x[i] = (services.x_max + services.x_min) / 2 + (services.x_max - services.x_min) * Math.Cos((2 * i + 1) * Math.PI / (2 * (number))) / 2;
                            }
                            array_x[number - 1] = services.x_max;
                        }
                        break;
                        default:
                            return;
                    };

                    for (int i = 0; i < number; i++)
                    {
                        array_y[i] = ser.functia(array_x[i]);
                    }
                }
            */

        public double InterpolatePoint(double x, ref double y)
        {
            double buff;
            y = 0;
            for (int i = 0; i < reg.darray_reg_one.Length; i++)
            {
                buff = 1.0;
                for (int k = 0; k < reg.darray_reg_one.Length; k++)
                {
                    if (k != i)
                    {
                        buff *= (x - reg.darray_reg_one[k]) / (reg.darray_reg_one[i] - reg.darray_reg_one[k]);
                    }
                }
                y += buff * reg.darray_reg_two[i];
            }
            return y;
        }

        /*        public double get_gridpoint_x(int i)
                {
                    return array_x[i];
                }
                public double get_gridpoint_y(int i)
                {
                    return array_y[i];
                }*/

    }
}
}