

import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.image.Image;
import java.lang.Math;

public class IronBrick extends AbstractBrick{
    /*private int x;
    private int y;*/
    private int hp;
    private boolean wasHit;
    
    public IronBrick(int x, int y){
        this.x = x;
        this.y = y;
        this.hp = 2;
        this.wasHit = false;
    }
    
    @Override
    public void paint(GraphicsContext gc){
        Image brickImage = new Image(getClass().getResourceAsStream("img/iron.png"));
        gc.drawImage(brickImage, x-35, y-15);
    }
    
    @Override
    public boolean isHit(double a, double b){
        if (Math.abs(a-x) < 35 && Math.abs(b-y) < 15){
            if(!wasHit){
                this.hp--;
                this.wasHit = true;
            }
        }
        else{
            this.wasHit = false;
        }
        
        if(this.hp == 0){
            return true;
        }
        else
            return false;   
    }
}
