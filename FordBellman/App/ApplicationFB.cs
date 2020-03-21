using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Matrix
{
    public partial class Form1 : Form
    {
        public int? SizeMatrix { get; set; } = null;
        public int? Source { get; set; } = null;

        public int[] validData = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 8 };
        public double[][] Matrix { get; set; }

        public Form1()
        {
            InitializeComponent();
        }

        private void CreateTextBox(Point location, int i, int j)
        {
            var textBox = new TextBox
            {
                Name = i + " " + j,
                Text = "0",
                Location = new Point(location.X,location.Y),
                Size = new Size(SizeTextBox.Size.Width, SizeTextBox.Size.Height)
            };
            textBox.TextChanged += (object sender, EventArgs e) =>
            {
                var valid = double.TryParse(textBox.Text, out double value);
                if (!valid)
                {
                    if (textBox.Text.Equals("-"))
                        Matrix[i][j] = double.MaxValue;
                    return;
                }
                Matrix[i][j] = value;
            };
            this.Controls.Add(textBox);
        }
        public void transp(double[][] a)
        {
            double tmp;
            for (int i = 0; i < a.GetLength(0); i++)
            {
                for (int j = 0; j < i; j++)
                {
                    tmp = a[i][j];
                    a[i][j] = a[j][i];
                    a[j][i] = tmp;
                }
            }
        }

        private void createMatrix()
        {
            double[][] matrix = new double[SizeMatrix.Value][];
            for(int i = 0; i < SizeMatrix; i++)
            {
                matrix[i] = new double[SizeMatrix.Value];
                for(int j = 0; j < SizeMatrix; j++)
                {
                    CreateTextBox(new Point((15 + SizeTextBox.Size.Width * j),
                        30 + (SizeTextBox.Size.Height * (i + 2))), i, j);
                }
            }
            Matrix = matrix;
        }
        private void create_click(object sender, EventArgs e)
        {
            if (this.SourceTextBox.Text.Equals("") || this.SizeTextBox.Text.Equals(""))
                 return;
            for (int i = 0; i < SizeMatrix; i++)
                for (int j = 0; j < SizeMatrix; j++)
                    this.Controls.RemoveByKey(i + " " + j);
            SizeMatrix = int.Parse(this.SizeTextBox.Text);
            createMatrix();
            create_matrix.Enabled = false;   
        }

        private void output_click(object sender, EventArgs e)
        {
            string output = "";
            for (int i = 0; i < SizeMatrix; i++)
            {           
                for (int j = 0; j < SizeMatrix; j++)
                {
                    if (Matrix[i][j] == double.MaxValue)
                        output += "\u221E";
                    else
                        output += Matrix[i][j].ToString();
                    output += (Matrix[i][j] < 0 ? "    " : "     ");
                }
                output += "\n";
            }

            OutPutLabel.Text = output;
        }
        private void SizeTextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            bool flag = validData.Contains((int)e.KeyChar);
            if (flag)
                e.Handled = false;
            else e.Handled = true;
        }

        private void SizeTextBox_TextChanged(object sender, EventArgs e)
        {
            if (!String.IsNullOrEmpty(SizeTextBox.Text) && SizeMatrix != int.Parse(SizeTextBox.Text))
                create_matrix.Enabled = true;
            else
                create_matrix.Enabled = false;
        }

        private void SourceTextBox_KeyPress(object sender, KeyPressEventArgs e)
        {
            bool flag = validData.Contains((int)e.KeyChar);
            if (flag) e.Handled = false;
            else e.Handled = true;
        }

        private void SourceTextBox_TextChanged(object sender, EventArgs e)
        {
            /*if (!String.IsNullOrEmpty(SourceTextBox.Text) && SizeMatrix != int.Parse(SourceTextBox.Text))
                create_matrix.Enabled = true;
            else
                create_matrix.Enabled = false;*/
        }

        private void FileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            
        }

        private void ReadFromFileToolStripMenuItem_Click(object sender, EventArgs e)
        {
            for (int i = 0; i < SizeMatrix; i++)
                for (int j = 0; j < SizeMatrix; j++)
                    this.Controls.RemoveByKey(i + " " + j);

            var size = String.Empty;
            var fileContent = string.Empty;
            var filePath = string.Empty;
            openFileDialog.InitialDirectory = "E:\repositories\files";
            openFileDialog.Filter = "txt files (*.txt)|*.txt|All files (*.*)|*.*";
            openFileDialog.FilterIndex = 2;
            openFileDialog.RestoreDirectory = true;

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                //Get the path of specified file
                filePath = openFileDialog.FileName;

                //Read the contents of the file into a stream
                var fileStream = openFileDialog.OpenFile();

                using (StreamReader reader = new StreamReader(fileStream))
                {
                    size = reader.ReadLine();
                    var valid = int.TryParse(size, out int value);
                    if (!valid)
                    {
                        MessageBox.Show("aga, bukvi v texte\n size matrix can not be letters", "ErrorMessage");
                        return;
                    }
                    else
                    {
                        SizeMatrix = value;
                    }

                    createMatrix();
                    SizeTextBox.Text = SizeMatrix.ToString();

                    int rows = 0;
                    String[] buff;
                    while (!reader.EndOfStream)
                    {
                        fileContent = reader.ReadLine();
                        buff = fileContent.Split(' ');
                        try
                        {
                            for (int j = 0; j < SizeMatrix; j++)
                            {
                                if (buff[j].Equals("-"))
                                    Matrix[rows][j] = double.MaxValue;
                                else
                                    Matrix[rows][j] = double.Parse(buff[j]);

                                var v = this.Controls.Find(rows + " " + j, false);
                                if (Matrix[rows][j] != double.MaxValue)
                                    v[0].Text = Matrix[rows][j].ToString();
                                else
                                    v[0].Text = "\u221E";
                            }
                        }
                        catch
                        {
                            MessageBox.Show("aga, bukvi v texte");
                            return;
                        }

                        rows++;
                        fileContent = String.Empty;
                    }
                    reader.Close();
                }
            }
        }

        private void Calculate_Click(object sender, EventArgs e)
        {
            bool check = false;
            double[] res = null;
            int source = int.Parse(SourceTextBox.Text) - 1;
            Thread th = new Thread(() => {
                try
                {
                    res = FordBellman.ALgorithm.FordBellman(Matrix, source);
                }
                catch(ArgumentException error)
                {
                    MessageBox.Show(error.Message, "ErrorMessage");
                    check = true;
                }
            });
            th.Start();
            th.Join();

            if (check) return;

            String output = "from the top V = " + (source + 1).ToString() + " to..\n\n";
            for (int i = 0; i < SizeMatrix; i++)
            {
                output += (i + 1).ToString() + "  with weight = ";
                if (res[i] == double.MaxValue)
                    output += "\u221E";
                else
                    output += res[i].ToString();
                output += "\n";
            }
            SolutionOutPut.Text = output;
        }

        private void ExitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("Exit application without save?", "Message", 
                MessageBoxButtons.YesNo) == DialogResult.No) return;
            Application.Exit();
        }

        private void FAQToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Form FAQ = new Form();
            FAQ.Text = "Frequently Asked Questions";
            FAQ.MinimumSize = new Size(400, 220);

            Label labelHelp = new Label();
            labelHelp.Location = new Point(20, 20);
            labelHelp.Size = new Size(350, 200);
            labelHelp.Font = new Font(labelHelp.Font.Name, 18.0F,
                                        labelHelp.Font.Style, labelHelp.Font.Unit);
            labelHelp.Text += "1. '-' is symbol of infinity (" + "\u221E" + ")\n";
            labelHelp.Text += "2. file saving does not work\n";
            labelHelp.Text += "3. CreateMatrix is create rows and column\n";
            labelHelp.Text += "4. LogOut is matrix output\n";
            labelHelp.Text += "5. 'calculate' is run algorithm Ford-Bellman\n";

            FAQ.Controls.Add(labelHelp);
     
            FAQ.ShowDialog();
        }

        private void SaveToolStripMenuItem_Click(object sender, EventArgs e)
        {

        }
    }
}
