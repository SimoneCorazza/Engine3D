using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace EngineEditor
{
    public enum PathSelectorType
    {
        Open,
        Save
    }

    /// <summary>
    /// Controllo che rappresenta un generico path selector
    /// </summary>
    public partial class PathSelectorControl : UserControl
    {
        PathSelectorType typeSelection = PathSelectorType.Open;

        /// <summary>
        /// Ottiene o imposta la tipologia di selezione della path
        /// </summary>
        public PathSelectorType TypeSelection
        {
            get { return typeSelection; }
            set { typeSelection = value; }
        }

        /// <summary>
        /// Ottiene o imposta la path attualmente selezionata
        /// </summary>
        public string Path
        {
            get { return txtPath.Text; }
            set { txtPath.Text = value; }
        }


        /// <summary>
        /// Ottiene o imposta il filtro per l'OpenFileDialog o per il SaveFileDialog
        /// </summary>
        public string Filter { get; set; }

        /// <summary>
        /// Ottiene o imposta l'intestazione della label
        /// </summary>
        [EditorBrowsable(EditorBrowsableState.Always)]
        [Browsable(true)]
        [DesignerSerializationVisibility(DesignerSerializationVisibility.Visible)]
        [Bindable(true)]
        public override string Text
        {
            get { return lblName.Text; }
            set { lblName.Text = value; }
        }

        public PathSelectorControl()
        {
            InitializeComponent();
        }




        private void lblName_TextChanged(object sender, EventArgs e)
        {
            txtPath.Location = new Point(lblName.Location.X + lblName.PreferredWidth + 10, txtPath.Location.Y);
            txtPath.Size = new Size(btnSelect.Location.X - txtPath.Location.X - 10, txtPath.Size.Height);
        }

        private void btnSelect_Click(object sender, EventArgs e)
        {
            FileDialog op;
            if (typeSelection == PathSelectorType.Open)
            {
                op = new OpenFileDialog();
                ((OpenFileDialog)op).Multiselect = false;
            }
            else
                op = new SaveFileDialog();

            op.Filter = Filter;
            op.FileName = txtPath.Text;
            if (op.ShowDialog() == DialogResult.OK)
                txtPath.Text = op.FileName;
        }
    }
}
