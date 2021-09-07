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
        static public CFinalSunApp Instance = new CFinalSunApp();

        public CFinalSunApp()
        {
            ExePath = Environment.CurrentDirectory;
            MapPath = string.Empty;
            FilePath = string.Empty;
            MainDialog = new CFinalSunDlg();
        }

        public void Run()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(MainDialog);
        }

        public string ExePath;
        public string MapPath;
        public string FilePath;
        public CFinalSunDlg MainDialog;

    }
}
