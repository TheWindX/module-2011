import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class user extends JPanel
{
    complex map_point(float x, float y)
    {
    	x = (float)(x/256-1.5);
    	y = (float)(y/256-0.8);
  	  return new complex(x, y);
    }
    
    Color color_gradient(Color c1, Color c2, float ratio)
    {
    	int red = (int)(c2.getRed() * ratio + c1.getRed() * (1 - ratio));
        int green = (int)(c2.getGreen() * ratio +
                          c1.getGreen() * (1 - ratio));
        int blue = (int)(c2.getBlue() * ratio +
                         c1.getBlue() * (1 - ratio));
        
        return new Color(red, green, blue);
    }
    
    
    BufferedImage draw()
    {
    	BufferedImage off_Image =
    			  new BufferedImage(512, 512,
    			                    BufferedImage.TYPE_INT_ARGB);

    			Graphics2D g2d = off_Image.createGraphics();
    			  for(int x = 0; x<512; ++x)
    		    	  for(int y = 0; y<512; ++y)
    		    	  {
    		    		  complex z  = map_point(x, y);
    		    		  complex c = z;
    		    		  
    		    		  int i = 0;
    		    		  for(; i<100; ++i)
    		    		  {
    		    			  z = z.times(z).plus(c);
    		    			  if(z.abs() > 2) break;
    		    		  }
    		    		  
    		    		  Color color = color_gradient(new Color(111, 111, 111), new Color(0, 0, 0), (float)(i/100.0 ) );
    		    		 g2d.setColor(color);
    		    		 g2d.drawLine(x, y, x, y);
    		    	  }
    			
    			return off_Image;
    }
    
    BufferedImage img = draw();
	public void paintComponent(Graphics g) {
	      super.paintComponent(g);
	      Graphics2D g2d = (Graphics2D) g;
	      g2d.setColor(Color.blue);
	      g2d.drawImage(img, 0, 0, 512, 512, null);
	  }
	  
	  public static void main(String[] args) {		   
	      JFrame frame = new JFrame("Points");
	      frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
	      frame.add(new user());
	      frame.setSize(512, 512);
	      frame.setLocationRelativeTo(null);
	      frame.setVisible(true);
	  }
}