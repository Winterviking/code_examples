using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th
{
    class register
    {
        // plots
        public List<double> x;
        public List<double> y;

        // service
        public int sidelength;

        // registers
        public double[,] ldmatrix;
        public double[,] rdmatrix;
        public double[,] wldmatrix;
        public double[,] wrdmatrix;
        public double[,] resdmatrix;
        public double[,] dmatrixin;

        public double[] ldvector;
        public double[] rdvector;
        public double[] wldvector;
        public double[] wrdvector;
        public double[] resdvector;
        public double[] dvectorin;

        public double ldvar;
        public double rdvar;
        public double wldvar;
        public double wrdvar;
        public double resdvar;

        // service reg
        public double[] darray_reg_one;
        public double[] darray_reg_two;
//        public double[] darray_reg_three;

        void setupServiceArray(int id, int length)
        {
            switch (id)
            {
                case 1:
                {
                    darray_reg_one = new double[length];
                }
                break;
                case 2:
                {
                    darray_reg_two = new double[length];
                }
                break;
            }
        }


        public void resetPlots()
        {
            x.Clear();
            y.Clear();
        }

        public void resetRegisters()
        {
            for (int i = 0; i < sidelength; i++)
            {
                ldvector[i] = 0.0;
                wldvector[i] = 0.0;
                rdvector[i] = 0.0;
                wrdvector[i] = 0.0;
                resdvector[i] = 0.0;

                for (int j = 0; j < sidelength; j++)
                {
                    ldmatrix[i, j] = 0.0;
                    wldmatrix[i, j] = 0.0;
                    rdmatrix[i, j] = 0.0;
                    wrdmatrix[i, j] = 0.0;
                    resdmatrix[i, j] = 0.0;
                }
            }

            ldvar = 0.0;
            rdvar = 0.0;
            wldvar = 0.0;
            wrdvar = 0.0;
            resdvar = 0.0;            
        }

        public void resetWorkingRegisters()
        {
            for (int i = 0; i < sidelength; i++)
            {
                wldvector[i] = 0.0;
                wrdvector[i] = 0.0;

                for (int j = 0; j < sidelength; j++)
                {
                    wldmatrix[i, j] = 0.0;
                    wrdmatrix[i, j] = 0.0;
                }
            }

            wldvar = 0.0;
            wrdvar = 0.0;
        }

        public void reinit_registers()
        {
            ldmatrix = null;
            wldmatrix = null;
            rdmatrix = null;
            wrdmatrix = null;
            resdmatrix = null;
            dmatrixin = null;

            ldvector = null;
            wldvector = null;
            rdvector = null;
            wrdvector = null;
            resdvector = null;
            dvectorin = null;

            ldmatrix = new double[sidelength, sidelength];
            wldmatrix = new double[sidelength, sidelength];
            rdmatrix = new double[sidelength, sidelength];
            wrdmatrix = new double[sidelength, sidelength];
            resdmatrix = new double[sidelength, sidelength];
            dmatrixin = new double[sidelength, sidelength];

            ldvector = new double[sidelength];
            wldvector = new double[sidelength];
            rdvector = new double[sidelength];
            wrdvector = new double[sidelength];
            resdvector = new double[sidelength];
            dvectorin = new double[sidelength];

            resetRegisters();

            x = new List<double>();
            y = new List<double>();
        }
       
        public bool mov_l_dm_wl_dm()
        {
            return mov( ref ldmatrix, ref wldmatrix);
        }

        public bool mov_res_dv_ldv()
        {
            return mov(ref resdvector, ref ldvector);
        }

        public bool mov_res_dv_rdv()
        {
            return mov(ref resdvector, ref rdvector);
        }

        public bool mov(ref double[] from, ref double[] to)
        {
            for (int i = 0; i < sidelength; i++)
            {
                to[i] = from[i];
            }
            return true;        
        }
       
        public bool mov(ref double[,] from, ref double[,] to)
        {
            for (int i = 0; i < sidelength; i++)
            {
                for (int j = 0; j < sidelength; j++)
                {
                    to[i, j] = from[i, j];
                }
            }
            return true;
        }
    }
}
