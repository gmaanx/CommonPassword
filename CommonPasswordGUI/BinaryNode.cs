using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CommonPasswordGUI
{
    public class BinaryNode
    {
        private Password data;
        private BinaryNode left;
        private BinaryNode right;

        // Properties
        public Password Data { get => data; set => data = value; }
        public BinaryNode Left { get => left; set => left = value; }
        public BinaryNode Right { get => right; set => right = value; }

        // Constructor
        public BinaryNode(Password data)
        {
            Data = data;
            Left = null;
            Right = null;
        }

        // 1. Phương thức tạo một nút mới với một mật khẩu
        public BinaryNode NewNode(Password password)
        {
            return new BinaryNode(password);
        }

        // 2. Phương thức thêm một nút vào cây
        public void Insert(BinaryNode node, Password password)
        {
            if (node == null)
            {
                node = new BinaryNode(password);
                return;
            }

            int comparison = string.Compare(password._Password, node.Data._Password);
            if (comparison < 0)
            {
                if (node.Left == null)
                {
                    node.Left = new BinaryNode(password);
                }
                else
                {
                    Insert(node.Left, password);
                }
            }
            else if (comparison > 0)
            {
                if (node.Right == null)
                {
                    node.Right = new BinaryNode(password);
                }
                else
                {
                    Insert(node.Right, password);
                }
            }
        }

        // 3. Phương thức xóa một nút khỏi cây
        public void Delete(BinaryNode root, string password)
        {
            if (root == null) return;

            int comparison = string.Compare(password, root.Data._Password);

            // Tìm kiếm nút cần xóa
            if (comparison < 0)
            {
                Delete(root.Left, password);
            }
            else if (comparison > 0)
            {
                Delete(root.Right, password);
            }
            else
            {
                // Trường hợp có một hoặc không có con
                if (root.Left == null)
                {
                    root = root.Right;
                }
                else if (root.Right == null)
                {
                    root = root.Left;
                }
                else
                {
                    // Trường hợp có hai con, tìm phần tử nhỏ nhất trong cây con bên phải
                    BinaryNode minNode = FindMin(root.Right);
                    root.Data = minNode.Data;
                    Delete(root.Right, minNode.Data._Password);
                }
            }
        }

        // 4. Phương thức tìm nút có giá trị nhỏ nhất trong cây con phải
        public BinaryNode FindMin(BinaryNode node)
        {
            if (node == null) return null;

            while (node.Left != null)
            {
                node = node.Left;
            }

            return node;
        }

        // 5. Phương thức duyệt cây theo thứ tự InOrder
        public void InOrderTraversal(BinaryNode node)
        {
            if (node != null)
            {
                InOrderTraversal(node.Left);  // Duyệt trái
                Console.WriteLine(node.Data._Password);  // In giá trị
                InOrderTraversal(node.Right);  // Duyệt phải
            }
        }
    }
}