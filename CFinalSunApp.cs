using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FinalRelert2
{
    class CFinalSunApp
    {
        public static CFinalSunApp Instance = new CFinalSunApp();
        public string ExePath { get; private set; }
        public string MapPath { get; private set; }
        public string FilePath { get; private set; }
        public CFinalSunDlg MainDialog { get; private set; }

        public CFinalSunApp()
        {
            this.ExePath = Environment.CurrentDirectory;
            this.MapPath = string.Empty;
            this.FilePath = string.Empty;
        }

        public void Run()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            this.MainDialog = new CFinalSunDlg();
            Application.Run(MainDialog);
        }
    }
}
