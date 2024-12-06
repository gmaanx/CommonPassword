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
    public partial class EditForm : Form
    {
        private List<Password> passwordList = new List<Password>();
        private string FilePath;
        public EditForm(string csvFilePath)
        {
            InitializeComponent();
            FilePath = csvFilePath;
            LoadCsvFile(FilePath);
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
        private void CalculatePasswordStats(Password password)
        {
            password.Length = password._Password.Length;
            password.NumChars = password._Password.Length; // Độ dài của password chính là số lượng ký tự
            password.NumDigits = password._Password.Count(char.IsDigit);
            password.NumUpper = password._Password.Count(char.IsUpper);
            password.NumLower = password._Password.Count(char.IsLower);
            password.NumSpecial = password._Password.Count(c => !char.IsLetterOrDigit(c));
            password.NumVowels = password._Password.Count(c => "aeiou".Contains(char.ToLower(c)));
            password.NumSyllables = CalculateSyllables(password._Password);
        }
        private int CalculateSyllables(string word)
        {
            // Giả định đơn giản cho việc tính toán số âm tiết
            int count = 0;
            bool lastWasVowel = false;

            foreach (char c in word)
            {
                if ("aeiouAEIOU".IndexOf(c) >= 0)
                {
                    if (!lastWasVowel)
                    {
                        count++;
                        lastWasVowel = true;
                    }
                }
                else
                {
                    lastWasVowel = false;
                }
            }

            return count;
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

        private void txtPasswordInput_Enter(object sender, EventArgs e)
        {
            ChangeTextBox(txtPasswordInput, "Enter password...", true);
        }

        private void txtPasswordInput_MouseLeave(object sender, EventArgs e)
        {
            ChangeTextBox(txtPasswordInput, "Enter password...", false);
        }

        private void AddBtn_Click(object sender, EventArgs e)
        {
            string newPassword = txtPasswordInput.Text; 

            if (!string.IsNullOrEmpty(newPassword))
            {
                Password password = new Password(newPassword);
                passwordList.Add(password); // Thêm vào danh sách passwordList

                // Thêm vào file CSV
                using (StreamWriter sw = File.AppendText(FilePath))
                {
                    sw.WriteLine(password._Password);  // Thêm password vào cuối file CSV
                }

                MessageBox.Show("Password đã được thêm thành công!");

                LoadCsvFile(FilePath); // Reload lại danh sách sau khi thêm
                txtPasswordInput.Clear();  // Xóa nội dung trong TextBox
            }
            else
            {
                MessageBox.Show("Vui lòng nhập password cần thêm.");
            }
        }

        private void removeBtn_Click(object sender, EventArgs e)
        {
            string passwordToRemove = txtPasswordInput.Text;  

            if (!string.IsNullOrEmpty(passwordToRemove))
            {
                // Tìm password trong danh sách và xóa nó
                var password = passwordList.FirstOrDefault(p => p._Password == passwordToRemove);
                if (password != null)
                {
                    passwordList.Remove(password);

                    // Xóa password khỏi file CSV
                    var updatedLines = File.ReadAllLines(FilePath).Where(line => !line.Contains(passwordToRemove)).ToList();
                    File.WriteAllLines(FilePath, updatedLines);

                    MessageBox.Show("Password đã được xóa thành công!");

                    LoadCsvFile(FilePath); // Reload lại danh sách sau khi xóa
                    txtPasswordInput.Clear(); // Xóa nội dung trong TextBox
                }
                else
                {
                    MessageBox.Show("Không tìm thấy password để xóa!");
                }
            }
            else
            {
                MessageBox.Show("Vui lòng nhập password cần xóa.");
            }
        }
    }
}
