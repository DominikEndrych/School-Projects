
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.image.Image;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author END0013
 */
public class AlienShip extends AbstractBrick {
    
    public AlienShip(int x, int y){
        this.x = x;
        this.y = y;
    }
    
    @Override
    public boolean isHit(double a, double b){
        return (Math.abs(a-x) < 35 && Math.abs(b-y) < 15);
    }
    
    @Override
    public void paint(GraphicsContext gc) {
        Image brickImage = new Image(getClass().getResourceAsStream("img/alienShip.png"));
        gc.drawImage(brickImage, x-35, y-15);
    }
}
