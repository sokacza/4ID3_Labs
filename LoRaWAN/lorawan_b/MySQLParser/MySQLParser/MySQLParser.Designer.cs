namespace MySQLParser
{
    partial class MySQLParser
    {
        /// <summary>
        ///  Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        ///  Clean up any resources being used.
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
        ///  Required method for Designer support - do not modify
        ///  the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            btn_QueryDatabase = new Button();
            lbl_DatabaseIP = new Label();
            txt_DatabaseIP = new TextBox();
            txt_DatabaseName = new TextBox();
            lbl_DatabaseName = new Label();
            txt_DatabaseUsername = new TextBox();
            lbl_DatabaseUsername = new Label();
            txt_DatabasePassword = new TextBox();
            lbl_DatabasePassword = new Label();
            txt_QueryDatabase = new TextBox();
            grid_DataView = new DataGridView();
            ((System.ComponentModel.ISupportInitialize)grid_DataView).BeginInit();
            SuspendLayout();
            // 
            // btn_QueryDatabase
            // 
            btn_QueryDatabase.Location = new Point(58, 157);
            btn_QueryDatabase.Name = "btn_QueryDatabase";
            btn_QueryDatabase.Size = new Size(128, 23);
            btn_QueryDatabase.TabIndex = 0;
            btn_QueryDatabase.Text = "Query Database";
            btn_QueryDatabase.UseVisualStyleBackColor = true;
            btn_QueryDatabase.Click += btn_QueryDatabase_Click;
            // 
            // lbl_DatabaseIP
            // 
            lbl_DatabaseIP.AutoSize = true;
            lbl_DatabaseIP.Location = new Point(58, 55);
            lbl_DatabaseIP.Name = "lbl_DatabaseIP";
            lbl_DatabaseIP.Size = new Size(68, 15);
            lbl_DatabaseIP.TabIndex = 1;
            lbl_DatabaseIP.Text = "Database IP";
            // 
            // txt_DatabaseIP
            // 
            txt_DatabaseIP.Location = new Point(172, 52);
            txt_DatabaseIP.Name = "txt_DatabaseIP";
            txt_DatabaseIP.Size = new Size(182, 23);
            txt_DatabaseIP.TabIndex = 2;
            // 
            // txt_DatabaseName
            // 
            txt_DatabaseName.Location = new Point(172, 94);
            txt_DatabaseName.Name = "txt_DatabaseName";
            txt_DatabaseName.Size = new Size(182, 23);
            txt_DatabaseName.TabIndex = 4;
            // 
            // lbl_DatabaseName
            // 
            lbl_DatabaseName.AutoSize = true;
            lbl_DatabaseName.Location = new Point(58, 97);
            lbl_DatabaseName.Name = "lbl_DatabaseName";
            lbl_DatabaseName.Size = new Size(90, 15);
            lbl_DatabaseName.TabIndex = 3;
            lbl_DatabaseName.Text = "Database Name";
            // 
            // txt_DatabaseUsername
            // 
            txt_DatabaseUsername.Location = new Point(519, 55);
            txt_DatabaseUsername.Name = "txt_DatabaseUsername";
            txt_DatabaseUsername.Size = new Size(182, 23);
            txt_DatabaseUsername.TabIndex = 6;
            // 
            // lbl_DatabaseUsername
            // 
            lbl_DatabaseUsername.AutoSize = true;
            lbl_DatabaseUsername.BackColor = SystemColors.Control;
            lbl_DatabaseUsername.Location = new Point(405, 58);
            lbl_DatabaseUsername.Name = "lbl_DatabaseUsername";
            lbl_DatabaseUsername.Size = new Size(111, 15);
            lbl_DatabaseUsername.TabIndex = 5;
            lbl_DatabaseUsername.Text = "Database Username";
            // 
            // txt_DatabasePassword
            // 
            txt_DatabasePassword.Location = new Point(519, 97);
            txt_DatabasePassword.Name = "txt_DatabasePassword";
            txt_DatabasePassword.Size = new Size(182, 23);
            txt_DatabasePassword.TabIndex = 8;
            // 
            // lbl_DatabasePassword
            // 
            lbl_DatabasePassword.AutoSize = true;
            lbl_DatabasePassword.BackColor = SystemColors.Control;
            lbl_DatabasePassword.Location = new Point(405, 100);
            lbl_DatabasePassword.Name = "lbl_DatabasePassword";
            lbl_DatabasePassword.Size = new Size(108, 15);
            lbl_DatabasePassword.TabIndex = 7;
            lbl_DatabasePassword.Text = "Database Password";
            // 
            // txt_QueryDatabase
            // 
            txt_QueryDatabase.Location = new Point(206, 157);
            txt_QueryDatabase.Name = "txt_QueryDatabase";
            txt_QueryDatabase.Size = new Size(495, 23);
            txt_QueryDatabase.TabIndex = 9;
            // 
            // grid_DataView
            // 
            grid_DataView.ColumnHeadersHeightSizeMode = DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            grid_DataView.Location = new Point(58, 209);
            grid_DataView.Name = "grid_DataView";
            grid_DataView.RowTemplate.Height = 25;
            grid_DataView.Size = new Size(643, 212);
            grid_DataView.TabIndex = 10;
            // 
            // MySQLParser
            // 
            AutoScaleDimensions = new SizeF(7F, 15F);
            AutoScaleMode = AutoScaleMode.Font;
            ClientSize = new Size(800, 450);
            Controls.Add(grid_DataView);
            Controls.Add(txt_QueryDatabase);
            Controls.Add(txt_DatabasePassword);
            Controls.Add(lbl_DatabasePassword);
            Controls.Add(txt_DatabaseUsername);
            Controls.Add(lbl_DatabaseUsername);
            Controls.Add(txt_DatabaseName);
            Controls.Add(lbl_DatabaseName);
            Controls.Add(txt_DatabaseIP);
            Controls.Add(lbl_DatabaseIP);
            Controls.Add(btn_QueryDatabase);
            Name = "MySQLParser";
            Text = "MySQLParser";
            Load += Form1_Load;
            ((System.ComponentModel.ISupportInitialize)grid_DataView).EndInit();
            ResumeLayout(false);
            PerformLayout();
        }

        #endregion

        private Button btn_QueryDatabase;
        private Label lbl_DatabaseIP;
        private TextBox txt_DatabaseIP;
        private TextBox txt_DatabaseName;
        private Label lbl_DatabaseName;
        private TextBox txt_DatabaseUsername;
        private Label lbl_DatabaseUsername;
        private TextBox txt_DatabasePassword;
        private Label lbl_DatabasePassword;
        private TextBox txt_QueryDatabase;
        private DataGridView grid_DataView;
    }
}