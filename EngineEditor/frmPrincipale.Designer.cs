namespace EngineEditor
{
    partial class frmPrincipale
    {
        /// <summary>
        /// Variabile di progettazione necessaria.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Pulire le risorse in uso.
        /// </summary>
        /// <param name="disposing">ha valore true se le risorse gestite devono essere eliminate, false in caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Codice generato da Progettazione Windows Form

        /// <summary>
        /// Metodo necessario per il supporto della finestra di progettazione. Non modificare
        /// il contenuto del metodo con l'editor di codice.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip_newEdit = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip_assetEditor = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip_sceneEditor = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip_exit = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip_closeProspective = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.menuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip
            // 
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem});
            this.menuStrip.Location = new System.Drawing.Point(0, 0);
            this.menuStrip.Name = "menuStrip";
            this.menuStrip.Size = new System.Drawing.Size(596, 24);
            this.menuStrip.TabIndex = 0;
            this.menuStrip.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuStrip_newEdit,
            this.menuStrip_closeProspective,
            this.toolStripMenuItem1,
            this.menuStrip_exit});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // menuStrip_newEdit
            // 
            this.menuStrip_newEdit.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menuStrip_assetEditor,
            this.menuStrip_sceneEditor});
            this.menuStrip_newEdit.Name = "menuStrip_newEdit";
            this.menuStrip_newEdit.Size = new System.Drawing.Size(167, 22);
            this.menuStrip_newEdit.Text = "Open Editor";
            // 
            // menuStrip_assetEditor
            // 
            this.menuStrip_assetEditor.Name = "menuStrip_assetEditor";
            this.menuStrip_assetEditor.Size = new System.Drawing.Size(152, 22);
            this.menuStrip_assetEditor.Text = "Asset Editor";
            this.menuStrip_assetEditor.Click += new System.EventHandler(this.menuStrip_assetEditor_Click);
            // 
            // menuStrip_sceneEditor
            // 
            this.menuStrip_sceneEditor.Name = "menuStrip_sceneEditor";
            this.menuStrip_sceneEditor.Size = new System.Drawing.Size(152, 22);
            this.menuStrip_sceneEditor.Text = "Scene Editor";
            // 
            // menuStrip_exit
            // 
            this.menuStrip_exit.Name = "menuStrip_exit";
            this.menuStrip_exit.Size = new System.Drawing.Size(167, 22);
            this.menuStrip_exit.Text = "Exit";
            // 
            // menuStrip_closeProspective
            // 
            this.menuStrip_closeProspective.Name = "menuStrip_closeProspective";
            this.menuStrip_closeProspective.Size = new System.Drawing.Size(167, 22);
            this.menuStrip_closeProspective.Text = "Close Prospective";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(164, 6);
            // 
            // frmPrincipale
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(596, 489);
            this.Controls.Add(this.menuStrip);
            this.IsMdiContainer = true;
            this.MainMenuStrip = this.menuStrip;
            this.Name = "frmPrincipale";
            this.Text = "Engine Editor";
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem menuStrip_newEdit;
        private System.Windows.Forms.ToolStripMenuItem menuStrip_assetEditor;
        private System.Windows.Forms.ToolStripMenuItem menuStrip_sceneEditor;
        private System.Windows.Forms.ToolStripMenuItem menuStrip_exit;
        private System.Windows.Forms.ToolStripMenuItem menuStrip_closeProspective;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
    }
}

