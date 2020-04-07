import javafx.scene.canvas.GraphicsContext;

import java.util.ArrayList;
import java.util.Iterator;

public class ObjectManager {

    private final ArrayList<Transformable> objects;

    public ObjectManager() {
        objects = new ArrayList<Transformable>();
    }

    public void add(Transformable p) {
        this.objects.add(p);
    }

    public void redraw(Ball ball, GraphicsContext gc) {
        
        Iterator<Transformable> it = this.objects.iterator();
        while (it.hasNext()) {
            Transformable ip = it.next();
            if (ip.isHit(ball.getX(), ball.getY())) {
                it.remove();
            } 
            else ip.paint(gc);
            
            if(ip instanceof AlienShip)  {
                ip.moveObject(0.5, 0, gc);
            }
        }
    }

}
