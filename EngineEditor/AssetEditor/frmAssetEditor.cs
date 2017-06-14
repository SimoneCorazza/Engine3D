using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace EngineEditor
{
    public partial class frmAssetEditor : Form
    {
        public frmAssetEditor()
        {
            InitializeComponent();
        }

        private void btnCreateMSH_Click(object sender, EventArgs e)
        {
            if(pathSelMSH.Path != "" && pathSelOBJ.Path != "")
            {
                AssetConverter.ConvertOBJToMSH(pathSelOBJ.Path, pathSelMSH.Path);
            }
        }
    }
}
