namespace EngineEditor
{
    partial class frmAssetEditor
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.btnCreateMSH = new System.Windows.Forms.Button();
            this.pathSelMSH = new EngineEditor.PathSelectorControl();
            this.pathSelOBJ = new EngineEditor.PathSelectorControl();
            this.SuspendLayout();
            // 
            // btnCreateMSH
            // 
            this.btnCreateMSH.Location = new System.Drawing.Point(151, 111);
            this.btnCreateMSH.Name = "btnCreateMSH";
            this.btnCreateMSH.Size = new System.Drawing.Size(91, 23);
            this.btnCreateMSH.TabIndex = 2;
            this.btnCreateMSH.Text = "Create .MSH";
            this.btnCreateMSH.UseVisualStyleBackColor = true;
            this.btnCreateMSH.Click += new System.EventHandler(this.btnCreateMSH_Click);
            // 
            // pathSelMSH
            // 
            this.pathSelMSH.Filter = "MSH File (*.msh)|*.msh";
            this.pathSelMSH.Location = new System.Drawing.Point(20, 59);
            this.pathSelMSH.Name = "pathSelMSH";
            this.pathSelMSH.Path = "";
            this.pathSelMSH.Size = new System.Drawing.Size(367, 31);
            this.pathSelMSH.TabIndex = 1;
            this.pathSelMSH.Text = "MSH File";
            this.pathSelMSH.TypeSelection = EngineEditor.PathSelectorType.Save;
            // 
            // pathSelOBJ
            // 
            this.pathSelOBJ.Filter = "All files (*.*) |*.*|OBJ File (*.obj)|*.obj";
            this.pathSelOBJ.Location = new System.Drawing.Point(20, 12);
            this.pathSelOBJ.Name = "pathSelOBJ";
            this.pathSelOBJ.Path = "";
            this.pathSelOBJ.Size = new System.Drawing.Size(367, 31);
            this.pathSelOBJ.TabIndex = 0;
            this.pathSelOBJ.Text = "OBJ File";
            this.pathSelOBJ.TypeSelection = EngineEditor.PathSelectorType.Open;
            // 
            // frmAssetEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(399, 146);
            this.Controls.Add(this.pathSelMSH);
            this.Controls.Add(this.pathSelOBJ);
            this.Controls.Add(this.btnCreateMSH);
            this.Name = "frmAssetEditor";
            this.Text = "Asset Editor";
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.Button btnCreateMSH;
        private PathSelectorControl pathSelOBJ;
        private PathSelectorControl pathSelMSH;
    }
}