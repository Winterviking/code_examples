using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace _5th
{
    class Console
    {
        public void Initialize(ref System.Windows.Forms.RichTextBox consoleWindow_)
        {
            consoleWindow = consoleWindow_;
        }

        public System.Windows.Forms.RichTextBox consoleWindow;
    }
}
