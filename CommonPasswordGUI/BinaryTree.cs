using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CommonPasswordGUI
{
    public class BinaryTree
    {
        private BinaryNode root;

        // Phương thức thêm một mật khẩu vào cây
        public void InsertPassword(Password password)
        {
            root = Insert(root, password);
        }

        private BinaryNode Insert(BinaryNode node, Password password)
        {
            if (node == null)
            {
                return new BinaryNode(password);
            }

            int comparison = string.Compare(password._Password, node.Data._Password);
            if (comparison < 0)
            {
                node.Left = Insert(node.Left, password);
            }
            else if (comparison > 0)
            {
                node.Right = Insert(node.Right, password);
            }
            return node;
        }

        // Phương thức xóa một mật khẩu khỏi cây
        public void DeletePassword(string password)
        {
            root = Delete(root, password);
        }

        private BinaryNode Delete(BinaryNode node, string password)
        {
            if (node == null)
                return null;

            int comparison = string.Compare(password, node.Data._Password);
            if (comparison < 0)
            {
                node.Left = Delete(node.Left, password);
            }
            else if (comparison > 0)
            {
                node.Right = Delete(node.Right, password);
            }
            else
            {
                // Trường hợp có một hoặc không có con
                if (node.Left == null)
                {
                    node = node.Right;
                }
                else if (node.Right == null)
                {
                    node = node.Left;
                }
                else
                {
                    // Trường hợp có hai con
                    BinaryNode minNode = FindMin(node.Right);
                    node.Data = minNode.Data;
                    node.Right = Delete(node.Right, minNode.Data._Password);
                }
            }
            return node;
        }

        // Phương thức tìm kiếm một mật khẩu trong cây
        public BinaryNode FindPassword(string password)
        {
            return FindPassword(root, password);
        }

        private BinaryNode FindPassword(BinaryNode node, string password)
        {
            if (node == null)
            {
                return null;
            }

            int comparison = string.Compare(password, node.Data._Password);
            if (comparison == 0)
            {
                return node;  // Mật khẩu đã tìm thấy
            }
            else if (comparison < 0)
            {
                return FindPassword(node.Left, password);
            }
            else
            {
                return FindPassword(node.Right, password);
            }
        }

        // Phương thức in ra tất cả các mật khẩu trong cây (Duyệt theo thứ tự InOrder)
        public void PrintPasswords()
        {
            InOrderTraversal(root);
        }

        private void InOrderTraversal(BinaryNode node)
        {
            if (node != null)
            {
                InOrderTraversal(node.Left);  // Duyệt trái
                Console.WriteLine(node.Data._Password);  // In mật khẩu
                InOrderTraversal(node.Right);  // Duyệt phải
            }
        }

        // Phương thức làm phẳng cây thành một mảng (flatten tree)
        public List<Password> FlattenTree()
        {
            List<Password> passwordList = new List<Password>();
            FlattenTree(root, passwordList);
            return passwordList;
        }

        private void FlattenTree(BinaryNode node, List<Password> passwordList)
        {
            if (node != null)
            {
                FlattenTree(node.Left, passwordList);
                passwordList.Add(node.Data);  // Thêm mật khẩu vào danh sách
                FlattenTree(node.Right, passwordList);
            }
        }

        // Phương thức sắp xếp các mật khẩu theo thứ tự tăng dần
        public void SortPasswords()
        {
            List<Password> passwordList = FlattenTree();
            passwordList.Sort((p1, p2) => string.Compare(p1._Password, p2._Password));
            Console.WriteLine("Sorted passwords:");
            foreach (var pass in passwordList)
            {
                Console.WriteLine(pass._Password);
            }
        }

        // Property
        public BinaryNode Root { get => root; set => root = value; }

        // Constructor
        public BinaryTree()
        {
            Root = null;
        }

        private BinaryNode InsertNode(BinaryNode node, Password password)
        {
            if (node == null)
            {
                return new BinaryNode(password);
            }

            int comparison = string.Compare(password._Password, node.Data._Password);
            if (comparison < 0)
            {
                node.Left = InsertNode(node.Left, password);
            }
            else if (comparison > 0)
            {
                node.Right = InsertNode(node.Right, password);
            }

            return node;
        }

        // Tìm nút có giá trị nhỏ nhất
        public BinaryNode FindMin(BinaryNode node)
        {
            if (node == null)
            {
                return null;
            }

            while (node.Left != null)
            {
                node = node.Left;
            }

            return node;
        }

        // Xóa mật khẩu khỏi cây
        public BinaryNode DeletePassword(BinaryNode root, string password)
        {
            if (root == null)
            {
                return null;
            }

            int comparison = string.Compare(password, root.Data._Password);

            if (comparison < 0)
            {
                root.Left = DeletePassword(root.Left, password);
            }
            else if (comparison > 0)
            {
                root.Right = DeletePassword(root.Right, password);
            }
            else
            {
                if (root.Left == null)
                {
                    return root.Right;
                }
                else if (root.Right == null)
                {
                    return root.Left;
                }

                BinaryNode minRightNode = FindMin(root.Right);
                root.Data = minRightNode.Data;
                root.Right = DeletePassword(root.Right, minRightNode.Data._Password);
            }

            return root;
        }

        // Lưu cây vào tệp
        public void SaveToFile(string filePath)
        {
            using (var writer = new System.IO.StreamWriter(filePath))
            {
                SaveNodeToFile(Root, writer);
            }
        }

        private void SaveNodeToFile(BinaryNode node, System.IO.StreamWriter writer)
        {
            if (node != null)
            {
                writer.WriteLine(node.Data._Password);
                SaveNodeToFile(node.Left, writer);
                SaveNodeToFile(node.Right, writer);
            }
        }
    }
}