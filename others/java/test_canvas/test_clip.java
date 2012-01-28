import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.RenderingHints;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.JFrame;
import javax.swing.JPanel;



public class test_clip extends JPanel
{	
	void test_clip_paint(Graphics2D g, int lv)
	{
		if(lv == 0) return;
		Graphics2D g_curGraphics2d = (Graphics2D)g.create();
		g_curGraphics2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
		g_curGraphics2d.translate(280, 280);
		g_curGraphics2d.scale(0.5, 0.5);
		g_curGraphics2d.setClip(g_curGraphics2d.getClipBounds().intersection( new Rectangle(0, 0, 512, 512) ) );
		
		g_curGraphics2d.setColor(Color.black);
		g_curGraphics2d.fillRect(0, 0, 512, 512);
		g_curGraphics2d.setColor(new Color(0xffff0000));
		g_curGraphics2d.fillArc(-20, -20, 552, 552, 0, 360);
		test_clip_paint(g_curGraphics2d, lv-1);
		g_curGraphics2d.setStroke(new BasicStroke(10) );
		g_curGraphics2d.setColor(new Color(0xffffff00));
		g_curGraphics2d.drawRect(1, 1, 505, 505);
		g_curGraphics2d.dispose();
	}
	@Override
	public void paint(Graphics g) {
		// TODO Auto-generated method stub
		super.paint(g);
		Graphics2D g1 =  (Graphics2D)g.create();
		test_clip_paint(g1, 3);
		
		g.drawLine(0,  0, 256, 256);
	}
	 
	 public static void main(String[] args) 
	{
		JFrame f = new JFrame();
		f.addWindowListener(new WindowAdapter() {
		      public void windowClosing(WindowEvent e) {
		        System.exit(0);
		      }
		    });
		    f.setContentPane(new test_clip());
		    f.setSize(800,375);
		    f.setVisible(true);
	}
}
	 
	 
	 
	 