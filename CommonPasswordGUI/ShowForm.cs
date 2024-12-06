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
using ComponentFactory.Krypton.Toolkit;

namespace CommonPasswordGUI
{
    public partial class ShowForm : Form
    {
        private List<string> passwordList = new List<string>();
        private List<string> displayedPasswords = new List<string>();
        public ShowForm(string csvFilePath)
        {
            InitializeComponent();
            LoadCsvFile(csvFilePath);
        }
        private void LoadCsvFile(string filePath)
        {
            passwordList.Clear();  // Xóa dữ liệu cũ
            if (File.Exists(filePath))
            {
                var lines = File.ReadAllLines(filePath);
                foreach (var line in lines)
                {
                    var parts = line.Split(',');
                    if (parts.Length >= 1)
                    {
                        passwordList.Add(parts[0]);  // Thêm password vào danh sách
                    }
                }
            }
            else
            {
                MessageBox.Show("File CSV không tồn tại!");
            }
        }
        private void PrintLines(int numLines)
        {
            if (passwordList.Count == 0)
            {
                MessageBox.Show("Không có dữ liệu để hiển thị.");
                return;
            }

            // Tính số dòng cần in (tối đa là số dòng trong file)
            int linesToPrint = Math.Min(numLines, passwordList.Count);

            listBoxOutput.Items.Clear();  // Xóa dữ liệu cũ trong ListBox
            displayedPasswords.Clear();  // Xóa dữ liệu cũ đã in

            // In các dòng vào ListBox và lưu vào danh sách đã in
            for (int i = 0; i < linesToPrint; i++)
            {
                listBoxOutput.Items.Add(passwordList[i]);  // Thêm dòng vào ListBox
                displayedPasswords.Add(passwordList[i]);  // Thêm vào danh sách đã in
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
        private void QuickSort(List<string> list, int low, int high)
        {
            if (low < high)
            {
                // Find pivot element such that
                // element smaller than pivot are on the left of pivot
                // and elements greater than pivot are on the right
                int pivotIndex = Partition(list, low, high);

                // Recursively apply the same logic to the left and right subarrays
                QuickSort(list, low, pivotIndex - 1);
                QuickSort(list, pivotIndex + 1, high);
            }
        }

        // Partition to rearrange the list for QuickSort
        private int Partition(List<string> list, int low, int high)
        {
            // Choose the rightmost element as pivot
            string pivot = list[high];
            int i = low - 1;  // Index of smaller element

            for (int j = low; j < high; j++)
            {
                // If current element is smaller than the pivot
                if (list[j].Length < pivot.Length)
                {
                    i++;
                    Swap(list, i, j);
                }
            }

            // Swap the pivot with the element at i+1
            Swap(list, i + 1, high);
            return i + 1;
        }

        // Helper method to swap elements in the list
        private void Swap(List<string> list, int i, int j)
        {
            string temp = list[i];
            list[i] = list[j];
            list[j] = temp;
        }
        private void PrintBtn_Click(object sender, EventArgs e)
        {
            int numLines;
            if (int.TryParse(txtNumLines.Text, out numLines))  // txtNumLines là TextBox để nhập số dòng
            {
                PrintLines(numLines);  // Gọi phương thức in
            }
            else
            {
                MessageBox.Show("Vui lòng nhập một số hợp lệ.");
            }
        }

        private void txtNumLines_Enter(object sender, EventArgs e)
        {
            ChangeTextBox(txtNumLines, "Enter n lines...", true);
        }

        private void txtNumLines_Leave(object sender, EventArgs e)
        {
            ChangeTextBox(txtNumLines, "Enter n lines...", false);
        }

        private void sortBtn_Click(object sender, EventArgs e)
        {
            if (displayedPasswords.Count > 0)
            {
                // Sắp xếp theo độ dài của password bằng QuickSort
                QuickSort(displayedPasswords, 0, displayedPasswords.Count - 1);

                // Sau khi sắp xếp, in lại danh sách vào ListBox
                listBoxOutput.Items.Clear();  // Xóa dữ liệu cũ trong ListBox
                foreach (var password in displayedPasswords)
                {
                    listBoxOutput.Items.Add(password);  // Thêm từng password vào ListBox đã sắp xếp
                }
                MessageBox.Show("Đã sắp xếp!", "Thông báo");
            }
            else
            {
                MessageBox.Show("Chưa có dữ liệu nào để sắp xếp.");
            }
        }
    }
    
}
