using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th_just_prog
{
    // all the function contracts

    interface IAbstractFunction<A,F>
    {
//        private F Operator(A argument);// what i would do with this lol
    }

    interface IFunction<T> : IAbstractFunction<T, T>
    {
        public T Function(T argument);
    }

    interface IDataProvider<T> : IAbstractFunction<int, T[,]>
    {
        public T GetNumberOfData(int number);
    }

    interface IDataProcessor<T> : IAbstractFunction<object, T[,]>
    {
        public T[,] Proc(object datasource);
    }

    interface IDigitalSolver<T> : IAbstractFunction<T[,], T[,]>
    {
        public T[,] Solve(T[,] points);
    }

    interface IMatrixNumericCharacteristic<T> : IAbstractFunction<T[,], T>
    { 
        T calculate ( T[,] matrix, E_RELATION_OPERATOR_DATA keep = E_RELATION_OPERATOR_DATA.SAFETY );
    } 
    
    interface IParameters
    {
        void SetParameter(object data, int additionalData = 0);
    }

    interface IDataGetterSetter<T>
    {
        T data
        {
            get;
            set;
        }
    }


}
