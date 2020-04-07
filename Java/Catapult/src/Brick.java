import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.image.Image;
import java.lang.Math;


public class Brick extends AbstractBrick{
    
    /*private int x;
    private int y;*/
    
    public Brick(int x, int y){
        this.x = x;
        this.y = y;
    }
    
    @Override
    public void paint(GraphicsContext gc) {
        Image brickImage = new Image(getClass().getResourceAsStream("img/image.png"));
        gc.drawImage(brickImage, x-35, y-15);
    }
    
    @Override
    public boolean isHit(double a, double b){
        return (Math.abs(a-x) < 35 && Math.abs(b-y) < 15);
    }
    
}
