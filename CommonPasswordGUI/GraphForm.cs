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

namespace CommonPasswordGUI
{
    public partial class GraphForm : Form
    {
        public GraphForm()
        {
            InitializeComponent();
            pictureStatus(true, false, false, false, false, false);
            MainButton(lengthBtn);
        }
        private void pictureStatus(bool length, bool numChars,
            bool numDigits, bool numLower, bool numUpper, bool numVowels)
        {
            lengthGraph.Visible = length;
            numCharsGraph.Visible = numChars;
            numDigitsGraph.Visible = numDigits;
            numLowerGraph.Visible = numLower;
            numUpperGraph.Visible = numUpper;
            numVowelsGraph.Visible = numVowels;
        }
        private void SetButtonDefaultColors()
        {
            lengthBtn.StateCommon.Back.Color1 = Color.FromArgb(26, 33, 53);
            lengthBtn.StateCommon.Back.Color2 = Color.FromArgb(26, 33, 53);
            lengthBtn.StateCommon.Content.ShortText.Color1 = Color.FromArgb(240, 232, 217);

            charBtn.StateCommon.Back.Color1 = Color.FromArgb(26, 33, 53);
            charBtn.StateCommon.Back.Color2 = Color.FromArgb(26, 33, 53);
            charBtn.StateCommon.Content.ShortText.Color1 = Color.FromArgb(240, 232, 217);

            digitBtn.StateCommon.Back.Color1 = Color.FromArgb(26, 33, 53);
            digitBtn.StateCommon.Back.Color2 = Color.FromArgb(26, 33, 53);
            digitBtn.StateCommon.Content.ShortText.Color1 = Color.FromArgb(240, 232, 217);

            lowerBtn.StateCommon.Back.Color1 = Color.FromArgb(26, 33, 53);
            lowerBtn.StateCommon.Back.Color2 = Color.FromArgb(26, 33, 53);
            lowerBtn.StateCommon.Content.ShortText.Color1 = Color.FromArgb(240, 232, 217);

            upperBtn.StateCommon.Back.Color1 = Color.FromArgb(26, 33, 53);
            upperBtn.StateCommon.Back.Color2 = Color.FromArgb(26, 33, 53);
            upperBtn.StateCommon.Content.ShortText.Color1 = Color.FromArgb(240, 232, 217);

            vowelBtn.StateCommon.Back.Color1 = Color.FromArgb(26, 33, 53);
            vowelBtn.StateCommon.Back.Color2 = Color.FromArgb(26, 33, 53);
            vowelBtn.StateCommon.Content.ShortText.Color1 = Color.FromArgb(240, 232, 217);
        }
        private void MainButton(KryptonButton button)
        {
            SetButtonDefaultColors();
            button.StateCommon.Back.Color1 = Color.FromArgb(240, 232, 217);
            button.StateCommon.Back.Color2 = Color.FromArgb(240, 232, 217);
            button.StateCommon.Content.ShortText.Color1 = Color.FromArgb(26, 33, 53);

            button.OverrideDefault.Back.Color1 = button.StateCommon.Back.Color1;
            button.OverrideDefault.Back.Color2 = button.StateCommon.Back.Color2;
            button.OverrideDefault.Content.ShortText.Color1 = button.StateCommon.Content.ShortText.Color1;
            button.OverrideDefault.Content.ShortText.Color2 = button.StateCommon.Content.ShortText.Color2;

            button.StateTracking.Back.Color1 = button.StateCommon.Back.Color1;
            button.StateTracking.Back.Color2 = button.StateCommon.Back.Color2;
            button.StateTracking.Content.ShortText.Color1 = button.StateTracking.Content.ShortText.Color1;
            button.StateTracking.Content.ShortText.Color2 = button.StateTracking.Content.ShortText.Color2;
        }

        private void lengthBtn_Click(object sender, EventArgs e)
        {
            MainButton(lengthBtn);
            pictureStatus(true, false, false, false, false, false);
        }

        private void charBtn_Click(object sender, EventArgs e)
        {
            MainButton(charBtn);
            pictureStatus(false, true, false, false, false, false);
        }

        private void digitBtn_Click(object sender, EventArgs e)
        {
            MainButton(digitBtn);
            pictureStatus(false, false, true, false, false, false);         
        }

        private void lowerBtn_Click(object sender, EventArgs e)
        {
            MainButton(lowerBtn);
            pictureStatus(false, false, false, true, false, false);
        }

        private void upperBtn_Click(object sender, EventArgs e)
        {
            MainButton(upperBtn);
            pictureStatus(false, false, false, false, true, false);
        }

        private void vowelBtn_Click(object sender, EventArgs e)
        {
            MainButton(vowelBtn);
            pictureStatus(false, false, false, false, false, true);
        }
    }
}
