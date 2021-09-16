using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace FinalRelert2
{
    public partial class CFinalSunDlg : Form
    {
        public static CFinalSunDlg Instance
        {
            get
            {
                return CFinalSunApp.Instance.MainDialog;
            }
        }

        public CFinalSunDlg()
        {
            InitializeComponent();

        }
    }
}
