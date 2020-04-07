/**
 * It manages movement of a ball in space after is shot. 
 * It should also contains implementation of a shooting and a ball movement. However, that design
 * would be more complicated.
 * 
 * @author koz01
 *
 */
public class Physics {

	private final int gravity;
	
	
	public Physics(int gravity) {
		super();
		this.gravity = gravity;
	}

	public void manageBallMovement(Ball ball, CatapultSimulationController controllerForRedraw, int canvasWidth, int canvasHeight) {
		long time = System.currentTimeMillis();
		while (ball.getY() < canvasHeight) {
			ProcessRoutines.sleep(1);
			long newTime = System.currentTimeMillis();
			double timeDiff = (newTime - time) / 100.0;
			ball.move(timeDiff);
			ball.fixXCoordinate(canvasWidth);
			ball.accelerate(0, gravity, timeDiff);
			time = newTime;
			controllerForRedraw.needsRedraw();
		}

		//TODO Until the ball is above bottom of the canvas (its y coordinate is lower than
		//     a height of the canvas) move with ball and modify its acceleration in a vertical 
		//     dimension by gravity.
	}
}
