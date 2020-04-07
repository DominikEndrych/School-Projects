
import javafx.scene.canvas.GraphicsContext;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author Dominik
 */
public abstract class AbstractBrick implements Transformable{
    
    protected double x;
    protected double y;
    
    @Override
    public void moveObject(double x, double y, GraphicsContext gc){
        
        double smerX = x;
        double smerY = y;
        
        
        
        /*if(this.x <= 0 || this.x >= gc.getCanvas().getWidth()){
            x *= -1;
        }
        
        if(this.y == 0 || this.y == gc.getCanvas().getHeight()){
            y *= -1;
        }*/
        
        this.x += smerX;
        this.y += smerY;
        
        
        
    }
}