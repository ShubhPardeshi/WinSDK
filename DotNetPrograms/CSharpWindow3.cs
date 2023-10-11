using System;
using System.Drawing;
using System.Windows.Forms;

public class CSharpWindow3:Form
{
  public static void Main()
  {
     Application.Run(new CSharpWindow3());
  }

  public CSharpWindow3()
  {
     Icon = new Icon("navwj.ico");
	 Width = 800;
	 Height = 600;
	 BackColor = Color.Black;
	 ResizeRedraw = true;
	 this.KeyDown += new KeyEventHandler(MyKeyDown);
	 this.MouseDown += new MouseEventHandler(MyMouseDown);
  }

  protected override void OnPaint(PaintEventArgs PEA)
  {
    Graphics grfx = PEA.Graphics;
	StringFormat strfmt = new StringFormat();
	strfmt.Alignment = StringAlignment.Center;
	strfmt.LineAlignment = StringAlignment.Center;
	grfx.DrawString("Shubhangi",
	                 Font,
					 new SolidBrush(System.Drawing.Color.Green),
					 ClientRectangle,
	                 strfmt);
  }
  
  void MyKeyDown(Object Sender,KeyEventArgs K)
  {
     MessageBox.Show("Some Key is pressed");
  }
  
  void MyMouseDown(Object Sender,MouseEventArgs M)
  {
     MessageBox.Show("Mouse is clicked");
  }
}