using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5thSaveMe
{
    public enum E_SLAE_SOLVE_METHOD
    { 
        GAUSS
    }

    // IS COMPLETELY SAFE
    public class StandartSLAESolver : ISLAESolver<double>
    {
        public double[] Solve(SLAE<double> slae, E_SLAE_SOLVE_METHOD method = E_SLAE_SOLVE_METHOD.GAUSS, E_RELATION_OPERATOR_DATA safety = E_RELATION_OPERATOR_DATA.SAFETY)
        {
            int num = slae.rightColumn.Value.Length;
            double[] res = null;
            //new double[num];

            if (method == E_SLAE_SOLVE_METHOD.GAUSS)
            {
                IMatrix<double> wmatrix = null;
                IVector<double> wrightc = null;
                if (safety == E_RELATION_OPERATOR_DATA.SAFETY)
                {
                    wmatrix = slae.coefficients.Clone();
                    wrightc = slae.rightColumn.Clone();
                }
                else if (safety == E_RELATION_OPERATOR_DATA.CORRUPTION)
                {
                    wmatrix = slae.coefficients;
                    wrightc = slae.rightColumn;
                }
                
                double scoeff_g, dcoeff_g;

                bool good;

                for (int i = 0; i < num - 1; i++)
			    {
                    good = false;
                    if (wmatrix[i, i] == 0)
                    {
                        for (int j = i; j < num; j++)
                        {
                            if (wmatrix[j, i] != 0)
                            {
                                for (int l = i; l < num; l++)
                                {
                                    wmatrix[i, l] += wmatrix[j, l];
                                }
                                good = true;
                                break;
                            }
                        }
                    }
                    else
                    {
                        good = true;
                    }

                    if (!good)
                    {
                        wmatrix[i, i] = 0.000000000000001;
                    }
                    scoeff_g = wmatrix[i, i];


                    for ( int j = i + 1; j < num; j++)
                    {
                        dcoeff_g = wmatrix[j,i];
                        for (int k = 0; k < num; k++)
			            {
			                wmatrix[j,k] = wmatrix[j,k] - wmatrix[i,k] * dcoeff_g / scoeff_g;
			            }
                        wrightc[j] = wrightc[j] - wrightc[i] * dcoeff_g / scoeff_g;
                    }
			    }

                // optional : maybe use:) as on-demand - data :)
                double determinant = 1;
                for (int i = 0; i < num; i++)
			    {
			        determinant *= wmatrix[i,i];
			    }

                for (int i = num - 1; i >= 0; i--)
			    {
			        for (int j = i+1; j < num; j++)
			        {
			            wrightc[i] -= wmatrix[i,j];
                        wmatrix[i,j] = 0;
			        }
                    wrightc[i] /= wmatrix[i,i];
                    wmatrix[i,i] = 1;
                    for (int j = i-1; j >= 0; j--)
			        {
			            wmatrix[j,i] *= wrightc[i];
			        }
			    }

                res = wrightc.Value;
            }

            return res;
        }
    }
}
