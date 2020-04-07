import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;
import javafx.scene.transform.Affine;
import javafx.scene.transform.Transform;

/**
 * Graphical representation of a catapult and it also implements process of a shooting.
 * @author koz01
 *
 */
public class Catapult {

	private static final int ARR_SIZE = 5;
	private final int x;
	private final int y;
	private int len;

	private int angle;

	private int power;

	public Catapult(int x, int y, int len) {
		super();
		this.x = x;
		this.y = y;
		this.len = len;
	}

	public void setAngle(int angle) {
		this.angle = angle;
	}

	public void setPower(int power) {
		this.power = power;
	}

	public void setLen(int len) { this.len = len; }

	public void shootBall(Ball ball, CatapultSimulationController controllerForRedraw) {
		int  xAcc = (int) (Math.cos(Math.toRadians(this.angle)) * this.power);
		int yAcc = (int) (-Math.sin(Math.toRadians(this.angle)) * this.power);

		int catapultEndX = x + (int) ( Math.cos(Math.toRadians(angle)) * len);
		int catapultEndY = y - (int) ( Math.sin(Math.toRadians(angle)) * len);

		long lastTime = System.currentTimeMillis();

		while (ball.getX() < catapultEndX && ball.getY() > catapultEndY) {
			ProcessRoutines.sleep(1);
			long newTime = System.currentTimeMillis();
			double timeDiff = (newTime - lastTime) / 100.0;
			ball.move(timeDiff);
			ball.accelerate(xAcc, yAcc, timeDiff);

			lastTime = newTime;
			controllerForRedraw.needsRedraw();
		}
		//TODO - Implement acceleration by catapult:
		// 1. Spread power to x and y directions: 
		//  - xAcc = cos(angle) * power
		//  - yAcc = sin(angle) * power (coordinate system in canvas is oposite)
		// 2. Compute end of the catapult.
		// 3. Store initial time in the variable lastTime.
		// 4. while ball do not reach an end of the catapult do:
		//      Sleep for a one milisecond (use ProcessRoutines.sleep).
		//      Get actual time and compute a time difference.
		//      Move ball(Call method move on the ball).
		//      Compute new acceleration of the ball(Call method accelerate on the ball).
		//      Update variable lastTime with a actual time.
		//		Force canvas redraw.
	}

	public void paint(GraphicsContext gc) {
		Affine oldTransform = gc.getTransform();
		Transform transform = Transform.translate(x, y);
		transform = transform.createConcatenation(Transform.rotate(-angle, 0, 0));
		gc.setTransform(new Affine(transform));
		gc.setFill(Color.LIGHTBLUE);
		gc.setStroke(Color.LIGHTBLUE);
		gc.strokeLine(0, 0, len, 0);
		gc.fillPolygon(new double[] { len, len - ARR_SIZE, len - ARR_SIZE, len },
				new double[] { 0, -ARR_SIZE, ARR_SIZE, 0 }, 4);
		gc.setTransform(oldTransform);
	}

}
