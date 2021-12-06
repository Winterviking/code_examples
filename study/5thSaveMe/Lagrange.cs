using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5thSaveMe
{
    class Lagrange : Interpolator<double>
    {
        public Lagrange ( double from_, double to_, int number_, IFunction<double> function_, IGridGenerator1D<double> externalGridGenerator = null )
        {
            if (externalGridGenerator == null)
            {
                gg = new StandartGridGenerator(from_, to_);
            }
            else
            {
                gg = externalGridGenerator;
            }

            x = gg.Generate(number_, E_GRID_GENERATION_ALGORYTHM.CHEBYSHEV);
            y = new double[number_];
            function = function_;
            number = number_;

            for (int i = 0; i < number; i++)
            {
                y[i] = function_.Function(x[i]);
            }


            //TODO:::: optimize plz
            //polinomz' TRUE COEFFS!!!!!
            double[] roots = new double[number_ - 1];// helper
            double[] coeffs_ = new double[number_];

            trueCoeffs = new double[number_];

            double scalecoeff = default(double);
            for (int k = 0; k < number_; k++)// polinoms
            {
                // k polynom roots  
                for (int i = 0; i < k; i++)
                    roots[i] = x[i];
                for (int i = k + 1; i < number_; i++)
                    roots[i - 1] = x[i];

                // scale coeff for every polynom
                scalecoeff = y[k];

                for (int i = 0; i < roots.Length; i++)
                {
                    scalecoeff *= 1 / (x[k] - roots[i]);
                }

                // COEFFS a0=1; a(k,i) = a(k-1,i) - a(k,i-1)*x(k) k:power; i:coeff number;
                coeffs_[0] = 1;
                for (int i = 2; i <= coeffs_.Length; i++)
                {
                    for (int j = 1; j < i; j++)
                    {
                        coeffs_[j] = coeffs_[j] - coeffs_[j - 1] * roots[j - 1];
                    }
                }
                
                for (int i = 0; i < coeffs_.Length; i++)
                {
                    trueCoeffs[i] += scalecoeff * coeffs_[i];
                }
            }
            SystemIO.Log("EAT IT :::: COEFFS ::::");
            for (int i = 0; i < number_; i++)
            {
                SystemIO.Log(trueCoeffs[i].ToString());
            }
        }

        public override double InterpolatePoint(double argument)
        {
            double res = 0;

            double buff;
            for (int i = 0; i < number; i++)
            {
                buff = 1.0;
                for (int k = 0; k < number; k++)
                {
                    if (k != i)
                    {
                        buff *= (argument - x[k]) / (x[i] - x[k]);
                    }
                }
                res += buff * y[i];
            }

            return res;
        }

        IGridGenerator1D<double> gg;
        IFunction<double> function;

        double[] trueCoeffs;

        int number;

        double[] x;
        double[] y;
    }
}
