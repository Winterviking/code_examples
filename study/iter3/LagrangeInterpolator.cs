using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th_just_prog
{
    class LagrangeInterpolator : IFunction<double,double>
    {
        public LagrangeInterpolator()
        { 
        
        }

        //public LagrangeInterpolator(int number)
        //{
        //    SetParameter(number, 10);// set grid
        //}

        public double GetValueOfFunction(double argument)
        {
            double res = 0;
            if (interpolationPoints != null)
            {
                double buff;
                for (int i = 0; i <= interpolationPoints.GetUpperBound(0); i++)
                {
                    buff = 1.0;
                    for (int k = 0; k <= interpolationPoints.GetUpperBound(0); k++)
                    {
                        if (k != i)
                        {
                            buff *= (argument - interpolationPoints[k,0]) / (interpolationPoints[i,0] - interpolationPoints[k,0]);
                        }
                    }
                    res += buff * interpolationPoints[i,1];
                }
            }
            else
            {
                SystemIO.Log("Error:: no interpolation points specified");
            }
            return res;
        }
        public void SetParameter(object data, int additionalData = 0)
        {
            if (custom_grid_generator)
                { customGridGenerator.SetParameter(data, additionalData); }
            gridGenerator.SetParameter(data, additionalData);
            if (typeof(bool) == data.GetType())
            {
                custom_grid_generator = (bool)data;
            }
            else if (typeof(IDataProvider<double>) == data.GetType() || additionalData == 100)
            { 
                customGridGenerator = (IDataProvider<double>)data;
                if ( additionalData == 0 )
                    { custom_grid_generator = false; }
                else
                    { custom_grid_generator = true; }
            }
            else if ( ( typeof(int) == data.GetType() ) && ( additionalData == 10 ) )//number
            {
                if ((int)data > 2)
                {
                    if (interpolationPoints != null)
                    {
                        if ((interpolationPoints.GetUpperBound(0) + 1) != (int)data)
                        {
                            generateGrid( (int)data );
                        }
                    }
                    else
                    {
                        generateGrid( (int)data );
                    }
                }
            }
        }

        private void generateGrid ( int number )
        {
            interpolationPoints = null;
            if (custom_grid_generator)
                { interpolationPoints = customGridGenerator.getAllPoints(number); }
            else
                { interpolationPoints = gridGenerator.getAllPoints(number); }
        }

        bool custom_grid_generator = false;

        private double[,] interpolationPoints = null;
        private InterpolationGridProvider gridGenerator = new InterpolationGridProvider();
        private IDataProvider<double> customGridGenerator = null;
    }
}


