using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5thSaveMe
{
    public class DVector : IVector<double>
    {
        public DVector()
        { }
        public DVector(double[] initvalue)
        {
            Value = initvalue;
        }

        public DVector(IVector<double> toclone)
        {
            // Full true copying
            double[] res;

            Math.ArrayOpsWrapper<double>.arrayOperations.truecopyvector(toclone.Value, out res);
            this.vector = res;
        }

        public double[] Value
        {
            get
            {
                return vector;
            }
            set
            {
                vector = value;
            }
        }

        public double this[int x]
        {
            get { return vector[x]; }
            set { vector[x] = value; }
        }

        public void minus(ref IVector<double> operand2, ref IVector<double> res)
        {
            for (int i = 0; i < vector.Length; i++)
            {
                res[i] = vector[i] - operand2[i];
            }
        }

        public IVector<double> Clone()
        {
            return new DVector(this);
        }

        public double norm()
        {
            return Math.ArrayOpsWrapper<double>.arrayOperations.vectorNorm(vector);
        }



        double[] vector;
    }
}
