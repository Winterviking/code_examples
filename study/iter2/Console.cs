using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _5th2nd
{
    public interface IConsole
    {
        void Log( string phrase );
        string GetInput();

        //public bool busy
        //{
        //    get;
        //    set;
        //}
    }

    class BasicConsole : IConsole
    {
        public void Log( string phrase )
        {
            output.AppendText(phrase);
        }

        public string GetInput()
        {
            return input.Text;
        }

        RichTextBox output;
        TextBox input;
    }
}
