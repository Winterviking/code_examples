using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th
{
    class eigenvalue
    {
        public bool eigenProc(ref register reg_)
        {
            //init part
            reg = reg_;

            dfrom = -20;
            dto = 20;

            stepnum = 10000;
            dinterarray = new double[stepnum + 1];
            step = (dto - dfrom) / stepnum;

            gauss = new Gauss();
            interpolation.Lagrange lagrange = new interpolation.Lagrange();
            lagrange.init( ref reg );

            dihotomy = new roots.dihotomy();
            dihotomy.init(ref reg, dfrom, dto, ref lagrange);

//            System.Windows.Forms.MessageBox.Show(reg.ldmatrix[10, 10].ToString());

            //array of determinants in resdvector
//            createRandomGrid(); // ldvector
            createUniformGrid();
//            createChebysheffGrid();

            for (int i = 0; i < reg.darray_reg_one.Length; i++)
            {
                preparematrix(reg.darray_reg_one[i]);
                gauss.GaussDirectPass(ref reg, false);
                reg.darray_reg_two[i] = reg.resdvar;
//                System.Windows.Forms.MessageBox.Show(reg.ldmatrix[1, 0].ToString());
            }

            reg.mov_res_dv_rdv();

            //interpolation : to plot function if needed
            double walker = dfrom;
            for (int i = 0; i < dinterarray.Length; i++)
            {
                lagrange.InterpolatePoint(walker, ref dinterarray[i]);
                walker += step;
            }

            dihotomy.dihotomyProc( ref dinterarray, step );  

            return true;
        }

        public bool createRandomGrid()
        {
            Random rndm = new Random();
            for (int i = 0; i < reg.darray_reg_one.Length; i++)
			{
                // -10..10
                reg.darray_reg_one[i] = rndm.NextDouble()*(dto - dfrom) + dfrom;
			}
            
            return true;
        }

        public bool createUniformGrid()
        {
            double step = (dto - dfrom) / (reg.darray_reg_one.Length - 1);

            for (int i = 0; i < reg.darray_reg_one.Length; i++)
            {
                reg.darray_reg_one[i] = dfrom + i*step;
            }

            return true;
        }

        public bool createChebysheffGrid()
        {
            return true;
        }

        public bool preparematrix(double eigenvalue_)
        {
            reg.mov_l_dm_wl_dm();
            for (int i = 0; i < reg.sidelength; i++)
            {
                reg.wldmatrix[i, i] = reg.wldmatrix[i, i] - eigenvalue_;
//                System.Windows.Forms.MessageBox.Show(reg.wldmatrix[i, i].ToString());
            }
            return true;
        }
        roots.dihotomy dihotomy;
        register reg;

        Gauss gauss;
        

        double dfrom;
        double dto;
        int stepnum;
        double[] dinterarray;
        double step;
    }
}
