namespace EngineEditor.SceneEditor
{
    partial class frmSceneEditor
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
            this.menuStrip = new System.Windows.Forms.MenuStrip();
            this.menu_scene = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_items = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_addItem = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_addCamera = new System.Windows.Forms.ToolStripMenuItem();
            this.menu_addActor = new System.Windows.Forms.ToolStripMenuItem();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripSeparator();
            this.menu_sceneGeneralSettings = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip
            // 
            this.menuStrip.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menu_scene,
            this.menu_items});
            this.menuStrip.Location = new System.Drawing.Point(0, 0);
            this.menuStrip.Name = "menuStrip";
            this.menuStrip.Size = new System.Drawing.Size(927, 24);
            this.menuStrip.TabIndex = 0;
            this.menuStrip.Text = "menuStrip";
            // 
            // menu_scene
            // 
            this.menu_scene.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menu_sceneGeneralSettings});
            this.menu_scene.Name = "menu_scene";
            this.menu_scene.Size = new System.Drawing.Size(50, 20);
            this.menu_scene.Text = "Scene";
            // 
            // menu_items
            // 
            this.menu_items.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menu_addItem,
            this.toolStripMenuItem1});
            this.menu_items.Name = "menu_items";
            this.menu_items.Size = new System.Drawing.Size(48, 20);
            this.menu_items.Text = "Items";
            // 
            // menu_addItem
            // 
            this.menu_addItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.menu_addCamera,
            this.menu_addActor});
            this.menu_addItem.Name = "menu_addItem";
            this.menu_addItem.Size = new System.Drawing.Size(152, 22);
            this.menu_addItem.Text = "Add";
            // 
            // menu_addCamera
            // 
            this.menu_addCamera.Name = "menu_addCamera";
            this.menu_addCamera.Size = new System.Drawing.Size(152, 22);
            this.menu_addCamera.Text = "Camera";
            // 
            // menu_addActor
            // 
            this.menu_addActor.Name = "menu_addActor";
            this.menu_addActor.Size = new System.Drawing.Size(152, 22);
            this.menu_addActor.Text = "Actor";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(149, 6);
            // 
            // menu_sceneGeneralSettings
            // 
            this.menu_sceneGeneralSettings.Name = "menu_sceneGeneralSettings";
            this.menu_sceneGeneralSettings.Size = new System.Drawing.Size(158, 22);
            this.menu_sceneGeneralSettings.Text = "General settings";
            // 
            // frmSceneEditor
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(927, 666);
            this.Controls.Add(this.menuStrip);
            this.MainMenuStrip = this.menuStrip;
            this.Name = "frmSceneEditor";
            this.Text = "Scene Editor";
            this.menuStrip.ResumeLayout(false);
            this.menuStrip.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip;
        private System.Windows.Forms.ToolStripMenuItem menu_scene;
        private System.Windows.Forms.ToolStripMenuItem menu_sceneGeneralSettings;
        private System.Windows.Forms.ToolStripMenuItem menu_items;
        private System.Windows.Forms.ToolStripMenuItem menu_addItem;
        private System.Windows.Forms.ToolStripMenuItem menu_addCamera;
        private System.Windows.Forms.ToolStripMenuItem menu_addActor;
        private System.Windows.Forms.ToolStripSeparator toolStripMenuItem1;
    }
}