using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace _5thSaveMe
{
    class SystemIO
    {
        static public string[] OpenFile(string filename)
        {
            return System.IO.File.ReadAllLines(filename);
        }

        static public void CloseFile()
        {
            // stub
        }

        static public void Log(string line)
        {
            if (console != null)
                console.Log(line + "\n");
        }

        // necessary before using
        static public void initDefaultConsole(RichTextBox dumpwindow)
        {
            console = new OutputConsole(dumpwindow);
        }

        static IConsole console = null;
    }

    public interface IConsole
    {
        void Log(string phrase);
        string GetInput();

        //public bool busy
        //{
        //    get;
        //    set;
        //}
    }

    class BasicConsole : IConsole
    {
        public BasicConsole(RichTextBox output_, TextBox input_)
        {
            output = output_;
            input = input_;
        }

        public void Log(string phrase)
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

    class OutputConsole : IConsole
    {
        public OutputConsole(RichTextBox output_)
        {
            output = output_;
        }

        public void Log(string phrase)
        {
            output.AppendText(phrase);
        }

        public string GetInput()
        {
            return "";
        }

        RichTextBox output;
    }
}
