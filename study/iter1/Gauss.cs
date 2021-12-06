using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th
{
    class Gauss
    {
        public bool GaussDirectPass(ref register reg, bool leftsideonly)
        {
            //DIRECTPASS
            double coeff;
            for (int i = 0; i < reg.sidelength - 1; i++)
            {
                for (int j = i + 1; j < reg.sidelength; j++)
                {
                    coeff = reg.wldmatrix[j, i] / reg.wldmatrix[i, i];
                    for (int k = j; k < reg.sidelength; k++)
                    {
                        reg.wldmatrix[j, k] = reg.wldmatrix[j, k] - coeff * reg.wldmatrix[i, k];
                    }
                    reg.wldmatrix[j, i] = 0;
                }
            } // LEAVE IT IN WORKING REGISTER

            //DETERMINANT
            reg.resdvar = 1;
            for (int i = 0; i < reg.sidelength; i++)
            {
                reg.resdvar *= reg.wldmatrix[i, i]; // DETERMINANT IS A RESULT
            } 
            return true;
        }

        public bool GaussReversePass(ref register reg, bool leftsideonly)
        {
            return true;
        }

        public bool GaussProc ( ref register reg, bool leftsideonly ) // TODO:MAKE IT WITH RIGHT COLUMN IF NEEDED
        {
            GaussDirectPass(ref reg, leftsideonly);
            GaussReversePass(ref reg, leftsideonly);

            return true;
        }
    }
}
