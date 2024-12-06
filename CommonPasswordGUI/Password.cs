using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace CommonPasswordGUI
{
    public class Password
    {
        private string password;
        private int length;
        private int numChars;
        private int numDigits;
        private int numUpper;
        private int numLower;
        private int numSpecial;
        private int numVowels;
        private int numSyllables;

        // Các properties
        public string _Password { get => password; set => password = value; }
        public int Length { get => length; set => length = value; }
        public int NumChars { get => numChars; set => numChars = value; }
        public int NumDigits { get => numDigits; set => numDigits = value; }
        public int NumUpper { get => numUpper; set => numUpper = value; }
        public int NumLower { get => numLower; set => numLower = value; }
        public int NumSpecial { get => numSpecial; set => numSpecial = value; }
        public int NumVowels { get => numVowels; set => numVowels = value; }
        public int NumSyllables { get => numSyllables; set => numSyllables = value; }

        // Constructor
        public Password(string password)
        {
            _Password = password;
            CalculatePasswordStats();
        }

        // Tính toán thống kê mật khẩu
        private void CalculatePasswordStats()
        {
            Length = _Password.Length;
            NumChars = _Password.Length;
            NumDigits = 0;
            NumUpper = 0;
            NumLower = 0;
            NumSpecial = 0;
            NumVowels = 0;
            NumSyllables = 0;

            foreach (var ch in _Password)
            {
                if (char.IsDigit(ch)) NumDigits++;
                else if (char.IsUpper(ch)) NumUpper++;
                else if (char.IsLower(ch)) NumLower++;
                else NumSpecial++;

                if ("aeiou".Contains(char.ToLower(ch))) NumVowels++;
            }

            // Cập nhật số âm tiết (ước tính đơn giản)
            NumSyllables = NumVowels;
        }
    }
}