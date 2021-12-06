using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using _5thSaveMe.Math;

// TODO:: GET RID OF REGISTERS

namespace _5thSaveMe
{
    public interface IIOType<T>
    {
        T ConsoleInput();
        T FileInput(string filename_ = null);
        T VariableInput();

        void ConsoleOutput(T obj);
        void FileOutput(T obj);
        void VariableOutput(T obj);

        void SetParam(object data, int additionalData = 0);

        string Filename
        {
            set;
        }
    }

}
