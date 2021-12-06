using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th_just_prog
{
    // Simplest Universal Function interface
    public interface IFunction<A, F>
    {
        F GetValueOfFunction(A argument);
        void SetParameter(object data, int additionalData = 0);
    }
}
