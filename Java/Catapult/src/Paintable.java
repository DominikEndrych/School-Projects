import javafx.scene.canvas.GraphicsContext;


public interface Paintable {
    public void paint(GraphicsContext gc);
    public boolean isHit(double a, double b);
}
