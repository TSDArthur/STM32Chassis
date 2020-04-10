using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Crane_Manager
{
    public partial class FormMain : Form
    {
        [DllImport("user32.DLL")]
        public static extern bool RegisterTouchWindow(IntPtr hwnd, int ulFlags);
        [DllImport("user32.DLL")]
        public static extern bool UnregisterTouchWindow(IntPtr hwnd);
        public FormMain()
        {
            InitializeComponent();
            RegisterTouchWindow(buttonX20.Handle, 0);
        }

        private SerialPort port = null;
        public string taskRecord = "";
        public int Vx = 0, Vy = 0, Rw = 0;
        public int StepperHeight = 0, Angle = 0;
        public double P = 7, I = 4.5;
        public int pulleyAState = 1;
        public int pulleyBState = 1;
        public int pulleyCState = 1;
        public int pulleyCHook = 0;
        string[] dataVal = new string[8];

        void SetSendContent()
        {
            textBoxSend.Text = "(" + Vx.ToString() + " " +
                Vy.ToString() + " " +
                Rw.ToString() + " " +
                StepperHeight.ToString() + " " +
                pulleyAState.ToString() + " " +
                pulleyBState.ToString() + " " +
                pulleyCState.ToString() + " " +
                pulleyCHook.ToString() + " " +
                P.ToString() + " " +
                I.ToString() + ")";
            return;
        }

        void Port_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            this.RefreshInfoTextBox();
        }

        /// <summary>
        /// Initialize Serials
        /// </summary>
        private bool InitialSerialPort()
        {
            bool retValue = false;
            try
            {
                string portName = comboBoxSerial.SelectedItem.ToString();
                port = new SerialPort(portName, 115200)
                {
                    Encoding = Encoding.ASCII,
                    ReceivedBytesThreshold = 1
                };
                port.DataReceived += Port_DataReceived;
                port.Open();
                retValue = true;
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error：" + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Information);
                retValue = false;
            }
            return retValue;
        }

        /// <summary>
        /// read data from serial
        /// </summary>
        /// <returns></returns>
        private string ReadSerialData()
        {
            string value = String.Empty;
            try
            {
                port.ReceivedBytesThreshold = port.ReadBufferSize;
                while (port != null && port.BytesToRead > 0)
                {
                    value += port.ReadExisting();
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show("Error：" + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            port.ReceivedBytesThreshold = 1;
            return value;
        }

        /// <summary>
        /// refresh the task list
        /// </summary>
        private void RefreshInfoTextBox()
        {
            string value = this.ReadSerialData();
            taskRecord += value;
            if (taskRecord.Substring(taskRecord.Length - 1, 1) != ")") return;
            int st = 0, ed = 0;
            for (int i = 0; i < taskRecord.Length; i++)
            {
                if (taskRecord.Substring(i, 1) == "(")
                {
                    st = i;
                    break;
                }
            }
            for (int i = taskRecord.Length - 1; i >= 0; i--)
            {
                if (taskRecord.Substring(i, 1) == ")")
                {
                    ed = i;
                    break;
                }
            }
            if (ed <= st) return;
            taskRecord = taskRecord.Substring(st + 1, ed - st - 1);
            dataVal = taskRecord.Split(' ');
            taskRecord = String.Empty;
        }

        /// <summary>
        /// Dispose Serials
        /// </summary>
        private void DisposeSerialPort()
        {
            if (port != null)
            {
                try
                {
                    if (port.IsOpen)
                    {
                        port.Close();
                    }
                    port.Dispose();
                }
                catch (Exception ex)
                {
                    MessageBox.Show("Error：" + ex.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Information);
                }
            }
        }
        private void FormMain_Load(object sender, EventArgs e)
        {
            this.comboBoxSerial.Items.AddRange(SerialPort.GetPortNames());
            this.comboBoxSerial.SelectedIndex = this.comboBoxSerial.Items.Count - 1;
        }

        private void ButtonX20_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonX15_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Butto10_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonRotateL_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button5RotateR_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonXn10_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonXn15_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonXn20_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtY10_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtY15_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtY20_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtYn10_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtYn15_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtYn20_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonX20_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 60;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonX15_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 30;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Butto10_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 15;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonRotateL_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 2;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button5RotateR_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = -2;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonXn10_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -15;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonXn15_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -30;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonXn20_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -60;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtY10_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 15;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtY15_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 30;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtY20_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 60;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtYn10_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = -15;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtYn15_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = -30;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtYn20_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = -60;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button1010_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 15;
                Vy = 15;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button1010_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button1015_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 15;
                Vy = 30;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button1015_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button1020_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 15;
                Vy = 60;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button1020_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button1510_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 30;
                Vy = 15;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button1510_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button1515_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 30;
                Vy = 30;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button1515_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button1520_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 30;
                Vy = 60;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button1520_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button2010_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 60;
                Vy = 15;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button2010_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button2015_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 60;
                Vy = 30;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button2015_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button2020_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 60;
                Vy = 60;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button2020_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn1010_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -15;
                Vy = 15;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn1010_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn1015_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -15;
                Vy = 30;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn1015_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn1020_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -15;
                Vy = 60;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn1020_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn1510_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn1515_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn1520_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn2010_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn2015_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn2020_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button20n20_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button20n15_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button20n10_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button15n20_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button15n15_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button15n10_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button10n20_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button10n15_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button10n10_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn10n20_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn10n15_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn10n10_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn15n20_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn15n15_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn15n10_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttn20n20_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn20n15_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn20n10_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 0;
                Vy = 0;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn1510_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -30;
                Vy = 15;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn1515_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -30;
                Vy = 30;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn1520_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -30;
                Vy = 60;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn2010_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -60;
                Vy = 15;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn2015_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -60;
                Vy = 30;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn2020_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -60;
                Vy = 60;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button20n20_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 60;
                Vy = -60;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button20n15_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 60;
                Vy = -30;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button20n10_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 60;
                Vy = -15;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button15n20_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 30;
                Vy = -60;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button15n15_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 30;
                Vy = -30;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button15n10_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 30;
                Vy = -15;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button10n20_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 15;
                Vy = -60;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button10n15_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 15;
                Vy = -30;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Button10n10_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = 15;
                Vy = -15;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn10n20_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -15;
                Vy = -60;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn10n15_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -15;
                Vy = -30;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn10n10_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -15;
                Vy = -15;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn15n20_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -30;
                Vy = -60;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn15n15_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -30;
                Vy = -30;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn15n10_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -30;
                Vy = -15;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttn20n20_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -60;
                Vy = -60;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn20n15_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -60;
                Vy = -30;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonPPlus_Click(object sender, EventArgs e)
        {
            P += 0.2;
        }

        private void ButtonPDown_Click(object sender, EventArgs e)
        {
            P -= 0.2;
        }

        private void ButtonIPlus_Click(object sender, EventArgs e)
        {
            I += 0.2;
        }

        private void ButtonIDown_Click(object sender, EventArgs e)
        {
            I -= 0.2;
        }

        private void ButtonX15_Click(object sender, EventArgs e)
        {

        }

        private void ButtonPAF_Click(object sender, EventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                pulleyAState = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonPAI_Click(object sender, EventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                pulleyAState = 1;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonPAB_Click(object sender, EventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                pulleyAState = 2;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonPAL_Click(object sender, EventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                pulleyAState = 3;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonPAR_Click(object sender, EventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                pulleyAState = 4;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonStpUp_Click(object sender, EventArgs e)
        {
            StepperHeight += 5;
        }

        private void ButtonStpDown_Click(object sender, EventArgs e)
        {
            StepperHeight -= 5;
        }

        private void ButtonPBF_Click(object sender, EventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                pulleyBState = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonPBI_Click(object sender, EventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                pulleyBState = 1;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonPBB_Click(object sender, EventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                pulleyBState = 2;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonPBL_Click(object sender, EventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                pulleyBState = 3;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonPBR_Click(object sender, EventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                pulleyBState = 4;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonPCF_Click(object sender, EventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                pulleyCState = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonPCI_Click(object sender, EventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                pulleyCState = 1;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonPCB_Click(object sender, EventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                pulleyCState = 2;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonPCL_Click(object sender, EventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                pulleyCState = 3;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonPCR_Click(object sender, EventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                pulleyCState = 4;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonPCH_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                pulleyCHook = 1;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonPCH_MouseUp(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                pulleyCHook = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void Buttonn20n10_MouseDown(object sender, MouseEventArgs e)
        {
            if (buttonSend.Enabled == true)
            {
                Vx = -60;
                Vy = -15;
                Rw = 0;
                SetSendContent();
                ButtonSend_Click(null, null);
            }
        }

        private void ButtonConnect_Click(object sender, EventArgs e)
        {
            if (buttonConnect.Text == "Connect")
            {
                this.DisposeSerialPort();
                this.InitialSerialPort();
                buttonConnect.Text = "Disconnect";
                buttonSend.Enabled = true;
            }
            else
            {
                this.DisposeSerialPort();
                buttonConnect.Text = "Connect";
                buttonSend.Enabled = false;
            }
        }

        private void TimerSerial_Tick(object sender, EventArgs e)
        {
            if (SerialPort.GetPortNames().Length != comboBoxSerial.Items.Count)
            {
                comboBoxSerial.Items.Clear();
                comboBoxSerial.Items.AddRange(SerialPort.GetPortNames());
                comboBoxSerial.SelectedIndex = comboBoxSerial.Items.Count - 1;
            }
            if(comboBoxSerial.Items.Count==0)
            {
                buttonConnect.Enabled = false;
            }
            else
            {
                buttonConnect.Enabled = true;
            }
            labelSpeedX.Text = "X: " + Vx.ToString();
            labelSpeedY.Text = "Y: " + Vy.ToString();
            labelSpeedZ.Text = "Z: " + Rw.ToString();
            labelMA.Text = "MA: " + dataVal[0];
            labelMB.Text = "MB: " + dataVal[1];
            labelMC.Text = "MC: " + dataVal[2];
            labelMD.Text = "MD: " + dataVal[3];
            labelStepperHeight.Text = "H: " + dataVal[4];
            labelServo.Text = "S: " + dataVal[5];
            labelP.Text = "P: " + dataVal[6];
            labelI.Text = "I: " + dataVal[7];
            textBoxP.Text = "P: " + P.ToString();
            textBoxI.Text = "I: " + I.ToString();
            textBoxStpHeight.Text = StepperHeight.ToString();
        }

        private void ButtonSend_Click(object sender, EventArgs e)
        {
            port.Write(textBoxSend.Text);
        }
    }
}
