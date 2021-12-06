using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace _5thSaveMe
{
    public interface ICalculator<T>
    {
        T Sum(T a, T b);
        T Difference(T a, T b);
        int Compare(T a, T b);
        T Multiply(T a, T b);
        T Divide(T a, T b);
        T Divide(T a, int b);
        bool compareToZero(T a);
        T negate(T a);
        T ConvertToNumber(double a);
        double getDoubleValue(T a);
    }

    struct DoubleCalculator : ICalculator<double>
    {
        public double Sum(double a, double b)
        {
            return a + b;
        }

        public double Difference(double a, double b)
        {
            return a - b;
        }

        public int Compare(double a, double b)
        {
            if (a > b)
            {
                return 1;
            }
            else if (a < b)
            {
                return -1;
            }
            else
            {
                return 0;
            }
        }

        public double Multiply(double a, double b)
        {
            return a * b;
        }

        public Double Divide(Double a, Double b)
        {
            return a / b;
        }

        public Double Divide(Double a, int b)
        {
            return a / b;
        }

        public bool compareToZero(double a)
        {
            return a == 0.0;
        }

        public double negate(double a)
        {
            return -a;
        }

        public double ConvertToNumber(double a)
        {
            return a;
        }

        public double getDoubleValue(double a)
        {
            return a;
        }
    }

    public class Number<T>
    {

        private T value;

        public Number(T value)
        {
            this.value = value;
        }

        public static Type GetCalculatorType()
        {
            Type tType = typeof(T);
            Type calculatorType = null;
            //if (tType == typeof(Int32))
            //{
            //    calculatorType = typeof(Int32Calculator);
            //}
            //else if (tType == typeof(Int64))
            //{
            //    calculatorType = typeof(Int64Calculator);
            //}
            /*else*/
            if (tType == typeof(Double))
            {
                calculatorType = typeof(DoubleCalculator);
            }
            //else if (tType == typeof(string))
            //{
            //    calculatorType = typeof(StringCalculator);
            //}
            else
            {
                throw new InvalidCastException(String.Format("Unsupported Type- Type {0} does not have a partner implementation of interface ICalculator<T> and cannot be used in generic arithmetic using type Number<T>", tType.Name));
            }
            return calculatorType;
        }

        private static ICalculator<T> fCalculator = null;

        public static ICalculator<T> Calculator
        {
            get
            {
                if (fCalculator == null)
                {
                    MakeCalculator();
                }
                return fCalculator;
            }
        }

        public static void MakeCalculator()
        {
            Type calculatorType = GetCalculatorType();
            fCalculator = Activator.CreateInstance(calculatorType) as ICalculator<T>;
        }

        // Operator Calls : text calls
        #region operation methods

        public static T Sum(T a, T b)
        {
            return Calculator.Sum(a, b);
        }

        public static T Difference(T a, T b)
        {
            return Calculator.Difference(a, b);
        }

        public static int Compare(T a, T b)
        {
            return Calculator.Compare(a, b);
        }

        public static T Multiply(T a, T b)
        {
            return Calculator.Multiply(a, b);
        }

        public static T Divide(T a, T b)
        {
            return Calculator.Divide(a, b);
        }

        public static T Divide(T a, int b)
        {
            return Calculator.Divide(a, b);
        }

        public static bool CompareToZero(T a)
        {
            return Calculator.compareToZero(a);
        }

        public static T negate(T a)
        {
            return Calculator.negate(a);
        }

        public static T ConvertToNumber(double a)
        {
            return Calculator.ConvertToNumber(a);
        }

        public static double getDoubleValue(T a)
        {
            return Calculator.getDoubleValue(a);
        }


        #endregion

        // WRAPPING for easy usage + - * / new ()
        #region Operators

        public static implicit operator Number<T>(T a)
        {
            return new Number<T>(a);
        }

        public static implicit operator T(Number<T> a)
        {
            return a.value;
        }

        public static Number<T> operator +(Number<T> a, Number<T> b)
        {
            return Calculator.Sum(a.value, b.value);
        }

        public static Number<T> operator -(Number<T> a, Number<T> b)
        {
            return Calculator.Difference(a, b);
        }

        public static bool operator >(Number<T> a, Number<T> b)
        {
            return Calculator.Compare(a, b) > 0;
        }

        public static bool operator <(Number<T> a, Number<T> b)
        {
            return Calculator.Compare(a, b) < 0;
        }

        public static Number<T> operator *(Number<T> a, Number<T> b)
        {
            return Calculator.Multiply(a, b);
        }

        public static Number<T> operator /(Number<T> a, Number<T> b)
        {
            return Calculator.Divide(a, b);
        }

        public static Number<T> operator /(Number<T> a, int b)
        {
            return Calculator.Divide(a, b);
        }
        #endregion
    }
}