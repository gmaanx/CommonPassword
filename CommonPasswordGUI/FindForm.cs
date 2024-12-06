using ComponentFactory.Krypton.Toolkit;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;

namespace CommonPasswordGUI
{
    public partial class FindForm : Form
    {
        private List<Password> passwordList = new List<Password>();
        public FindForm(string csvFilePath)
        {
            InitializeComponent();
            LoadCsvFile(csvFilePath);
        }
        private void LoadCsvFile(string filePath)
        {
            passwordList.Clear();
            if (File.Exists(filePath))
            {
                var lines = File.ReadAllLines(filePath);
                foreach (var line in lines)
                {
                    var parts = line.Split(',');
                    if (parts.Length >= 1)
                    {
                        var password = new Password(parts[0]); 
                        passwordList.Add(password);
                    }
                }
            }
            else
            {
                MessageBox.Show("File CSV không tồn tại!");
            }
        }
        private void ChangeTextBox(KryptonTextBox textBox, string text, bool isEntering)
        {
            if (isEntering && textBox.Text == text)
            {
                textBox.Text = "";
            }
            else if (!isEntering && string.IsNullOrWhiteSpace(textBox.Text))
            {
                textBox.Text = text;
            }
        }

        private void findBtn_Click(object sender, EventArgs e)
        {
            string searchQuery = txtPasswordInput.Text; // txtPasswordInput là TextBox để nhập từ khóa tìm kiếm
            var foundPasswords = passwordList.Where(p => p._Password.Contains(searchQuery)).ToList();

            if (foundPasswords.Any())
            {
                StringBuilder result = new StringBuilder(); // Chuỗi kết quả để hiển thị trong MessageBox
                foreach (var password in foundPasswords)
                {
                    result.AppendLine($"Password: {password._Password}, Length: {password.Length}, " +
                                      $"Chars: {password.NumChars}, Digits: {password.NumDigits}, " +
                                      $"Upper: {password.NumUpper}, Lower: {password.NumLower}, " +
                                      $"Special: {password.NumSpecial}, Vowels: {password.NumVowels}, " +
                                      $"Syllables: {password.NumSyllables}");
                }
                // Hiển thị tất cả kết quả trong MessageBox
                MessageBox.Show(result.ToString(), "Kết quả tìm kiếm");
            }
            else
            {
                MessageBox.Show("Không tìm thấy password nào khớp!", "Thông báo");
            }
        }

        private void txtPasswordInput_Enter(object sender, EventArgs e)
        {
            ChangeTextBox(txtPasswordInput, "Enter password...", true);
        }

        private void txtPasswordInput_Leave(object sender, EventArgs e)
        {
            ChangeTextBox(txtPasswordInput, "Enter password...", false);
        }
    }
}
