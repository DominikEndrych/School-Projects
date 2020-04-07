namespace zapocty
{
    partial class Form1
    {
        /// <summary>
        /// Vyžaduje se proměnná návrháře.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Uvolněte všechny používané prostředky.
        /// </summary>
        /// <param name="disposing">hodnota true, když by se měl spravovaný prostředek odstranit; jinak false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Kód generovaný Návrhářem Windows Form

        /// <summary>
        /// Metoda vyžadovaná pro podporu Návrháře - neupravovat
        /// obsah této metody v editoru kódu.
        /// </summary>
        private void InitializeComponent()
        {
            this.listView = new System.Windows.Forms.ListView();
            this.columnLogin = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnPoints = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.columnHasPassed = ((System.Windows.Forms.ColumnHeader)(new System.Windows.Forms.ColumnHeader()));
            this.groupAdd = new System.Windows.Forms.GroupBox();
            this.labelAddError = new System.Windows.Forms.Label();
            this.buttonAdd = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.textBoxPoints = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.textBoxLogin = new System.Windows.Forms.TextBox();
            this.buttonDelete = new System.Windows.Forms.Button();
            this.groupModify = new System.Windows.Forms.GroupBox();
            this.labelModifyError = new System.Windows.Forms.Label();
            this.buttonModify = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.textBoxModifyPoints = new System.Windows.Forms.TextBox();
            this.label5 = new System.Windows.Forms.Label();
            this.textBoxModifyLogin = new System.Windows.Forms.TextBox();
            this.modifyButton = new System.Windows.Forms.Button();
            this.groupAdd.SuspendLayout();
            this.groupModify.SuspendLayout();
            this.SuspendLayout();
            // 
            // listView
            // 
            this.listView.Columns.AddRange(new System.Windows.Forms.ColumnHeader[] {
            this.columnLogin,
            this.columnPoints,
            this.columnHasPassed});
            this.listView.FullRowSelect = true;
            this.listView.HeaderStyle = System.Windows.Forms.ColumnHeaderStyle.Nonclickable;
            this.listView.HideSelection = false;
            this.listView.Location = new System.Drawing.Point(12, 12);
            this.listView.MultiSelect = false;
            this.listView.Name = "listView";
            this.listView.Size = new System.Drawing.Size(232, 203);
            this.listView.TabIndex = 1;
            this.listView.UseCompatibleStateImageBehavior = false;
            this.listView.View = System.Windows.Forms.View.Details;
            this.listView.SelectedIndexChanged += new System.EventHandler(this.listView_SelectedIndexChanged);
            // 
            // columnLogin
            // 
            this.columnLogin.Text = "Login";
            this.columnLogin.Width = 80;
            // 
            // columnPoints
            // 
            this.columnPoints.Text = "Body";
            // 
            // columnHasPassed
            // 
            this.columnHasPassed.Text = "Zápočet";
            // 
            // groupAdd
            // 
            this.groupAdd.Controls.Add(this.labelAddError);
            this.groupAdd.Controls.Add(this.buttonAdd);
            this.groupAdd.Controls.Add(this.label2);
            this.groupAdd.Controls.Add(this.textBoxPoints);
            this.groupAdd.Controls.Add(this.label1);
            this.groupAdd.Controls.Add(this.textBoxLogin);
            this.groupAdd.Location = new System.Drawing.Point(261, 12);
            this.groupAdd.Name = "groupAdd";
            this.groupAdd.Size = new System.Drawing.Size(245, 113);
            this.groupAdd.TabIndex = 2;
            this.groupAdd.TabStop = false;
            this.groupAdd.Text = "Přidat nového studenta";
            // 
            // labelAddError
            // 
            this.labelAddError.AutoSize = true;
            this.labelAddError.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F);
            this.labelAddError.Location = new System.Drawing.Point(6, 89);
            this.labelAddError.Name = "labelAddError";
            this.labelAddError.Size = new System.Drawing.Size(54, 13);
            this.labelAddError.TabIndex = 5;
            this.labelAddError.Text = "Error label";
            this.labelAddError.Visible = false;
            // 
            // buttonAdd
            // 
            this.buttonAdd.Location = new System.Drawing.Point(164, 84);
            this.buttonAdd.Name = "buttonAdd";
            this.buttonAdd.Size = new System.Drawing.Size(75, 23);
            this.buttonAdd.TabIndex = 3;
            this.buttonAdd.Text = "Přidat";
            this.buttonAdd.UseVisualStyleBackColor = true;
            this.buttonAdd.MouseClick += new System.Windows.Forms.MouseEventHandler(this.AddNewStudent);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(6, 55);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(34, 13);
            this.label2.TabIndex = 3;
            this.label2.Text = "Body:";
            // 
            // textBoxPoints
            // 
            this.textBoxPoints.Location = new System.Drawing.Point(47, 52);
            this.textBoxPoints.Name = "textBoxPoints";
            this.textBoxPoints.Size = new System.Drawing.Size(49, 20);
            this.textBoxPoints.TabIndex = 2;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 29);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(36, 13);
            this.label1.TabIndex = 1;
            this.label1.Text = "Login:";
            // 
            // textBoxLogin
            // 
            this.textBoxLogin.Location = new System.Drawing.Point(47, 26);
            this.textBoxLogin.Name = "textBoxLogin";
            this.textBoxLogin.Size = new System.Drawing.Size(137, 20);
            this.textBoxLogin.TabIndex = 0;
            // 
            // buttonDelete
            // 
            this.buttonDelete.Enabled = false;
            this.buttonDelete.Location = new System.Drawing.Point(12, 221);
            this.buttonDelete.Name = "buttonDelete";
            this.buttonDelete.Size = new System.Drawing.Size(75, 23);
            this.buttonDelete.TabIndex = 4;
            this.buttonDelete.Text = "Odstranit";
            this.buttonDelete.UseVisualStyleBackColor = true;
            this.buttonDelete.MouseClick += new System.Windows.Forms.MouseEventHandler(this.RemoveStudent);
            // 
            // groupModify
            // 
            this.groupModify.Controls.Add(this.labelModifyError);
            this.groupModify.Controls.Add(this.buttonModify);
            this.groupModify.Controls.Add(this.label4);
            this.groupModify.Controls.Add(this.textBoxModifyPoints);
            this.groupModify.Controls.Add(this.label5);
            this.groupModify.Controls.Add(this.textBoxModifyLogin);
            this.groupModify.Location = new System.Drawing.Point(261, 131);
            this.groupModify.Name = "groupModify";
            this.groupModify.Size = new System.Drawing.Size(245, 113);
            this.groupModify.TabIndex = 5;
            this.groupModify.TabStop = false;
            this.groupModify.Text = "Upravit zvoleného studenta";
            this.groupModify.Visible = false;
            // 
            // labelModifyError
            // 
            this.labelModifyError.AutoSize = true;
            this.labelModifyError.Font = new System.Drawing.Font("Microsoft Sans Serif", 7F);
            this.labelModifyError.Location = new System.Drawing.Point(6, 89);
            this.labelModifyError.Name = "labelModifyError";
            this.labelModifyError.Size = new System.Drawing.Size(54, 13);
            this.labelModifyError.TabIndex = 5;
            this.labelModifyError.Text = "Error label";
            this.labelModifyError.Visible = false;
            // 
            // buttonModify
            // 
            this.buttonModify.Location = new System.Drawing.Point(164, 84);
            this.buttonModify.Name = "buttonModify";
            this.buttonModify.Size = new System.Drawing.Size(75, 23);
            this.buttonModify.TabIndex = 3;
            this.buttonModify.Text = "Potvrdit";
            this.buttonModify.UseVisualStyleBackColor = true;
            this.buttonModify.MouseClick += new System.Windows.Forms.MouseEventHandler(this.ModifyStudent);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 55);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(34, 13);
            this.label4.TabIndex = 3;
            this.label4.Text = "Body:";
            // 
            // textBoxModifyPoints
            // 
            this.textBoxModifyPoints.Location = new System.Drawing.Point(47, 52);
            this.textBoxModifyPoints.Name = "textBoxModifyPoints";
            this.textBoxModifyPoints.Size = new System.Drawing.Size(49, 20);
            this.textBoxModifyPoints.TabIndex = 2;
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(6, 29);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(36, 13);
            this.label5.TabIndex = 1;
            this.label5.Text = "Login:";
            // 
            // textBoxModifyLogin
            // 
            this.textBoxModifyLogin.Location = new System.Drawing.Point(47, 26);
            this.textBoxModifyLogin.Name = "textBoxModifyLogin";
            this.textBoxModifyLogin.Size = new System.Drawing.Size(137, 20);
            this.textBoxModifyLogin.TabIndex = 0;
            // 
            // modifyButton
            // 
            this.modifyButton.Enabled = false;
            this.modifyButton.Location = new System.Drawing.Point(93, 221);
            this.modifyButton.Name = "modifyButton";
            this.modifyButton.Size = new System.Drawing.Size(75, 23);
            this.modifyButton.TabIndex = 6;
            this.modifyButton.Text = "Upravit";
            this.modifyButton.UseVisualStyleBackColor = true;
            this.modifyButton.MouseClick += new System.Windows.Forms.MouseEventHandler(this.EnableModifyMenu);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(523, 251);
            this.Controls.Add(this.modifyButton);
            this.Controls.Add(this.groupModify);
            this.Controls.Add(this.buttonDelete);
            this.Controls.Add(this.groupAdd);
            this.Controls.Add(this.listView);
            this.Name = "Form1";
            this.Text = "Evidence Studentů";
            this.groupAdd.ResumeLayout(false);
            this.groupAdd.PerformLayout();
            this.groupModify.ResumeLayout(false);
            this.groupModify.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion
        private System.Windows.Forms.ListView listView;
        private System.Windows.Forms.ColumnHeader columnLogin;
        private System.Windows.Forms.ColumnHeader columnPoints;
        private System.Windows.Forms.ColumnHeader columnHasPassed;
        private System.Windows.Forms.GroupBox groupAdd;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox textBoxLogin;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox textBoxPoints;
        private System.Windows.Forms.Button buttonAdd;
        private System.Windows.Forms.Button buttonDelete;
        private System.Windows.Forms.Label labelAddError;
        private System.Windows.Forms.GroupBox groupModify;
        private System.Windows.Forms.Label labelModifyError;
        private System.Windows.Forms.Button buttonModify;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.TextBox textBoxModifyPoints;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.TextBox textBoxModifyLogin;
        private System.Windows.Forms.Button modifyButton;
    }
}

