using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace _5th_just_prog
{
    //public static class Calculator
    //{
    //    public static T Sum<T>(T a, T b)
    //    {
    //        return Number<T>.Sum(a, b);
    //    }
    //}

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

/*
    struct Int32Calculator : ICalculator<Int32>
    {
        public Int32 Sum(Int32 a, Int32 b)
        {
            return a + b;
        }

        public Int32 Difference(Int32 a, Int32 b)
        {
            return a - b;
        }

        public int Compare(Int32 a, Int32 b)
        {
            return Difference(a, b);
        }

        public int Multiply(Int32 a, Int32 b)
        {
            return a * b;
        }

        public int Divide(Int32 a, Int32 b)
        {
            return a / b;
        }

    }
*/

/*
    struct Int64Calculator : ICalculator<Int64>
    {
        public Int64 Sum(Int64 a, Int64 b)
        {
            return a + b;
        }

        public Int64 Difference(Int64 a, Int64 b)
        {
            return a - b;
        }

        public int Compare(Int64 a, Int64 b)
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

        public Int64 Multiply(Int64 a, Int64 b)
        {
            return a * b;
        }

        public Int64 Divide(Int64 a, Int64 b)
        {
            return a / b;
        }

        public Int64 Divide(Int64 a, int b)
        {
            return a / b;
        }
    }
*/

/*
    struct SingleCalculator : ICalculator<Single>
    {
        public Single Sum(Single a, Single b)
        {
            return a + b;
        }

        public Single Difference(Single a, Single b)
        {
            return a - b;
        }

        public int Compare(Single a, Single b)
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

        public Single Multiply(Single a, Single b)
        {
            return a * b;
        }

        public Single Divide(Single a, Single b)
        {
            return a / b;
        }

        public Single Divide(Single a, int b)
        {
            return a / b;
        }
    }
*/

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

/*
    struct StringCalculator : ICalculator<string>
    {
        public string Sum(string a, string b)
        {
            return a + b;
        }

        public string Difference(string a, string b)
        {
            if (b.Length < a.Length)
            {
                return a.Substring(0, b.Length);
            }
            else
            {
                return "";
            }
        }

        public int Compare(string a, string b)
        {
            return a.CompareTo(b);
        }

        public string Multiply(string a, string b)
        {
            if (a.Length == 1 && b.Length == 1)
            {
                return ((char)(((byte)a[0] * (byte)b[0]) % 256)) + "";
            }

            int bigLength = Math.Max(a.Length, b.Length);
            while (a.Length < bigLength)
            {
                a = " " + a;
            }
            while (b.Length < bigLength)
            {
                b = " " + b;
            }

            string result = "";
            for (int i = 0; i < bigLength; i++)
            {
                Number<string> numA = a[i] + "";
                Number<string> numB = b[i] + "";
                result += numA * numB;
            }

            return result;
        }

        public String Divide(String a, String b)
        {
            return String.Format("{0} / {1}", a, b);
        }

        public String Divide(String a, int b)
        {
            return String.Format("{0} / {1}", a, b);
        }


    }
*/


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
            /*else*/ if (tType == typeof(Double))
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

        public static bool CompareToZero( T a )
        {
            return Calculator.compareToZero( a );
        }

        public static T negate(T a)
        {
            return Calculator.negate( a );
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

    /*
                Random random = new Random(DateTime.Now.Millisecond);

                SummableListU<int> list = new SummableListU<int>();

                for (int i = 0; i < (int)numericUpDown1.Value; i++) {
                    list.Add(random.Next(1000));
                }

                DateTime startTime = DateTime.Now;
                int sum = list.Sum();
                int average = list.Average();
                DateTime endTime = DateTime.Now;

                TimeSpan difference = endTime - startTime;

                CalcUtilTextBox.Text = string.Format("{0:0.00}", difference.TotalMilliseconds);
     * 
     * 
     * 
     class SummableList<T> : List<T> {

        public T Sum() {
            Number<T> result = default(T);

            foreach (T item in this)
                result += item;

            return result;
        }

        public T Average() {
            Number<T> sum = Sum();
            return sum / Count;
        }
    }
     */





}