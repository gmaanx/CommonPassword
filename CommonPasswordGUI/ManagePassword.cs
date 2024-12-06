using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;

namespace CommonPasswordGUI
{
    public class ManagePassword
    {
        private BinaryTree passwordTree;

        // Constructor
        public ManagePassword()
        {
            passwordTree = new BinaryTree();
        }

        // Thêm mật khẩu
        public void AddPassword(string password)
        {
            var newPassword = new Password(password);
            passwordTree.InsertPassword(newPassword);
        }

        // Xóa mật khẩu
        public void DeletePassword(string password)
        {
            passwordTree.DeletePassword(passwordTree.Root, password);
        }

        // Lưu mật khẩu vào tệp
        public void SavePasswordsToFile(string filePath)
        {
            passwordTree.SaveToFile(filePath);
        }

        // Đọc mật khẩu từ tệp
        public void ReadPasswordsFromFile(string filePath)
        {
            using (StreamReader reader = new StreamReader(filePath))
            {
                string line;
                while ((line = reader.ReadLine()) != null)
                {
                    AddPassword(line);
                }
            }
        }

        // Hiển thị mật khẩu
        public void DisplayPasswords()
        {
            passwordTree.PrintPasswords();
        }
    }
}