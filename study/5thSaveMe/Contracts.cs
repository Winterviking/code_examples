using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5thSaveMe
{
    // all the function contracts

    public interface IAbstractFunction<A, F>
    {
        //        private F Operator(A argument);// what i would do with this lol
    }

    public delegate T DlgFunction<T>(T argument);

    public interface IFunction<T> : IAbstractFunction<T, T>
    {
        T Function(T argument);
    }

    public interface IInterpolator<T> : IAbstractFunction<T,T>
    {
        T InterpolatePoint(T argument);
    }

    abstract public class Interpolator<T> : IFunction<T>, IInterpolator<T>
    {
        // we are constructiong delegate
        public Interpolator()
        {
        }

        public T Function(T argument)
        {
            return InterpolatePoint(argument);
        }



        abstract public T InterpolatePoint(T argument);
    }

    // IFunction, IInterpolator

    public interface IGridGenerator1D<T> : IAbstractFunction<int, T[]>
    {
        T[] Generate(int number, E_GRID_GENERATION_ALGORYTHM algorythm = E_GRID_GENERATION_ALGORYTHM.UNIFORM );
        T From
        {
            get;
            set;
        }
        T To
        {
            get;
            set;
        }
        T LastStep
        {
            get;
        }
    }

    public interface IDataProcessor1D<T> : IAbstractFunction<T[], T[]>
    {
        T[] Process( T[] data );

        IFunction<T> Processor
        {
            set;
        }
    }
    // IGridGenerator

    //public interface IDataProvider<T> : IAbstractFunction<int, T[,]>
    //{
    //    T GetNumberOfData(int number);
    //}

    public interface IDataProcessor<T> : IAbstractFunction<object, T[,]>
    {
        T[,] Proc(object datasource);
    }

    public interface IDigitalSolver<T> : IAbstractFunction<T[,], T[,]>
    {
        T[,] Solve(T[,] points);
    }

    //public interface IMatrixNumericCharacteristic<T> : IAbstractFunction<T[,], T>
    //{
    //    T calculate(T[,] matrix, E_RELATION_OPERATOR_DATA keep = E_RELATION_OPERATOR_DATA.SAFETY);
    //}

    //public interface IParameters
    //{
    //    void SetParameter(object data, int additionalData = 0);
    //}

    //public interface IDataGetterSetter<T>
    //{
    //    T data
    //    {
    //        get;
    //        set;
    //    }
    //}

    public interface ISolver<T> : IAbstractFunction<IFunction<T>,List<T>>
    {
        T Solve(DlgFunction<T> equation, T from, T to, E_DIGITAL_SOLVE_METHOD method);
    }

    public interface ISLAESolver<T> : IAbstractFunction<SLAE<T>, T[]>
    {
        T[] Solve(SLAE<T> slae, E_SLAE_SOLVE_METHOD method = E_SLAE_SOLVE_METHOD.GAUSS, E_RELATION_OPERATOR_DATA safety = E_RELATION_OPERATOR_DATA.SAFETY);
    }

    public interface IIterativeProc<T> : IAbstractFunction<T, T>
    {
        T Iteration(T prev);
        T Proc(double epsilon, int maxnumber = 10000000);
    }

    public abstract class AVectorIterativeProc<T> : IIterativeProc<IVector<T>>
    {
        abstract public IVector<T> Iteration(IVector<T> prev);
        abstract public IVector<T> Proc(double epsilon, int maxnumber = 10000000);

        virtual public IMatrix<T> Operator
        {
            set
            { operator_ = value; }
        }
        protected IMatrix<T> operator_;
    }

    public interface IDigitalFunction<T> /*TODO:::: : IFunction<T>, IDataProvider<T>, IGridGenerator1D<T>*/
    {
        T From
        {
            get;
            set;
        }

        T To
        {
            get;
            set;
        }

        void Differentiate(int howManyTimes);
        List<T> FindRoots();
    }
}