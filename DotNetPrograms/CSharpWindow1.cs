using System;
using System.Drawing;
using System.Windows.Forms;

public class CSharpWindow1:Form
{
   public static void Main()
   {
      Application.Run(new CSharpWindow1());
   
   }
   
   public CSharpWindow1()
   {
       Width = 800;
       Height = 600;
       BackColor = Color.Black;
       ResizeRedraw = true;	   
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
}