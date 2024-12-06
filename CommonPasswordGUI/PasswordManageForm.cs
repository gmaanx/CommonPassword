using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using ComponentFactory.Krypton.Toolkit;

namespace CommonPasswordGUI
{
    public partial class PasswordManageForm : KryptonForm
    {
        [DllImport("Gdi32.dll", EntryPoint = "CreateRoundRectRgn")]
        private static extern IntPtr CreateRoundRectRgn(
           int nLeftRect,
           int nTopRect,
           int nRightRect,
           int nBottomRect,
           int nWidthEllipse,
           int nHeightEllipse);

        private const string csvFilePath = @"D:/UTE-DataStructure/common_passwords.csv";
        public PasswordManageForm()
        {
            InitializeComponent();

            this.Region = System.Drawing.Region.FromHrgn(CreateRoundRectRgn(0, 0, this.Width, this.Height, 25, 25));
            UpdateForm(mainBtn, new ShowForm(csvFilePath));

        }
        private void SetButtonDefaultColors()
        {
            mainBtn.StateCommon.Back.Color1 = Color.FromArgb(240, 232, 217);
            mainBtn.StateCommon.Back.Color2 = Color.FromArgb(240, 232, 217);
            mainBtn.StateCommon.Content.ShortText.Color1 = Color.FromArgb(4, 28, 9);

            findBtn.StateCommon.Back.Color1 = Color.FromArgb(240, 232, 217);
            findBtn.StateCommon.Back.Color2 = Color.FromArgb(240, 232, 217);
            findBtn.StateCommon.Content.ShortText.Color1 = Color.FromArgb(4, 28, 9);

            EditBtn.StateCommon.Back.Color1 = Color.FromArgb(240, 232, 217);
            EditBtn.StateCommon.Back.Color2 = Color.FromArgb(240, 232, 217);
            EditBtn.StateCommon.Content.ShortText.Color1 = Color.FromArgb(4, 28, 9);

            graphBtn.StateCommon.Back.Color1 = Color.FromArgb(240, 232, 217);
            graphBtn.StateCommon.Back.Color2 = Color.FromArgb(240, 232, 217);
            graphBtn.StateCommon.Content.ShortText.Color1 = Color.FromArgb(4, 28, 9);
        }
        private void UpdateButtonColors(KryptonButton button)
        {
            SetButtonDefaultColors();
            button.StateCommon.Back.Color1 = Color.FromArgb(26, 33, 53);
            button.StateCommon.Back.Color2 = Color.FromArgb(26, 33, 53);
            button.StateCommon.Content.ShortText.Color1 = Color.FromArgb(240, 232, 217);
        }
        private void LoadForm(Form form)
        {
            if (form == null) return;

            form.Dock = DockStyle.Fill;
            form.TopLevel = false;
            form.TopMost = true;
            form.FormBorderStyle = FormBorderStyle.None;

            this.pnlFormLoader.Controls.Add(form);
            form.Show();
        }
        private void UpdateForm(KryptonButton button, Form form)
        {
            SetButtonDefaultColors();
            button.StateCommon.Back.Color1 = Color.FromArgb(26, 33, 53);
            button.StateCommon.Back.Color2 = Color.FromArgb(26, 33, 53);
            button.StateCommon.Content.ShortText.Color1 = Color.FromArgb(240, 232, 217);

            this.pnlFormLoader.Controls.Clear();

            LoadForm(form);
        }

        private void showBtn_Click(object sender, EventArgs e)
        {
            UpdateForm(mainBtn, new ShowForm(csvFilePath));
        }

        private void findBtn_Click(object sender, EventArgs e)
        {
            UpdateForm(findBtn, new FindForm(csvFilePath));
        }

        private void EditBtn_Click(object sender, EventArgs e)
        {
            UpdateForm(EditBtn, new EditForm(csvFilePath));
        }

        private void graphBtn_Click(object sender, EventArgs e)
        {
            UpdateForm(graphBtn, new GraphForm());
        }
    }
}
